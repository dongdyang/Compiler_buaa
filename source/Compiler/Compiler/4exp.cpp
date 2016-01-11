#include "glob.h"

#define VOID 0
#define INT 1						//普通int
#define CHAR 2						//普通char
//#define WINT 3						//全局int	
//#define WCHAR 4						//全局char
#define INITSTACK 0x7fffeffc		//栈顶
#define VARREGSIZE 200


int tmi;							//临时的mi
int ap;								//地址表计数器address pointer
int preap;							//previous ap
int varreg[200];					//变量寄存器----------------------------
int ismain = 0;			//是否为主函数
int paran = 0;			//参数的数目
int tlabelnum = 0;			//标签数
int mi = 0;			//四元式处理的行数
int fp = 0;			//帧指针
int funcnum = 0;			//函数的个数
int sp = INITSTACK;	//栈指针
int level = 0;			//当前所在函数的层数,0表示main函数所在的层数
int funcparanum = 0;			//当前函数的参数个数，用于在地址传值的时候
int flag = 1;
int	cvl = 0;			//作为cvlevel的索引;
int apindex = 0;
int aps[30];
int precvlindex = 0;
int	precvl[20];
int beforefp = 3;			//这个表示每次每次进入一个函数，为了便于索引，要先将$ra,$sp,$fp值先压入($sp)栈,然后再为$fp进行相关操作，这里表示数量

char	tmpfunname[MAXIDENLEN] = " ";
char fname_tmp[100];
int proflag = 0;

int sps[20];
int spsindex = 0;

vector<int> constedge;

string paras[20];
vector<funcclass> fc;
vector<funcclass> tmpfunc;
tempvaraddress addrtable[1000];
cntstruct cnttable[200];
constvarlevel cvlevel[1000];

//在变量表中查找,并返回在临时表量表中的指针，返回的是索引t，目的是为通过name，找到其在table中的位置，为得到addrtable结构体中的信息
int findvartable(char *name) {
	int t = ap - 1;
	if (name[0] == '+' || name[0] == '-' || name[0] >= '0'&&name[0] <= '9')
		return -1;
	while (t >= 0) {
		if (strcmp(addrtable[t].name, name) == 0)
			return t;
		t--;
	}
	return -1;
}

//计算函数的层差
int funlevel(char* topfname, char* fname) {
	int pre = 0, cur = 0;
	for (int i = 0; i < (int)fc.size(); i++) {
		if (strcmp(fc[i].name, topfname) == 0) {
			pre = fc[i].level;
		}
	}
	for (int i = 0; i < (int)fc.size(); i++) {
		if (strcmp(fc[i].name, fname) == 0) {
			cur = fc[i].level;
		}
	}
	return pre - cur;
	/*
	调用者层数减去被调用者，比如层数为
	f1{
		f2{
			f3{
			}
		}
		f2调用f3
	}
	此时为2-3，返回-1
	*/
}

//计算变量的层数
int cvlevel_func(char *name) {
	for (int i = cvl - 1; i >= 0; i--) {
		if (strcmp(name, cvlevel[i].name) == 0) {
			return cvlevel[i].level;
		}
	}
	return -1;
}

//查找汇编变量地址,求变量的相对fp的地址，返回的是变量的address
int varaddr(char *name) {
	int t = ap - 1;
	if (name[0] == '+' || name[0] == '-' || name[0] >= '0'&&name[0] <= '9')
		return -1;
	while (t >= 0) {
		if (strcmp(addrtable[t].name, name) == 0) {
			return addrtable[t].address;
		}
		t--;
	}
	return -1;
}

/*
以下两个函数分别是为找到
函数和数组的类型（新定义的类型值）
*/
int funckind(char *fname) {
	for (int i = 0; i < (int)fc.size(); i++) {
		if (strcmp(fc[i].name, fname) == 0) {
			return fc[i].kind;
		}
	}
	return -1;
}

int varkind(char *name) {
	int t = ap - 1;
	if (name[0] == '+' || name[0] == '-' || name[0] >= '0'&&name[0] <= '9')
		return -1;
	while (t >= 0) {
		if (strcmp(addrtable[t].name, name) == 0)
			return addrtable[t].kind;
		t--;
	}
	return -1;
}

//给地址表插入相对地址，sp不变
void insertaddress(int kind, int addr, int nmi) {
	if (nmi == -1) {
		strcpy(addrtable[ap].name, midcode[mi].var3);
	}
	else {
		strcpy(addrtable[ap].name, midcode[nmi].var3);
	}
	if (addr == -1) {
		//因为每一次压完栈后都首先进行申请4个字节空间的操作，因此这里为了保证原来的地址，需要加回4
		//地址为相对地址
		addrtable[ap].address = sp + 4;
	}
	else {
		addrtable[ap].address = addr;//此时为定义函数的参数地址，为4的倍数：4，8，12，...,此时sp的地址不改变
	}
	addrtable[ap].kind = kind;
	addrtable[ap].cnt = 0;
	ap++;
}

//压栈lenth*4个字节,lenth默认为1,item默认为"0"
void pushstack(char* item, int lenth) {
	if (lenth == 1) {
		rsT << "\t\tli\t$t0\t" << item << "\t" << endl;
		rsT << "\t\tsw\t$t0\t($sp)" << endl;
	}
	sp -= (4 * lenth);
	rsT << "\t\tsubi\t$sp\t$sp\t" << 4 * lenth << endl;
	return;
}

/*---------------------------本文件入口函数---------------------------------*/
//中间代码转汇编
void midcode2asm() {
	memset(varreg, 0xff, sizeof(int) * 200);
	rsT << "\t.text" << endl;
	rsT << "\t\tori\t$fp\t$sp\t0" << endl;
	rsT << "\t\tsw\t$fp\t($sp)" << endl;
	rsT << "\t\tsubi\t$sp\t$sp\t4" << endl;
	rsT << "\t\tsw\t$fp\t($sp)" << endl;
	rsT << "\t\tori\t$fp\t$sp\t0" << endl;
	rsT << "\t\tsubi\t$sp\t$sp\t4" << endl;
	//rsT << "\t\tli\t$t8\t0x10040000\t\t#save word" << endl;
	sp = -4;
	mi = ap = 0;
	while (mi < midcodeiter) {
		constvarasm();
		aps[apindex++] = ap;
		
		rsT << "\t\tj\t__main" << endl;
		enterfunc();
	}
}

//进行常量和变量的定义
void constvarasm() {
	while (strcmp(midcode[mi].op, "const") == 0) {
		//-----------------为变量索引做准备
		strcpy(cvlevel[cvl].name, midcode[mi].var3);
		cvlevel[cvl].level = level;
		cvl++;
		pushstack(midcode[mi].var2);
		if (strcmp(midcode[mi].var1, "int") == 0) {
			insertaddress(INT);
		}
		else {
			insertaddress(CHAR);
		}
		mi++;
	}

	constedge.push_back(ap);//---------------------------------------的记录点


	while (strcmp(midcode[mi].op, "int") == 0 || strcmp(midcode[mi].op, "char") == 0 || strcmp(midcode[mi].op, "inta") == 0 || strcmp(midcode[mi].op, "chara") == 0)
	{
		//变量定义
		while (strcmp(midcode[mi].op, "int") == 0 || strcmp(midcode[mi].op, "char") == 0) {
			//-------------为变量索引做准备
			strcpy(cvlevel[cvl].name, midcode[mi].var3);
			cvlevel[cvl].level = level;
			cvl++;
			pushstack("0");//全局变量初始化为0
			if (strcmp(midcode[mi].op, "int") == 0) {
				insertaddress(INT);
			}
			else {
				insertaddress(CHAR);
			}
			mi++;
		}
		//数组定义
		//inta, 0, num, name
		//chara, 0, num, name
		while (strcmp(midcode[mi].op, "inta") == 0 || strcmp(midcode[mi].op, "chara") == 0) {
			//------------为变量索引做准备
			strcpy(cvlevel[cvl].name, midcode[mi].var3);
			cvlevel[cvl].level = level;
			cvl++;
			pushstack("0", atoi(midcode[mi].var2));
			if (strcmp(midcode[mi].op, "inta") == 0) {
				insertaddress(INT);
			}
			else {
				insertaddress(CHAR);
			}
			mi++;
		}
	}
	if (!ismain) {
		sps[spsindex] = sp;
		spsindex++;
	}

}

//进行函数类型的判断
void enterfunc() {
	funcclass tfc;
	while (strcmp(midcode[mi].op, "func") == 0) {
		funcnum++;
		precvl[precvlindex++] = cvl;
		strcpy(tfc.name, midcode[mi].var3);
		strcpy(fname_tmp, midcode[mi].var3);
		level++;
		if (strcmp(midcode[mi].var1, "char") == 0) {
			tfc.kind = CHAR;
		}
		else if (strcmp(midcode[mi].var1, "int") == 0) {
			tfc.kind = INT;
		}
		else {
			tfc.kind = VOID;
		}

		if (strcmp(midcode[mi].var3, "main") == 0) {
			ismain = 1;
			level--;
			rsT << "__main:" << endl;
		}
		else {
			ismain = 0;
			rsT << midcode[mi].var3 << ":" << endl;
		}
		tfc.level = level;
		fc.push_back(tfc);
		tmpfunc.push_back(tfc);
		strcpy(tmpfunname, midcode[mi].var3);

		mi++;
		funcasm();//若是某一层的主部分begin...end得单独出来写,这里未处理
	}
}

//处理函数内容
void funcasm() {
	if (!ismain) {
		
		
		sp = 0;//相对偏移为0，保存现场，如果是主函数则不需要将sp置为0

		rsT << "\t\tsw\t$sp\t($sp)\t\t#save register begin-----" << endl;
		rsT << "\t\tsubi\t$sp\t$sp\t4" << endl;

		rsT << "\t\tsw\t$ra\t($sp)" << endl;//保存$ra
		rsT << "\t\tsubi\t$sp\t$sp\t4" << endl;

		rsT << "\t\tsw\t$fp\t($sp)" << endl;//保存上一个函数的$fp
		rsT << "\t\tsubi\t$sp\t$sp\t4" << endl;

		rsT << "\t\tmove\t$fp\t$sp" << endl;//设置本函数$fp：$fp=$sp
		rsT << "\t\tsw\t$t9\t($fp)" << endl;
		rsT << "\t\tsubi\t$sp\t$sp\t4\t\t#save register ok---" << endl;//$sp-=4
		sp -= 4;
		proflag = 1;
	}
	else {
		if (proflag == 1) {
			sp = sps[0];
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	if (strcmp(midcode[mi].op, "para") == 0) {
		paraasm();
		for (int i = 0; i < (int)fc.size(); i++) {
			if (strcmp(fc[i].name, fname_tmp) == 0) {
				fc[i].paranum = paranum;
			}
		}
		mi++;
	}
	//if (!ismain) {
		constvarasm();
	//}
	aps[apindex++] = ap;
	if (strcmp(tmpfunname, "main") != 0) {
		rsT << "\t\tj\t" << tmpfunname << "__main" << endl;//checked
	}
	enterfunc();
	tmi = mi;
	//进入函数主部分begin...end
	while (strcmp(midcode[mi].op, "end") != 0) {
		paran = 0;
		for (int i = 0; i < (int)strlen(midcode[mi].op); i++) { if (midcode[mi].op[i] == ' ') { midcode[mi].op[i] = '\0'; break; } }
		if (strcmp(midcode[mi].op, "begin") == 0) beginasm();
		if (strcmp(midcode[mi].op, "+") == 0) addasm();
		if (strcmp(midcode[mi].op, "-") == 0) subasm();
		if (strcmp(midcode[mi].op, "*") == 0) mulasm();
		if (strcmp(midcode[mi].op, "/") == 0) divasm();
		if (strcmp(midcode[mi].op, ">") == 0) greasm();
		if (strcmp(midcode[mi].op, ">=") == 0) geqasm();
		if (strcmp(midcode[mi].op, "<") == 0) lssasm();
		if (strcmp(midcode[mi].op, "<=") == 0) leqasm();
		if (strcmp(midcode[mi].op, "<>") == 0) neqasm();
		if (strcmp(midcode[mi].op, "==") == 0) eqlasm();
		if (strcmp(midcode[mi].op, "=") == 0) assasm();
		if (strcmp(midcode[mi].op, "[]=") == 0) aassasm();
		if (strcmp(midcode[mi].op, "geta") == 0) assaasm();
		if (strcmp(midcode[mi].op, "lab:") == 0) setlabasm();
		if (strcmp(midcode[mi].op, "rd") == 0) rdasm();
		if (strcmp(midcode[mi].op, "wt") == 0) wtasm();
		if (strcmp(midcode[mi].op, "jne") == 0) jneasm();
		if (strcmp(midcode[mi].op, "jmp") == 0) jmpasm();
		if (strcmp(midcode[mi].op, "call") == 0) callasm();
		if (strcmp(midcode[mi].op, "ret") == 0) retasm();
		if (strcmp(midcode[mi].op, "fupa") == 0) {
			int index = 0;
			while (strcmp(midcode[mi].op, "fupa") == 0) {
				fupaasm(index);
				index++;
				mi++;
			}
			continue;
		}
		mi++;
	}
	////need to return value into memory
	//for (int i = 0; i < VARREGSIZE; i++) {
	//	if (varreg[i] >= 0 && varreg[i] <= 7) {
	//		//mips_find_var(midcode[mi].var3, "sw", "$t0");
	//		char* temp = new char[8];
	//		sprintf(temp, "$s%d", varreg[i]);
	//		mips_find_var(addrtable[i].name, "sw", temp);
	//		delete[] temp;
	//	}
	//}

	--apindex;
	ap = aps[apindex - 1];
	string funcname;
	funcname = tmpfunc.back().name;
	tmpfunc.pop_back();
	level--;

	cvl = precvl[--precvlindex];
	if (ismain) {
		rsT << "\t\tli\t$v0\t10" << endl;
		rsT << "\t\tsyscall" << endl;//终止程序
	}
	else {
		spsindex--;
		rsT << "__FEND_LAB_" << funcname << ":" << endl;//结束开始
		rsT << "\t\tlw\t$sp\t12($fp)" << endl;//退栈,恢复$sp,因此存的都是相对地址
		rsT << "\t\tlw\t$ra\t8($fp)" << endl;//恢复$ra
		rsT << "\t\tlw\t$fp\t4($fp)" << endl;//恢复上一个函数的fp					
		rsT << "\t\tjr\t$ra\t" << endl;//返回
	}
	mi = mi + 1;
	return;
}

/*    call, f ,   , a */
void callasm() {
	// 第一个值为指定的内存地址，块的大小由第三个参数指定，为新申请的内存做初始化工作， 其返回值为指向s的指针。

	savesreg();
	rsT << "\t\tmove\t$t9\t$fp" << endl;
	int fp_lw = funlevel(tmpfunc.back().name, midcode[mi].var1) + 1;//调用函数与被调用函数的层差
	while (fp_lw != 0) {
		rsT << "\t\tlw\t$t9\t($t9)" << endl;
		fp_lw--;
	}
	rsT << "\t\tjal\t" << midcode[mi].var1 << endl;
	rsT << "\t\tnop\n";
	loadsreg();//恢复$s0-$s7
	/*-----------------传地址---------------------------*/
	char curfuncname[100];
	strcpy(curfuncname, midcode[mi].var1);
	for (int i = 0; i < (int)fc.size(); i++) {
		if (strcmp(fc[i].name, curfuncname) == 0) {
			int length = fc[i].paranum;
			char str[20];
			for (int j = 0; j < length; j++) {
				strcpy(str, paras[j].c_str());
				//这里进行判断，是传地址则进行下面步骤，只是传值则跳过即可，判断为fc的isParaVar来进行判断
				if (varaddr(str) != -1 && fc[i].isParaVar[j]) {
					rsT << "\t\tlw\t$t0\t" << (length - j) * 4 << "($sp)" << endl;//当前栈上还压着上一层的$fp,这层的$ra
					mips_find_var(str, "sw", "$t0");
					for (int k = mi - 1; k >= 0; k--) {
						if (strcmp(midcode[k].var3, str) == 0 && strcmp(midcode[k].op, "geta") == 0) {
							int addr = varaddr(midcode[k].var1);
							if (isdigit(midcode[k].var2[0]) || midcode[k].var2[0] == '-' || midcode[k].var2[0] == '+') {
								addr += (atoi(midcode[k].var2) * 4);
								mips_find_var(midcode[k].var1, "sw", "$t0", 0, addr, 1);
							}
							else {
								mips_find_var(midcode[k].var2, "lw", "$t1");
								rsT << "\t\tmul\t$t1\t$t1\t4\n";
								rsT << "\t\taddi\t$t1\t$t1\t" << addr << endl;
								mips_find_var(midcode[k].var1, "add", "$t1", 1);
								rsT << "\t\tsw\t$t0\t0($t1)" << endl;
							}
							break;
						}
					}
				}
			}
		}
	}
	if (midcode[mi].var3[0] != ' ' && midcode[mi].var3[0] != '\0') {
		mips_find_var(midcode[mi].var3, "sw", "$v0");
	}
}

void beginasm() {
	if (strcmp(midcode[mi - 1].var3, "main") != 0) {
		rsT << midcode[mi].var3 << "__main:" << endl;
	}
	inittempvar();
	if (OPTFLAG) {
		memset(varreg, 0xff, sizeof(int) * VARREGSIZE);
		cntopt();
	}

}

void inittempvar() {
	while (strcmp(midcode[tmi].op, "end") != 0) {
		char v1[100], v2[100], v3[100];
		strcpy(v1, midcode[tmi].var1);
		strcpy(v2, midcode[tmi].var2);
		strcpy(v3, midcode[tmi].var3);
		if (v1[0] == '$' && varaddr(v1) == -1) {
			pushstack("0");
			insertaddress(INT, -1, tmi);
			strcpy(cvlevel[cvl].name, v1);
			cvlevel[cvl].level = level;
			cvl++;
		}
		if (v2[0] == '$' && varaddr(v2) == -1) {
			pushstack("0");
			insertaddress(INT, -1, tmi);
			strcpy(cvlevel[cvl].name, v2);
			cvlevel[cvl].level = level;
			cvl++;
		}
		if (v3[0] == '$' && varaddr(v3) == -1) {
			pushstack("0");
			strcpy(cvlevel[cvl].name, v3);
			cvlevel[cvl].level = level;
			cvl++;
			//四元式为	call, f , , a			a = f()
			if (strcmp(midcode[tmi].op, "call") == 0) {
				insertaddress(funckind(midcode[tmi].var1), -1, tmi);
			}
			//针对数组
			else if (strcmp(midcode[tmi].op, "geta") == 0) {
				insertaddress(varkind(v1), -1, tmi);
			}
			else {
				insertaddress(INT, -1, tmi);
			}
		}
		tmi++;
	}
}

//fupa,   ,   , a     ==> a is a function parameter
//函数调用，参数是从$sp的高地址到低地址的
void fupaasm(int index) {
	paras[index] = midcode[mi].var3;
	if (isdigit(midcode[mi].var3[0])) {
		rsT << "\t\tli\t$t0\t" << midcode[mi].var3 << endl;
	}
	else {
		mips_find_var(midcode[mi].var3, "lw", "$t0");
	}
	rsT << "\t\tsw\t$t0\t($sp)" << endl;      //sw    $t0 ($sp)	将调用所需要传递的参数压栈
	sp -= 4;
	rsT << "\t\tsubi\t$sp\t$sp\t4" << endl; //subi  $sp $sp 4  
}

//para, int, , a == > f(int a, ...)
//函数定义时的参数表
void paraasm() {
	paranum = 0;
	for (int i = mi; i < midcodeiter; i++) {
		if (strcmp(midcode[i].op, "para") == 0) {
			if (strcmp(midcode[i].var2, "var") == 0) {
				fc.back().isParaVar[paranum] = true;
			}
			else {
				fc.back().isParaVar[paranum] = false;
			}
			//-------------------------------------------------------------------------为变量索引做准备
			strcpy(cvlevel[cvl].name, midcode[i].var3);
			cvlevel[cvl].level = level;
			cvl++;
			paranum++;
		}
		else
			break;
	}
	for (int i = 0; i < paranum; i++) {
		int kind = (strcmp(midcode[mi].var1, "int") == 0) ? INT : CHAR;
		insertaddress(kind, 4 * (paranum - i) + beforefp * 4);
		//参数的地址为4*1，而不是相对sp地址,地址是从高到低的，也即类似于...，16，12，8，4这样递减，
		//与函数调用相合，优先分配空间给参数一致
		mi++;
	}
	mi--;
}


//    jmp ,  ,  ,
void jmpasm() {
	rsT << "\t\tj\t" << midcode[mi].var3 << endl;
}

/*
jne
bne		$t0		1	label
判断condition的条件结果存在$t0里
*/
void jneasm() {
	rsT << "\t\tbne\t$t0\t1\t" << midcode[mi].var3 << endl;
}

//放置标签    lab,  ,  ,
void setlabasm() {
	rsT << midcode[mi].var3 << ":\n";
}

//    add, a, b, c
void addasm() {

	if (isdigit(midcode[mi].var1[0]) || midcode[mi].var1[0] == '-' || midcode[mi].var1[0] == '+') {
		rsT << "\t\tli\t$t0\t" << midcode[mi].var1 << endl;
	}
	else {
		mips_find_var(midcode[mi].var1, "lw", "$t0");
	}
	if (isdigit(midcode[mi].var2[0]) || midcode[mi].var2[0] == '-' || midcode[mi].var2[0] == '+') {
		rsT << "\t\tli\t$t1\t" << midcode[mi].var2 << endl;
	}
	else {
		mips_find_var(midcode[mi].var2, "lw", "$t1");
	}
	rsT << "\t\tadd\t$t0\t$t0\t$t1" << endl;
	mips_find_var(midcode[mi].var3, "sw", "$t0");
}

//    sub, a, b, c
void subasm() {


	if (isdigit(midcode[mi].var1[0]) || midcode[mi].var1[0] == '-' || midcode[mi].var1[0] == '+') {
		rsT << "\t\tli\t$t0\t" << midcode[mi].var1 << endl;
	}
	else {
		mips_find_var(midcode[mi].var1, "lw", "$t0");
	}
	if (isdigit(midcode[mi].var2[0]) || midcode[mi].var2[0] == '-' || midcode[mi].var2[0] == '+') {
		rsT << "\t\tli\t$t1\t" << midcode[mi].var2 << endl;
	}
	else {
		mips_find_var(midcode[mi].var2, "lw", "$t1");
	}
	rsT << "\t\tsub\t$t0\t$t0\t$t1" << endl;
	mips_find_var(midcode[mi].var3, "sw", "$t0");
}

//    mul, a, b, c
void mulasm() {


	//--------------------
	if (isdigit(midcode[mi].var1[0]) || midcode[mi].var1[0] == '-' || midcode[mi].var1[0] == '+') {
		rsT << "\t\tli\t$t0\t" << midcode[mi].var1 << endl;
	}
	else {
		mips_find_var(midcode[mi].var1, "lw", "$t0");
	}
	if (isdigit(midcode[mi].var2[0]) || midcode[mi].var2[0] == '-' || midcode[mi].var2[0] == '+') {
		rsT << "\t\tli\t$t1\t" << midcode[mi].var2 << endl;
	}
	else {
		mips_find_var(midcode[mi].var2, "lw", "$t1");
	}
	rsT << "\t\tmul\t$t0\t$t0\t$t1" << endl;
	mips_find_var(midcode[mi].var3, "sw", "$t0");
}

//    div, a, b, c
void divasm() {


	if (isdigit(midcode[mi].var1[0]) || midcode[mi].var1[0] == '-' || midcode[mi].var1[0] == '+') {
		rsT << "\t\tli\t$t0\t" << midcode[mi].var1 << endl;
	}
	else {
		mips_find_var(midcode[mi].var1, "lw", "$t0");
	}
	if (isdigit(midcode[mi].var2[0]) || midcode[mi].var2[0] == '-' || midcode[mi].var2[0] == '+') {
		rsT << "\t\tli\t$t1\t" << midcode[mi].var2 << endl;
	}
	else {
		mips_find_var(midcode[mi].var2, "lw", "$t1");
	}
	rsT << "\t\tdiv\t$t0\t$t0\t$t1" << endl;
	mips_find_var(midcode[mi].var3, "sw", "$t0");
}

//    > , a, b, c
void greasm() {
	if (isdigit(midcode[mi].var1[0]) || midcode[mi].var1[0] == '-' || midcode[mi].var1[0] == '+') {
		rsT << "\t\tli\t$t0\t" << midcode[mi].var1 << endl;
	}
	else {
		mips_find_var(midcode[mi].var1, "lw", "$t0");
	}
	if (isdigit(midcode[mi].var2[0]) || midcode[mi].var2[0] == '-' || midcode[mi].var2[0] == '+') {
		rsT << "\t\tli\t$t1\t" << midcode[mi].var2 << endl;
	}
	else {
		mips_find_var(midcode[mi].var2, "lw", "$t1");
	}
	rsT << "\t\tslt\t$t0\t$t1\t$t0" << endl;
}

//    >=
void geqasm() {
	if (isdigit(midcode[mi].var1[0]) || midcode[mi].var1[0] == '-' || midcode[mi].var1[0] == '+') {
		rsT << "\t\tli\t$t0\t" << midcode[mi].var1 << endl;
	}
	else {
		mips_find_var(midcode[mi].var1, "lw", "$t0");
	}
	if (isdigit(midcode[mi].var2[0]) || midcode[mi].var2[0] == '-' || midcode[mi].var2[0] == '+') {
		rsT << "\t\tli\t$t1\t" << midcode[mi].var2 << endl;
	}
	else {
		mips_find_var(midcode[mi].var2, "lw", "$t1");
	}
	rsT << "\t\tslt\t$t0\t$t0\t$t1" << endl;   //如果t0小于t1，则t0=1 否则为t0=0
	rsT << "\t\tli\t$t1\t1" << endl;			//t1=1
	rsT << "\t\tsub\t$t0\t$t1\t$t0" << endl;
}

//    <
void lssasm() {
	if (isdigit(midcode[mi].var1[0]) || midcode[mi].var1[0] == '-' || midcode[mi].var1[0] == '+') {
		rsT << "\t\tli\t$t0\t" << midcode[mi].var1 << endl;
	}
	else {
		mips_find_var(midcode[mi].var1, "lw", "$t0");
	}
	if (isdigit(midcode[mi].var2[0]) || midcode[mi].var2[0] == '-' || midcode[mi].var2[0] == '+') {
		rsT << "\t\tli\t$t1\t" << midcode[mi].var2 << endl;
	}
	else {
		mips_find_var(midcode[mi].var2, "lw", "$t1");
	}
	rsT << "\t\tslt\t$t0\t$t0\t$t1" << endl;
}

//    <=
void leqasm() {
	if (isdigit(midcode[mi].var1[0]) || midcode[mi].var1[0] == '-' || midcode[mi].var1[0] == '+') {
		rsT << "\t\tli\t$t0\t" << midcode[mi].var1 << endl;
	}
	else {
		mips_find_var(midcode[mi].var1, "lw", "$t0");
	}
	if (isdigit(midcode[mi].var2[0]) || midcode[mi].var2[0] == '-' || midcode[mi].var2[0] == '+') {
		rsT << "\t\tli\t$t1\t" << midcode[mi].var2 << endl;
	}
	else {
		mips_find_var(midcode[mi].var2, "lw", "$t1");
	}
	rsT << "\t\tslt\t$t0\t$t1\t$t0" << endl;
	rsT << "\t\tli\t$t1\t1" << endl;
	rsT << "\t\tsub\t$t0\t$t1\t$t0" << endl;
}

//    ==
// condition语句
void eqlasm() {
	if (isdigit(midcode[mi].var1[0]) || midcode[mi].var1[0] == '-' || midcode[mi].var1[0] == '+') {
		rsT << "\t\tli\t$t0\t" << midcode[mi].var1 << endl;
	}
	else {
		mips_find_var(midcode[mi].var1, "lw", "$t0");
	}
	if (isdigit(midcode[mi].var2[0]) || midcode[mi].var2[0] == '-' || midcode[mi].var2[0] == '+') {
		rsT << "\t\tli\t$t1\t" << midcode[mi].var2 << endl;
	}
	else {
		mips_find_var(midcode[mi].var2, "lw", "$t1");
	}
	/*------------------------------------------------------------------------
	bne $1, $2, 10
	if($1!=$2)
	goto PC+4+40
	下面的逻辑是这样的：
	var1 var2不同，则调到label+t1，t0=0；
	var1 var2相同，则执行t0=1，跳到label+t2
	*/
	int t1 = tlabelnum++;
	int t2 = tlabelnum++;
	rsT << "\t\tbne\t$t0\t$t1\t__tLABEL" << t1 << endl;
	rsT << "\t\tli\t$t0\t1" << endl;	//li $t0 1	
	rsT << "\t\tj\t__tLABEL" << t2 << endl;
	rsT << "__tLABEL" << t1 << ":" << endl;
	rsT << "\t\tli\t$t0\t0" << endl;
	rsT << "__tLABEL" << t2 << ":" << endl;
}

//    <>
void neqasm() {
	if (isdigit(midcode[mi].var1[0]) || midcode[mi].var1[0] == '-' || midcode[mi].var1[0] == '+') {
		rsT << "\t\tli\t$t0\t" << midcode[mi].var1 << endl;
	}
	else {
		mips_find_var(midcode[mi].var1, "lw", "$t0");
	}
	if (isdigit(midcode[mi].var2[0]) || midcode[mi].var2[0] == '-' || midcode[mi].var2[0] == '+') {
		rsT << "\t\tli\t$t1\t" << midcode[mi].var2 << endl;
	}
	else {
		mips_find_var(midcode[mi].var2, "lw", "$t1");
	}
	/*
	beq $1,$2,10
	if($1==$2)
	goto PC+4+40
	*/
	int t1 = tlabelnum++;
	int t2 = tlabelnum++;
	rsT << "\t\tbeq\t$t0\t$t1\t__tLABEL" << t1 << endl;
	rsT << "\t\tli\t$t0\t1" << endl;
	rsT << "\t\tj\t__tLABEL" << t2 << endl;
	rsT << "__tLABEL" << t1 << ":" << endl;
	rsT << "\t\tli\t$t0\t0" << endl;
	rsT << "__tLABEL" << t2 << ":" << endl;
}

//=, 2, , temp			temp = 2;
void assasm() {
	//if (OPTFLAG) {
		//int reg_no = 0;
		//int reg_no2 = 0;
		//if ((reg_no = reg_find_var(midcode[mi].var3)) != -1) {
		//	if ((reg_no2 = reg_find_var(midcode[mi].var1)) != -1) {
		//		rsT << "\t\tsw\t$s" << reg_no2 << "\t$s" << reg_no << endl;
		//	}
		//	else {
		//		if (isdigit(midcode[mi].var1[0]) || midcode[mi].var1[0] == '-' || midcode[mi].var1[0] == '+') {
		//			rsT << "\t\tli\t$t0\t" << midcode[mi].var1 << endl;
		//		}
		//		else {
		//			mips_find_var(midcode[mi].var1, "lw", "$t0");
		//		}
		//		mips_find_var(midcode[mi].var3, "sw", "$t0");
		//	}
		//}
	//}

	if (isdigit(midcode[mi].var1[0]) || midcode[mi].var1[0] == '-' || midcode[mi].var1[0] == '+') {
		rsT << "\t\tli\t$t0\t" << midcode[mi].var1 << endl;
	}
	else {
		mips_find_var(midcode[mi].var1, "lw", "$t0");
	}
	mips_find_var(midcode[mi].var3, "sw", "$t0");
}

//    []= , a , i , t		a[i] = t; 
void aassasm() {
	int addr = varaddr(midcode[mi].var1);
	if (isdigit(midcode[mi].var2[0])) {
		addr += (atoi(midcode[mi].var2) * 4);
		if (isdigit(midcode[mi].var3[0]) || midcode[mi].var3[0] == '-' || midcode[mi].var3[0] == '+') {
			rsT << "\t\tli\t$t0\t" << midcode[mi].var3 << endl;
		}
		else {
			mips_find_var(midcode[mi].var3, "lw", "$t0");
		}
		mips_find_var(midcode[mi].var1, "sw", "$t0", 0, addr, 1);
	}
	else {
		//求数组元素a[i]地址
		mips_find_var(midcode[mi].var2, "lw", "$t1");
		rsT << "\t\tmul\t$t1\t$t1\t4\n";
		rsT << "\t\taddi\t$t1\t$t1\t" << addr << endl;
		mips_find_var(midcode[mi].var1, "add", "$t1", 1);
		if (isdigit(midcode[mi].var3[0]) || midcode[mi].var3[0] == '-' || midcode[mi].var3[0] == '+') {
			rsT << "\t\tli\t$t0\t" << midcode[mi].var3 << endl;
		}
		else {
			mips_find_var(midcode[mi].var3, "lw", "$t0");
		}
		rsT << "\t\tsw\t$t0\t0($t1)" << endl;
	}
}

//geta, a, n, b			b = a[n]
void assaasm() {
	int addr = varaddr(midcode[mi].var1);
	if (isdigit(midcode[mi].var2[0]) || midcode[mi].var2[0] == '-' || midcode[mi].var2[0] == '+') {
		addr += (atoi(midcode[mi].var2) * 4);    //addr1 = &a[n]
		mips_find_var(midcode[mi].var1, "lw", "$t0", 0, addr, 1);
		mips_find_var(midcode[mi].var3, "sw", "$t0");
	}
	else {
		//求数组元素a[i]地址
		mips_find_var(midcode[mi].var2, "lw", "$t1");
		rsT << "\t\tmul\t$t1\t$t1\t4\n";
		rsT << "\t\taddi\t$t1\t$t1\t" << addr << endl;
		mips_find_var(midcode[mi].var1, "add", "$t1", 1);
		rsT << "\t\tlw\t$t1\t0($t1)\n";
		mips_find_var(midcode[mi].var3, "sw", "$t1");
	}
}

//rd,   ,   , a
void rdasm() {
	int ti = findvartable(midcode[mi].var3);
	int kind = addrtable[ti].kind;
	if (kind == INT ) {
		rsT << "\t\tli\t$v0\t5" << endl;
	}
	else {
		rsT << "\t\tli\t$v0\t12" << endl;
	}
	rsT << "\t\tsyscall" << endl;
	mips_find_var(midcode[mi].var3, "sw", "$v0");
}

//wt,a,b,symb
//wt, ,b,int
//wt, ,b,char
//wt,a, , 
void wtasm() {
	//当a存在，不为空时
	if (midcode[mi].var1[0] != '\0') {
		int len = strlen(midcode[mi].var1);
		for (int i = 0; i < len; i++) {
			rsT << "\t\tli\t$v0\t11" << endl;
			rsT << "\t\tli\t$a0\t" << int(midcode[mi].var1[i]) << endl;
			rsT << "\t\tsyscall" << endl;
		}
	}
	if (midcode[mi].var2[0] != ' ' && midcode[mi].var2[0] != '\0') {
		//<无符号整数>
		if (isdigit(midcode[mi].var2[0])) {
			rsT << "\t\tli\t$v0\t1" << endl;
			rsT << "\t\tli\t$a0\t" << midcode[mi].var2 << endl;
			rsT << "\t\tsyscall" << endl;
			return;
		}
		//接着就是一个变量了
		int ti = findvartable(midcode[mi].var2);
		int kind = addrtable[ti].kind;
		//4.<常量定义>  :: = <标识符>＝ <常量>
		//5.<常量>  :: = [+| -] <无符号整数> | <字符>
		if (kind == INT ) {
			rsT << "\t\tli\t$v0\t1" << endl;
		}
		else {
			rsT << "\t\tli\t$v0\t11" << endl;
		}
		mips_find_var(midcode[mi].var2, "lw", "$a0");
		rsT << "\t\tsyscall" << endl;
	}
}

//ret ,   ,   , (a)   ==> return a / return
void retasm() {
	if (midcode[mi].var3[0] != ' ' && midcode[mi].var3[0] != '\0') {
		if (isdigit(midcode[mi].var3[0]) || midcode[mi].var2[0] == '-' || midcode[mi].var2[0] == '+') {
			rsT << "\t\tli\t$v0\t" << midcode[mi].var3 << endl;
		}
		else {
			mips_find_var(midcode[mi].var3, "lw", "$v0");
		}
	}
	rsT << "\t\tj\t__FEND_LAB_" << tmpfunc.back().name << endl;//跳至结束
}

//-----------------------------------------------------------------------------------------------

void mips_find_var(char* var, char* inst, char* reg, int type, int addr, int addrtype) {
	if (addrtype == 0) {
		int addr = varaddr(var);
		if (type == 0) {
			if (level == cvlevel_func(var)) {
				rsT << "\t\t" << inst << "\t" << reg << "\t" << addr << "($fp)" << endl;
			}
			else {
				int dis = level - cvlevel_func(var);
				rsT << "\t\tmove\t$t9\t$fp" << endl;
				while (dis != 0) {
					rsT << "\t\tlw\t$t9\t($t9)" << endl;
					dis--;
				}
				rsT << "\t\t" << inst << "\t" << reg << "\t" << addr << "($t9)" << endl;
			}
		}
		else {
			if (level == cvlevel_func(var)) {
				rsT << "\t\t" << inst << "\t" << reg << "\t" << reg << "\t$fp" << endl;
			}
			else {
				int dis = level - cvlevel_func(var);
				rsT << "\t\tmove\t$t9\t$fp" << endl;
				while (dis != 0) {
					rsT << "\t\tlw\t$t9\t($t9)" << endl;
					dis--;
				}
				rsT << "\t\t" << inst << "\t" << reg << "\t" << reg << "\t$t9" << endl;
			}
		}
	}
	else {
		if (level == cvlevel_func(var)) {
			rsT << "\t\t" << inst << "\t" << reg << "\t" << addr << "($fp)" << endl;
		}
		else {
			int dis = level - cvlevel_func(var);
			rsT << "\t\tmove\t$t9\t$fp" << endl;
			while (dis != 0) {
				rsT << "\t\tlw\t$t9\t($t9)" << endl;
				dis--;
			}
			rsT << "\t\t" << inst << "\t" << reg << "\t" << addr << "($t9)" << endl;
		}
	}
}

//----------------------------------------------------------------------------------------------------


//如果找得到返回这个值在变量寄存器的
int reg_find_var(char* name) {
	//varreg[cnttable[i].symbnum] = i;	//varreg的索引是该变量在变量表中的位置，相应的值为$s寄存器编号+1
	//int addr = addrtable[cnttable[i].symbnum].address;
	//rsT << "\t\tlw\t$s" << i << "\t" << addr << "($fp)" << endl;
	for (int i = 0; i < VARREGSIZE; i++) {
		if (varreg[i] >= 0 && varreg[i] <= 7) {
			if (strcmp(addrtable[i].name, name) == 0) {
				return varreg[i];
			}
		}
	}
	return -1;
}



//----------------------------------------------------------------------------------------------------
//函数参数和const常量不参加 s寄存器 的分配
bool cmpcnt(cntstruct a, cntstruct b) { return a.cnt > b.cnt; }
int cntindex = 0;//cnttable的size()
void cntopt() {
	//引用计数
	int tmi = mi;	//注意此时mi的值！！！！需要调整为为此函数的begin的mi值
	while (strcmp(midcode[tmi].op, "end") != 0) {
		if (!strcmp(midcode[tmi].op, "=") || !strcmp(midcode[tmi].op, "+") || !strcmp(midcode[tmi].op, "-") || !strcmp(midcode[tmi].op, "*") || !strcmp(midcode[tmi].op, "/")) {
			cnt(midcode[tmi].var1);
			cnt(midcode[tmi].var2);
			cnt(midcode[tmi].var3);
		}
		tmi++;
	}
	sort(cnttable, cnttable + cntindex, cmpcnt);//降序排列
	int tmp = cntindex > 8 ? 8 : cntindex;
	for (int i = 0; i < tmp; i++) {
		varreg[cnttable[i].symbnum] = i;	//varreg的索引是该变量在变量表中的位置，相应的值为$s寄存器编号+1
		int addr = addrtable[cnttable[i].symbnum].address;
		rsT << "\t\tlw\t$s" << i << "\t" << addr << "($fp)" << endl;
	}
}

int lstime = 0;

void savesreg() {
	if (OPTFLAG) {
		for (int i = 0; i < 8; i++) {
			rsT << "\t\tsw\t$s" << i << "\t" << 4 * i + lstime*32 << "($gp)" << endl;
		}
		lstime++;
	}
}

void loadsreg() {
	if (OPTFLAG) {
		lstime--;
		for (int i = 0; i < 8; i++) {
			rsT << "\t\tlw\t$s" << i << "\t" << 4 * i + lstime*32 << "($gp)" << endl;
		}
		
	}
}

void cnt(char* name) {
	int t = ap - 1;//ap不用更新
	if (name[0] == '+' || name[0] == '-' || (name[0] >= '0'&& name[0] <= '9') || name[0] == ' ' || name[0] == '\t' || name[0] == '\0' || name[0] == '$')
		return;
	while (t >= constedge.back()) {
		if (strcmp(addrtable[t].name, name) == 0 && addrtable[t].kind != AINT && addrtable[t].kind != ACHAR) {
			addrtable[t].cnt++;
			for (int q = 0; q <= cntindex; q++) {
				if (q == cntindex) {			//这个表示走到头了还没找到相应的元素，这时候要定义一个
					cnttable[cntindex].cnt = 1;
					cnttable[cntindex].symbnum = t;		//cnttable[cntindex].symbnum存储在符号表中索引
					cntindex++;
					break;
				}
				if (cnttable[q].symbnum == t) {//在cnttable中找到相应的变量名的位置的count+1
					cnttable[q].cnt++;
					break;
				}
			}
		}
		t--;
	}
}


void ammd(char* oper) {
	int flag = 0;
	int flag2 = 0;
	int reg_no = -1;
	int reg_no2 = -1;
	int reg_no3 = -1;
	if ((reg_no = reg_find_var(midcode[mi].var1)) != -1) {
		flag = 1;
	}
	else {
		if (isdigit(midcode[mi].var1[0]) || midcode[mi].var1[0] == '-' || midcode[mi].var1[0] == '+') {
			rsT << "\t\tli\t$t0\t" << midcode[mi].var1 << endl;
		}
		else {
			mips_find_var(midcode[mi].var1, "lw", "$t0");
		}
	}
	if ((reg_no2 = reg_find_var(midcode[mi].var2)) != -1) {
		flag2 = 1;
	}
	else {
		if (isdigit(midcode[mi].var2[0]) || midcode[mi].var2[0] == '-' || midcode[mi].var2[0] == '+') {
			rsT << "\t\tli\t$t1\t" << midcode[mi].var2 << endl;
		}
		else {
			mips_find_var(midcode[mi].var2, "lw", "$t1");
		}
	}
	//下面是分8种情况考虑
	if (flag == 0 && flag2 == 0) {
		/*if ((reg_no3 = reg_find_var(midcode[mi].var3)) != -1) {
			rsT << "\t\t" << oper << "\t$s" << reg_no3 << "\t$t0\t$t1" << endl;
		}
		else {
			rsT << "\t\t" << oper << "\t$t0\t$t0\t$t1" << endl;
			mips_find_var(midcode[mi].var3, "sw", "$t0");
		}*/
	}
	else if (flag == 1 && flag2 == 0) {
		if ((reg_no3 = reg_find_var(midcode[mi].var3)) != -1) {
			rsT << "\t\t" << oper << "\t$s" << reg_no3 << "\t$s" << reg_no << "\t$t1" << endl;
		}
		else {
			rsT << "\t\t" << oper << "\t$t0\t$s" << reg_no << "\t$t1" << endl;
			mips_find_var(midcode[mi].var3, "sw", "$t0");
		}
	}
	else if (flag == 0 && flag2 == 1) {
		if ((reg_no3 = reg_find_var(midcode[mi].var3)) != -1) {
			rsT << "\t\t" << oper << "\t$s" << reg_no3 << "\t\t0\t$s" << reg_no2 << endl;
		}
		else {
			rsT << "\t\t" << oper << "\t$t0\t$t0\t$s" << reg_no2 << endl;
			mips_find_var(midcode[mi].var3, "sw", "$t0");
		}
	}
	else {
		if ((reg_no3 = reg_find_var(midcode[mi].var3)) != -1) {
			rsT << "\t\t" << oper << "\t$s" << reg_no3 << "\t$s" << reg_no << "\t$s" << reg_no2 << endl;
		}
		else {
			rsT << "\t\t" << oper << "\t$t0\t$s" << reg_no << "\t$s" << reg_no2 << endl;
			mips_find_var(midcode[mi].var3, "sw", "$t0");
		}
	}
}