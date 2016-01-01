#include "glob.h"
#include "def.h"
//此处定义是为了方便 因子\赋值
#define INT		1
#define CHAR	2

int		mf = 0;				//类主函数个数
int		value;				//保存常量的值；2对函数来说返回char，1对于函数来说返回为Int，0返回值为void（对应procedure）
int		address;			//变量的地址；函数返回值的地址
int		paranum;			//全局变量，用来处理函数定义，因为函数的参数个数只能在参数表子程序执行结束之后才知道，所以只能在后面才插入符号表信息
int		kind;				//正在处理的标志符的类型
int		returnnum = 0;		//记录是否有返回值
int		hiscnt = 1;			//符号表容量的历史记录
int		factortype = 0;		//因子的类型
int		synlevel = 0;			//当前指针所在函数层数，0表示在最外层

char	name[MAXIDENLEN]=" ";	//标志符的名字，包括常量变量和函数
char	nowitem[200];		//处理表达式的时候用来存当前项
char	procname[100];		//函数、过程名

symtable maintable;

//------------------------------------------------------------------------------------------
void init() {
	for (int i = 0; i < MAXSYMTABLENUM; i++) {
		maintable.element[i].is_return = false;
	}
}

void pushtable(char* name, int kind, int value, int address, int paranum, int isVec) {
	//表是否满
	if (maintable.index >= MAXSYMTABLENUM) {
		error(OUTOFTABLE);
		exit(0);
	}
	//创建索引
	if (kind == FUNCTION|| kind == PROCEDURE) {
		int iter = 1;
		//首先是查看是否重名
		for (iter = 1; iter <= maintable.ftotal; iter++) {
			if (!strcmp(maintable.element[maintable.findextable[iter]].name, name)) {
				error(SYMBOLCONFLICT);
				return;
			}
		}
		maintable.findextable[++maintable.ftotal] = maintable.index;
	}
	else {
		//首先是查看是否重名，函数内部的变量常量不能重名
		for (int iter = maintable.findextable[maintable.ftotal]; iter < maintable.index; iter++) {
			if (!strcmp(maintable.element[iter].name, name)) {
				error(SYMBOLCONFLICT);
				return;
			}
		}
	}
	strcpy(maintable.element[maintable.index].name, name);
	maintable.element[maintable.index].kind = kind;
	maintable.element[maintable.index].value = value;
	maintable.element[maintable.index].address = maintable.index;
	maintable.element[maintable.index].paranum = isVec ? isVec : paranum;
	if (maintable.index <= hiscnt) {
		symtablehis << "------------------------" << endl;
	}
	hiscnt = maintable.index;
	symtablehis << maintable.index << "\t" << name << "\t" << kind << "\t" << value << "\t" << address << "\t" << paranum << "\t" << isVec << endl;
	maintable.index++;
}

void flushst() {
	int x = maintable.index - 1;
	int y;
	while ((
		maintable.element[x].kind == CINT	|| 
		maintable.element[x].kind == CCHAR	|| 
		maintable.element[x].kind == AINT	||
		maintable.element[x].kind == ACHAR	||
		maintable.element[x].kind == VINT	||
		maintable.element[x].kind == VCHAR	||
		maintable.element[x].kind == PARA) 
		&& 
		strcmp(maintable.element[x].name, procname) 
		!= 0) {
		maintable.element[x].kind = 0;
		maintable.element[x].address = 0;
		maintable.element[x].paranum = 0;
		maintable.element[x].value = 0;
		y = 0;
		while (y < 30)
			maintable.element[x].name[y++] = '\0';
		x--;
	}
	maintable.findextable[maintable.ftotal] = 0;
	maintable.ftotal--;
	maintable.index = x + 1;
	return;
}

int searchst(char* name, int flag, int flag2 ) { 
	int n;
	if (flag == 1) {
		n = maintable.index;
		while (n >= 0) {
			if (strcmp(maintable.element[n].name, name) == 0 && (
				maintable.element[n].kind == FUNCTION || maintable.element[n].kind == PROCEDURE))
				break;
			n--;
		}
		if (n < 0 ) {
			return -1 * FUNCTIONNOTFOUND;
		}
		return maintable.element[n].address;
	}
	else {
		n = maintable.index - 1;
		while (n >= 0 ) {
			if (strcmp(maintable.element[n].name, name) == 0)
				break;
			n--;
		}
		if (n < 0) {
			return -1;
		}

		//如果检索到的是参数的，则将参数的相对地址返回，此处相对地址为在符号表中的栈的位置
		if (maintable.element[n].kind == CINT
			|| maintable.element[n].kind == CCHAR
			|| maintable.element[n].kind == AINT
			|| maintable.element[n].kind == ACHAR
			|| maintable.element[n].kind == VINT
			|| maintable.element[n].kind == VCHAR
			|| maintable.element[n].kind == PARA)
			return maintable.element[n].address;

		return -1;
	}
}

//查找数组定义的长度
int arrnum(char *name) {
	int n = maintable.index-1;
	//查找符号表中是否有
	while (n >= 0) {
		if (strcmp(maintable.element[n].name, name) == 0)
			return maintable.element[n].paranum;
		n--;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------------------
//checked
//1.<程序> :: =   <分程序>.
void wprogram() {
	init();
	getsym();
	program();
	if (symid != PERIOD) {
		error(PERIODLACK, 0);
	}
}
vector<char*>	tmpfuncname;

//2.<分程序> ::=   [<常量说明部分>][<变量说明部分>]{[<过程说明部分>]| [<函数说明部分>]}<复合语句>
void program() {
	if (symid == CONSTTK) {
		conststate();
	}
	if (symid == VARTK) {
		varstate();
	}
	
	//进入函数/过程部分
	while (symid == FUNCTK || symid == PROCETK) {
		synlevel++;
		//15.<函数说明部分>  :: = <函数首部><分程序>{ ; <函数首部><分程序> };
		//17.<函数首部>   ::=   function <标识符>[<形式参数表>]: <基本类型>; 
		//18.<形式参数表> :: = '('<形式参数段>{; <形式参数段>}')'
		//19.<形式参数段>:: = [var]<标识符>{, <标识符>}: <基本类型>
		// function f(var a,b,c:integer):integer
		// function f:integer
		// function f(a:integer):integer
		// function f(a,b:integer):char
		// 若是fun1函数结束后还有一个函数func2，那么这里的func1的end后有“；”
		if (symid == FUNCTK) {
			getsym();
			strcpy(name, id.c_str());
			varcnt = 0;     //临时变量重新开始计数
			returnnum = 0;//将是否存在返回值的标记初始化，0表示无返回值，即未出现return
			address = 0;
			paranum = 0;
			strcpy(procname, name);//函数名拷贝
			char tmp_func[MAXIDENLEN] = " ";
			strcpy(tmp_func, name);
			tmpfuncname.push_back(tmp_func);
			getsym();
			/*------预读部分----*/
			int tempid = symid;//恢复现场用
			char tempch = ch;//恢复现场用
			int tempcnum = cnum;//恢复现场用
			if (symid == LPARENT) {
				getsym();
				while (symid != RPARENT) {
					getsym();
				}
				getsym();
			}
			if (symid == COLON) {
				getsym();
			}
			/*
			此处需要超前读
			*/
			kind = FUNCTION;//表示当前的函数是子程序，即非主函数
			//运行至此处的paranum虽然为0，但是在函数参数定义函数执行完后会重新给paranum赋值
			if (symid == INTTK) {
				value = 1;//2对于函数来说没有返回值，也就是procedure；1对于函数来说，表示返回值为Int 0返回值为void
				pushtable(procname, kind, value, address, paranum);
				insmidcode("func", "int", "  ", procname);
			}
			if (symid == CHARTK) {
				value = 2;//2对于函数来说没有返回值，也就是procedure；1对于函数来说，表示返回值为Int 0返回值为void
				pushtable(procname, kind, value, address, paranum);
				insmidcode("func", "char", "  ", procname);
			}

			//恢复预读前现场
			symid = tempid;
			cnum = tempcnum;
			ch = tempch;
			//--------预读结束

			if (symid == LPARENT) {
				getsym();
				parametertable();
				//缺'('＜参数＞')'的右小括号
				if (symid != RPARENT) {
					error(RIGHTPARENTLACK);
					continue;
				}
				getsym();
			}
			if (symid != COLON) {
				error(COLONLACK);
			}
			else {
				getsym();
			}
			if (symid != CHARTK && symid != INTTK) {
				error(RETURNTYPELACK);
			}
			getsym();
			if (symid != SEMICN) {
				error(SEMICOLONLACK, -1);
			}
			else {
				getsym();
			}
			program();
			getsym();
		}
		//14.<过程说明部分>  ::=  <过程首部><分程序>{; <过程首部><分程序>};
		//16.<过程首部>  ::=   procedure<标识符>[<形式参数表>];   //无返回值的可以看成函数
		//18.<形式参数表> :: = '('<形式参数段>{; <形式参数段>}')'
		//19.<形式参数段>:: = [var]<标识符>{, <标识符>}: <基本类型>
		// procedure p(var a,b,c:integer)
		// procedure p(a,b,c:integer)
		// procedure p(a:char)
		// procedure p;
		else if (symid == PROCETK) {
			getsym();
			if (symid != IDENT) {
				error(IDENTIFIERLACK);
				continue;
			}
			varcnt = 0;          //临时变量重新开始计数
			strcpy(name, id.c_str());
			kind = PROCEDURE;
			value = 0;
			address = 0;
			paranum = 0;
			pushtable(name, kind, value, address, paranum);
			strcpy(procname, name);
			char tmp_func[MAXIDENLEN] = " ";
			strcpy(tmp_func, name);
			tmpfuncname.push_back(tmp_func);
			insmidcode("func", "void", "  ", procname);
			getsym();
			if (symid == LPARENT) {
				getsym();
				parametertable();
				//缺'('＜参数＞')'的右小括号
				if (symid != RPARENT) {
					error(RIGHTPARENTLACK);
					continue;
				}
				getsym();
			}
			if (symid != SEMICN) {
				error(SEMICOLONLACK,-1);
			}
			else {
				getsym();
			}
			program();
			if (symid != SEMICN) {
				error(SEMICOLONLACK);
			}
			else {
				getsym();
			}
		}
	}
	while (symid == BEGINTK) {
		//38.<复合语句>  ::=   begin<语句>{; <语句>}end
		//此处不能简单的将其看成是复合语句，使用complexsentence()来递归，此处与一般的复合语句还是不同的
		//复合语句里是没有常量和变量的声明的
		varcnt = 0;        //临时变量重新开始计数
		//这里其实是需要加入一条指令表示函数的开始操作！？
		char* tmp = NULL;
		//strcpy(name, "funcmain");
		if (synlevel == 0) {
			strcpy(name, "main");
			kind = FUNCTION;
			value = 0;
			address = 0;
			paranum = 0;
			mf++; //主函数的个数+1-----------------------
			pushtable(name, kind, value, address, paranum);
			strcpy(procname, name);
			insmidcode("func", "  ", "  ", procname);
			insmidcode("begin", "  ", "  ", "  ");
		}
		else {
			tmp = tmpfuncname.back();
			insmidcode("begin", "  ", "  ",tmp);//这个是为了跳转做标记的
			tmpfuncname.pop_back();
		}
		getsym();
		sentencelist();
		if (symid != ENDTK) {
			error(ENDLACK);
		}
		if(synlevel!=0){
			int s = searchst(tmp,1);
			if (s > 0 && maintable.element[s].kind == FUNCTION) {
				if (!maintable.element[s].is_return) {
					error(NONERETURN);
				}
			}
		}
		flushst();//清除符号表，这里清空的是此子函数的符号表,不清除子函数名
		synlevel--;
		insmidcode("end", "  ", "  "," ");
		strcpy(name, " ");
		getsym();
		if (symid != PERIOD) {
			if (symid != SEMICN) {
				error(SEMICOLONLACK);
			}
		}
	}
	return;    //源程序结束，跳出
}

//3.<常量说明部分> ::=   const<常量定义>{,<常量定义>};
//4.<常量定义>::= <标识符>＝ <常量>
//5.<常量>:: = [+| -] <无符号整数> | <字符>
//6.<字符>::=  '<字母>' | '<数字>'		//常量在定义时只能有一个字母或者数字，由‘’包含起来。
//ATTENTION:在这里会直接读出类型，常量的定义没有给出类型，因此需要根据等式后面的结果来进行判断
//以下三个例子不能同时出现
// const a=123,b=+32,c=-123,d='a',e='8';
// const a=1;
// const a='8';
//该函数调用constdef函数，同时被program调用
void conststate() {
	getsym();//得到const 后面的IDENT
	address = 0;
//	paranum = 0;
	do {
		constdef();
	} while (symid == COMMA);
	if (symid != SEMICN) {
		error(SEMICOLONLACK);
		return;
	}
	getsym();
	return;
}

//4.<常量定义>::= <标识符>＝ <常量>
//5.<常量>:: = [+| -] <无符号整数> | <字符>
//6.<字符>::=  '<字母>' | '<数字>'		//常量在定义时只能有一个字母或者数字，由‘’包含起来。
//ATTENTION:这里不包含int和char, int, 这两者将从tclass传入
//该函数被conststate函数调用
//以下三个例子不能同时出现
// const a=123,b=+32,c=-123,d='a',e='8';
// const a=1;
// const a='8';
//此处解决的是    a=123      b=+32     c=-123    d='a'
void constdef() {
	char temp[200];
	if (symid == COMMA)
		getsym();
	if (symid == IDENT) {
		strcpy(name, id.c_str());
		getsym();
		if (symid == EQL) {
			getsym();
			if (symid == PLUS || symid == MINU) {
				kind = CINT;
				int symb = symid;
				getsym();
				if (symid == INTCON) {
					if (symb == PLUS) {
						value = num;
					}
					else {
						value = 0 - num;
					}
					pushtable(name, kind, value, address, paranum);
					sprintf(temp, "%d", value);
					insmidcode("const", "int", temp, name);
				}
			}
			else if (symid == INTCON) {
				kind = CINT;
				value = num;
				pushtable(name, kind, value, address, paranum);
				sprintf(temp, "%d", value);
				insmidcode("const", "int", temp, name);
			}
			else if (symid == CHARCON) {
				kind = CCHAR;
				value = id.c_str()[0];
				pushtable(name, kind, value, address, paranum);
				sprintf(temp, "%d", value);
				insmidcode("const", "char", temp, name);
			}
			else {
				error(UNKNOWRIGHTSYM);//unknow right sym
				return;
			}
		}
		else {
			error(CONSTNOTINIT);
			return;
		}
	}
	else {
		error(CSTDEFINEFAIL);
	}
	getsym();
	return;
}


//10.<变量说明部分>  ::=   var <变量说明> ; {<变量说明>;}
//11.<变量说明> :: = <标识符>{ , <标识符> } : <类型>
//12.<类型>   :: = <基本类型> | array'['<无符号整数>']' of <基本类型>
/* 例子：
var
	a,a1,a2:integer;
	b:array[100] of integer;
	c:char;
	d:integer;   //<-最后一个变量后有";"
*/
void varstate() {
	getsym();//得到var后面的IDENT
	value = 0;
	address = 0;
	paranum = 0;
	while (symid == IDENT) {
		string *s = new string[100]; //动态分配 针对文法11：100个IDENT定义
		int index = 0;
		s[index++] = id;

		getsym();
		while (symid == COMMA) {
			getsym();
			if (symid != IDENT) {
				error(IDENTIFIERLACK);
				continue;
			}
			s[index++] = id;
			getsym();
		}
		if (symid != COLON) {//不等于 冒号":"
			error(COLONLACK);//跳到integer\char\array,或者直接到分号；
		}
		else {
			getsym();
		}

		if (symid == INTTK) {
			kind = VINT;
			for (int i = 0; i < index; i++) {
				strcpy(name, s[i].c_str());
				pushtable(name, kind, value, address, paranum);
				insmidcode("int", "  ", "  ", name);
			}
			getsym();
		}
		else if (symid == CHARTK) {
			kind = VCHAR;
			for (int i = 0; i < index; i++) {
				strcpy(name, s[i].c_str());
				pushtable(name, kind, value, address, paranum);
				insmidcode("char", "  ", "  ", name);
			}
			getsym();
		}
		else if (symid == ARRAYTK) {
			int tmpnum;
			kind = symid;		//integer | char
			//获得数组大小
			getsym();
			if (symid != LBRACK) {
				error(LBRACKLACK);
			}
			else {
				getsym();
			}
			if (symid != INTCON) {
				error(ARRAYLENGTHLACK);//读到下一个IDNET或者分号
			}
			else {
				tmpnum = num;
				getsym();
				if (symid != RBRACK) {
					error(RIGHTBRACKLACK, 2);
				}
				else {
					getsym();
				}
				if (symid != OFTK) {
					error(DOLACK);
				}else{
					getsym();
				}
				if (symid == CHARTK) {
					kind = ACHAR;
				}
				else {
					kind = AINT;
				}
				for (int i = 0; i < index; i++) {
					strcpy(name, s[i].c_str());
					pushtable(name, kind, value, address, paranum, tmpnum);
					if (kind == AINT)
						insmidcode("inta", 0, num, name);
					else if (kind == ACHAR)
						insmidcode("chara", 0, num, name);
					getsym();
				}
			}
		}
		if (symid != SEMICN) {
			error(SEMICOLONLACK, 2);
		}
		else {
			getsym();
		}
	}
	if (symid == CONSTTK) {
		errnum++;
		printf("Error %d: Line %d, 常量定义位置错误！\n", errnum, lnum);
		conststate();
	}
}

//18.<形式参数表> :: = '('<形式参数段>{; <形式参数段>}')'
//19.<形式参数段>:: = [var]<标识符>{, <标识符>}: <基本类型>
//此处考虑"("、")"之间的所有内容
// function f(var a,b,c:integer):integer
// function f:integer
// function f(a:integer;var b,c:char;d:integer):integer
// function f(a,b:integer):char
// procedure p(var a,b,c:integer)
// procedure p(a,b,c:integer)
// procedure p(a:char)
// procedure p;
void parametertable() {
	int pi;		//记录(a:integer;var b,c:char;d:integer)变量在；后的i的初始位置
	int i = 0;		//记录参数个数
	while (symid == VARTK || symid == IDENT) {
		pi = i;
		int var_flag = 0;
		string *s = new string[100];				//动态分配 针对文法11：100个IDENT定义
		if (symid == VARTK) {
			var_flag = 1;
			getsym();
		}
		do {
			if (symid == COMMA)
				getsym();
			if (symid != IDENT) {
				error(IDENTIFIERLACK, 4);
			}
			else {
				s[i++] = id;
				getsym();
			}
		} while (symid == COMMA);
		if (symid != COLON) {
			error(COLONLACK);
		}
		else {
			getsym();
		}
		if (symid == INTTK || symid == CHARTK) {
			kind = PARA;			//4表示为函数参数
			value = 0;
			paranum = 0;
			for (int j = pi; j < i; j++) {
				address = j;							//地址为j，即参数的位置，地址全部为相对地址
				strcpy(name, s[j].c_str());
				pushtable(name, kind, value, address, paranum);						//将行数参数插入符号表
				if(var_flag==1){
					if (symid == INTTK) insmidcode("para", "int", "var", name);
					else if (symid == CHARTK) insmidcode("para", "char", "var", name);
				}
				else {
					if (symid == INTTK) insmidcode("para", "int", "  ", name);
					else if (symid == CHARTK) insmidcode("para", "char", "  ", name);
				}
			}
			getsym();
		}
		if (symid == SEMICN) {
			getsym();
			continue;
		}
		break;
	}
	paranum = i;//当前的参数个数
	maintable.element[maintable.findextable[maintable.ftotal]].paranum = paranum;//插入函数参数个数信息
	return;
}

//38.<复合语句>  ::=   begin<语句>{; <语句>}end
//20.<语句>  ::=   <赋值语句>|<条件语句>|<当循环语句>|<过程调用语句>|<复合语句>|<读语句>|
//					<写语句>|<for循环语句>|<空>
void complexsentence() {
	if (symid != BEGINTK) {
		error(BEGINLACK);
	}
	else {
		getsym();
	}
	sentencelist();
	if (symid != ENDTK) {
		error(ENDLACK);
	}
	getsym();
	return;//end后正常是";"或者"."
}

//20.<语句>  ::=   <赋值语句>|<条件语句>|<当循环语句>|<过程调用语句>|<复合语句>|<读语句>|<写语句>|<for循环语句>|<空>
//21.<赋值语句>  ::=  <标识符> := <表达式>| <函数标识符> := <表达式> | <标识符>'['<表达式>']':= <表达式>
//33.<条件语句> :: = if<条件>then<语句> | if<条件>then<语句>else<语句>
//35.<当循环语句>::=   do<语句> while<条件>
//37.<过程调用语句>  :: = <标识符>[<实在参数表>]
//38.<复合语句>  :: = begin<语句>{ ; <语句> }end
//39.<读语句>  :: = read'('<标识符>{, <标识符>}')'
//40.<写语句>  :: = write'('<字符串>, <表达式>')' | write'('<字符串>')' | write'('<表达式>')'
//36.<for循环语句> :: = for <标识符>  : = <表达式> （downto | to） <表达式> do <语句> //步长为1

void sentencelist() {
	bool flag = false;
	do {
		if (flag && symid != SEMICN) {
			error(SEMICOLONLACK);
		}
		else {
			if (symid == SEMICN)
				getsym();
		}
		sentence();
		flag = true;
	} while (symid == IDENT || symid == IFTK || symid == DOTK || symid == BEGINTK
		|| symid == READTK || symid == WRITETK || symid == FORTK || symid == SEMICN );
}

//checked!
//33.<条件语句> :: = if<条件>then<语句> | if<条件>then<语句>else<语句>
//31.<条件>  ::=   <表达式><关系运算符><表达式>
// if a>0 then
void ifsentence()
{
	char label1[10], label2[10], conditionvalue[30];
	strcpy(label1, nextlab());  //如果不满足if，则跳过label1，label1是if的结束部分
	strcpy(label2, nextlab());  //如果还有else，则else的结束位置是label2
	getsym();
	//＜条件＞
	condition();
	strcpy(conditionvalue, nowitem);  //条件计算的值在nowitem里面,此处应该是个临时变量$_x
	insmidcode("jne", "  ", "  ", label1);  //比较，为假的时候跳转
	if (symid != THENTK) {
		error(KEYWORDERROR, 4);
	}
	else {
		getsym();
	}
	sentence();
	insmidcode("jmp", "  ", "  ", label2);//不执行else的部分
	insmidcode("lab:", "  ", "  ", label1);
	if (symid != ELSETK) {
		insmidcode("lab:", "  ", "  ", label2);
		return;
	}
	else {
		getsym();
		sentence();
		insmidcode("lab:", "  ", "  ", label2);
		return;
	}
}

//checked
//31.<条件>  ::=   <表达式><关系运算符><表达式>
//32.<关系运算符>  :: = < | <= | > | >= |= | <>
void condition()
{
	char place1[30], place2[30];
	expression();
	strcpy(place1, nowitem);  //条件至少有一个表达式
	if (symid == LSS || symid == LEQ || symid == GRE || symid == GEQ || symid == NEQ || symid == EQL) {
		if (symid == LSS) {
			getsym();
			expression();
			strcpy(place2, nowitem);
			insmidcode("<", place1, place2, "  ");
		}
		else if (symid == LEQ) {
			getsym();
			expression();
			strcpy(place2, nowitem);
			insmidcode("<=", place1, place2, "  ");
		}
		else if (symid == GRE) {
			getsym();
			expression();
			strcpy(place2, nowitem);
			insmidcode(">", place1, place2, "  ");
		}
		else if (symid == GEQ) {
			getsym();
			expression();
			strcpy(place2, nowitem);
			insmidcode(">=", place1, place2, "  ");
		}  
		else if (symid == NEQ) {
			getsym();
			expression();
			strcpy(place2, nowitem);
			insmidcode("<>", place1, place2, "  ");
		}
		else if (symid == EQL) {
			getsym();
			expression();
			strcpy(place2, nowitem);
			insmidcode("==", place1, place2, "  ");
		}
	}
	else {
		error(UNKNOWNOPRRATOR);
	}
	return;
}

//checked
//23.<表达式>  :: = [+| -]<项>{<加法运算符><项>}
void expression()
{
	char place1[30], place2[30], place3[30];
	if (symid == PLUS || symid == MINU) {
		factortype = INT;
		if (symid == PLUS) {
			getsym();
			item();//项，结束后，项的结果会放入全局变量nowitem
			strcpy(place3, nowitem);//把项的结果放入临时变量的位置
		}
		if (symid == MINU) {
			getsym();
			item();//项
			strcpy(place1, nowitem);
			strcpy(place3, nextvar());
			insmidcode("-", "0 ", place1, place3); //place3 = 0 - (place1)
		}
	}
	else {
		item();
		strcpy(place3, nowitem);
	}
	while (symid == PLUS || symid == MINU) {
		factortype = INT;
		strcpy(place1, place3);
		if (symid == PLUS) {
			getsym();
			item();
			strcpy(place2, nowitem);
			strcpy(place3, nextvar());
			insmidcode("+", place1, place2, place3);//place3=place1+place2
			continue;
		}
		else {
			getsym();
			item();
			strcpy(place2, nowitem);
			strcpy(place3, nextvar());
			insmidcode("-", place1, place2, place3);
			continue;
		}
	}
	strcpy(nowitem, place3);//把表达式的最终值存放在p之中 
	return;
}

//	35|36.<循环语句>
void loopsentence()
{
	int s = 0;
	char names[30] ;// names1[30],names2[30],place2[30], place3[30]
	char label1[10], label2[10];// op_flag[5];
	strcpy(label1, nextlab());
	strcpy(label2, nextlab());

	//35.<当循环语句>::=   do<语句> while<条件>
	if (symid == DOTK) {
		getsym();
		insmidcode("lab:", "  ", "  ", label1);
		sentence();
		//getsym();
		if (symid != WHILETK) {
			//error
		}
		else {
			getsym();
		}
		condition();
		insmidcode("jne", "  ", "  ", label2);
		insmidcode("jmp", "  ", "  ", label1);
		insmidcode("lab:", "  ", "  ", label2);
		return;
	}
	//36.<for循环语句> :: = for <标识符>  : = <表达式> （downto | to） <表达式> do <语句> //步长为1
	//调用表达式：	expression() 
	//调用语句：	sentence()
	if (symid == FORTK) {
		char item1[200];
		char item2[200];
		getsym();
		char ident[20];
		if (symid != IDENT) {
			error(UNACCEPTABLESENTENCE);//不合法的句子
			return;
		}
		strcpy(names, id.c_str());
		strcpy(ident, id.c_str());
		getsym();
		if (symid != ASSIGN) {
			error(UNACCEPTABLESENTENCE);
			return;
		}
		s = searchst(names, 0);
		if (s < 0) {     //如果是常量
			if (s == -1) error(VARNOTDEFINE, 1);  //"="左边是不合法的标识符
			else    error(ASSIGNCONST);
			return;
		}
		getsym();
		expression();//checked
		strcpy(item1, nowitem);
		int updown = symid;
		getsym();
		expression();//checked
		strcpy(item2, nowitem);
		if (updown == DOWNTK) {
			insmidcode(">=", item1, item2, "  ");
		}
		else {
			insmidcode("<=", item1, item2, "  ");
		}
		insmidcode("jne", "  ", "  ", label2);
		insmidcode("=", item1, "  ", names);
		insmidcode("lab:", "  ", "  ", label1);
		if (updown == DOWNTK) {
			insmidcode(">=", ident, item2, "  ");
		}
		else if (updown==TOTK){
			insmidcode("<=", ident, item2, "  ");
		}
		else {
			error(DOWNTOLACK);
		}
		insmidcode("jne", "  ", "  ", label2);
		if (symid != DOTK) {
			error(DOLACK);
		}
		else {
			getsym();
		}
		sentence();

		if (updown == DOWNTK) {
			insmidcode(">", ident, item2, "  ");
		}
		else {
			insmidcode("<", ident, item2, "  ");
		}
		insmidcode("jne", "  ", "  ", label2);

		if (updown == DOWNTK) {
			char*  tmp = nextvar();
			insmidcode("-", ident, "1", tmp);
			insmidcode("=", tmp, "  ", ident);
		}
		else {
			char*  tmp = nextvar();
			insmidcode("+", ident, "1", tmp);
			insmidcode("=", tmp, "  ", ident);
		}
		insmidcode("jmp", "  ", "  ", label1);
		insmidcode("lab:", "  ", "  ", label2);
		return;
	}
}



//checked
//<赋值语句>  <过程调用语句>
//21.<赋值语句>  ::=  <标识符> := <表达式>| <函数标识符> := <表达式> | <标识符>'['<表达式>']':= <表达式>
//37.<过程调用语句>  ::=  <标识符>[<实在参数表>]
//27.<实在参数表> ::= '(' <实在参数> {, <实在参数>}')'
void assignsentence() {
	//ident是此刻的symbol
	int s;
	int isVec = 0;
	char names[MAXIDENLEN];
	strcpy(names, id.c_str());	
	getsym();
	/*
	＜赋值语句＞;
	21.<赋值语句>  ::=  <标识符> := <表达式>| <函数标识符> : = <表达式> | <标识符>'['<表达式>']':= <表达式>
	赋值语句后没有分号
	*/
	char place2[100];
	int flagL_A = 0;//LBRACK(if) to ASSIGN(if) 

	//这一部分处理等号左边的部分
	if (symid == LBRACK) { //如果是数组
		s = searchst(names, 0);
		if (s == -1)
		{
			error(VARNOTDEFINE, 1);
			return;
		}else if (s < -1) {
			s = -s / 2;
		}
		if (maintable.element[s].kind != AINT && maintable.element[s].kind != ACHAR) {
			error(ARRAYLACK);
		}
		getsym();
		expression();
		strcpy(place2, nowitem);
		if (isdigit(nowitem[0])) {
			int arrnums = 0;
			arrnums = arrnum(names);
			if (atoi(nowitem) >= arrnums) {
				printf("Warning: Line:%d index of array out of boundary, which should be less than %d.\n", lnum, atoi(nowitem));
			}
		}
		isVec = 1;
		if (symid != RBRACK) {
			error(RIGHTBRACKLACK, 1);
			return;
		}
		getsym();
		flagL_A = 1;
	}
	if (symid == ASSIGN) {
		//此处不能为else if，因为上一个if结束后，可能会进行进入这个if
		//符号表函数部分应该要存函数返回值的个数,且函数只能有一个返回值,返回值后不能再跟函数体的别的内容
		//<函数标识符> :: = <表达式>     
		//23.<表达式>  :: = [+| -]<项>{<加法运算符><项>}
		//-----------------------------函数返回值处理结束，下面是正常的赋值处理
		int t = searchst(names, 1); 
		if (t < 0) {
			//普通的赋值
			s = searchst(names, 0);
			if (s < -1) {						//如果是常量
				error(ASSIGNCONST);				//"="左边是不合法的标识符
				return;
			}
			getsym();
			expression();
			char place3[30];
			strcpy(place3, nowitem);
			//=, 2, , temp			temp = 2;
			//[]=, a, i, t			a[i] = t;
			if (isVec) {
				insmidcode("[]=", names, place2, place3);
			}
			else {
				insmidcode("=", nowitem, "  ", names);
			}
			return;
		}
		else {
			
			//没有做检查

			maintable.element[t].is_return = true;
			getsym();
			expression();
			char place3[30];
			strcpy(place3, nowitem);
			insmidcode("ret", "  ", "  ", place3);
			return;
		}
	}
	//37.<过程调用语句>  ::=  <标识符>[<实在参数表>]
	//27.<实在参数表> ::= '(' <实在参数> {, <实在参数>}')'
	//28.<实在参数> ::=   <表达式> 
	//说明：最后一个函数的函数调用语句没有分号"；",也可以有
	if (symid == LPARENT) {
		//37.<过程调用语句>  ::=  <标识符>[<实在参数表>]
		//27.<实在参数表> ::= '(' <实在参数> {, <实在参数>}')'
		//28.<实在参数> ::=   <表达式> 
		getsym();
		valueofpara();  //计算并记录参数的值以及个数
		if (symid != RPARENT) {
			error(RIGHTPARENTLACK, 1);
			return;
		}
		s = searchst(names, 1);
		if (s == -1 * FUNCTIONNOTFOUND) {
			error(FUNCTIONNOTFOUND);
			return;
		}
		if (s >= 0) {
			//如果函数的实参个数与形参个数不匹配
			if (maintable.element[s].paranum != paranum) {
				error(FORMALPARANUMUNMATCH);
				getsym();
			}
			insmidcode("call", names, "  ", "  ");
			int presym = symid;
			getsym();
			if (symid != ENDTK) {
				if (symid != SEMICN) {
					error(SEMICOLONLACK, -1);
				}
			}
		}
	}
	else {
		//此处默认单个标识符的为函数调用
		s = searchst(names, 1);
		if (s == -1 * FUNCTIONNOTFOUND) {
			error(FUNCTIONNOTFOUND);
			return;
		}
		if (s >= 0) {
			if (maintable.element[s].paranum != 0) {
				error(FORMALPARANUMUNMATCH);
				getsym();
			}
			insmidcode("call", names, "  ", "  ");
			int presym = symid;
		}
		else {
			error(UNKNOWN);
		}
	}
	return;
}

//20.<语句>  :: = <赋值语句> | <条件语句> | <当循环语句> | <过程调用语句> 
//					| <复合语句> | <读语句> | <写语句> | <for循环语句> | <空>
void sentence() {

	if (symid == BEGINTK) {
		complexsentence();
		return;
	}
	//条件语句
	if (symid == IFTK) {
		ifsentence();
		return;
	}
	//循环语句
	if (symid == DOTK || symid == FORTK) {
		loopsentence();
		return;
	}

	//<赋值语句>  <过程调用语句>
	//21.<赋值语句>  ::=  <标识符> := <表达式>| <函数标识符> := <表达式> | <标识符>'['<表达式>']':= <表达式>
	//37.<过程调用语句>  ::=  <标识符>[<实在参数表>]
	//27.<实在参数表> ::= '(' <实在参数> {, <实在参数>}')'
	if (symid == IDENT) {
		assignsentence();
		return;
	}

	//读语句
	//39.<读语句>  :: = read'('<标识符>{, <标识符>}')'
	if (symid == READTK) {
		readsentence();
		return;
	}

	//写语句
	if (symid == WRITETK) {
		writesentence();
		return;
	}

	//空语句
	if (symid == SEMICN || symid == ENDTK ) {
		return;
	}
	//不合法的句子
	error(UNACCEPTABLESENTENCE);
	return;
}

//checked
//26.<函数调用语句> :: = <标识符>[<实在参数表>]
//27.<实在参数表> :: = '(' <实在参数> {, <实在参数>}')'
//28.<实在参数> :: = <表达式>
//23.<表达式>  ::=   [+|-]<项>{<加法运算符><项>}
//24.<项>  :: = <因子>{ <乘法运算符><因子> }
//25.<因子>:: = <标识符> | <标识符>'['<表达式>']' | <无符号整数> | '('<表达式>')' | <函数调用语句>
void valueofpara()
{
	int j = 0;
	vector<string> paraqueue;
	bool flag = false;
	do {
		if (flag && symid != COMMA) {
			error(COMMALACK);
		}
		else {
			if (symid == COMMA) {
				getsym();
			}
		}
		if (symid == PLUS || symid == MINU || symid == IDENT || symid == LPARENT || symid == CHARCON || symid == INTCON) {
			expression();
			paraqueue.push_back(nowitem);
			flag = true;
			j++;
		}
		else {
			error(UNKNOWN);
		}
	} while (symid == COMMA);
	char tc[20];
	for (int i = 0; i <(int) paraqueue.size(); i++) {
		strcpy(tc, paraqueue[i].c_str());
		insmidcode("fupa", "  ", "  ", tc);//function parameters
	}
	paranum = j;
	paraqueue.~vector();
	return;
}

//checked
//39.<读语句>  ::=   read'('<标识符>{,<标识符>}')'
//9.<标识符> ::=   <字母>{<字母>|<数字>}
void readsentence()
{
	char names[30];
	int s;
	getsym();
	if (symid != LPARENT) {
		error(LEFTPARENTLACK, 1);
		return;
	}
	bool flag = false;
	do {
		if (flag && symid != COMMA) {
			error(COMMALACK);
		}
		getsym();
		if (symid != IDENT) {
			error(IDENTIFIERLACK, 3);         //不合法的标志符
			return;
		}
		strcpy(names, id.c_str());
		s = searchst(names, 0);
		if (s < 0) {
			if (s == -1)
				error(VARNOTDEFINE, 1);            //未定义标志符
			else
				error(ASSIGNCONST, 1);
			return;
		}
		else {
			insmidcode("rd", "  ", "  ", names);
			flag = true;
			getsym();
		}
	} while (symid == COMMA);

	if (symid != RPARENT) {
		error(RIGHTPARENTLACK, 1);
		return;
	}
	getsym();
	return;
}

//checked
//40.<写语句>  ::=   write'('<字符串>,<表达式>')'|write'('<字符串>')'|write'('<表达式>')'
void writesentence()
{
	char place1[200] = "", place2[30] = ""; //place1是字符串，place2是表达式
	getsym();
	if (symid != LPARENT) {
		error(LEFTPARENTLACK, 1);
		return;
	}
	getsym();
	if (symid == STRCON) {
		strcpy(place1, id.c_str());
		getsym();
		if (symid == COMMA) {
			getsym();
			expression();
			strcpy(place2, nowitem);
		}
	}
	else {
		expression();
		strcpy(place2, nowitem);
	}
	if (symid != RPARENT) {
		error(RIGHTPARENTLACK, 1);
		return;
	}
	insmidcode("wt", place1, place2, (factortype == CHAR) ? "char" : "int");
	getsym();
	return;
}

//checked
//24.<项>  :: = <因子>{ <乘法运算符><因子> }
void item()
{
	char place1[200], place2[200], place3[200];
	factor();
	strcpy(place3, nowitem);//这种操作是为了对付只有赋值的情况
	while (symid == MULT || symid == DIV) {
		factortype = INT;
		strcpy(place1, place3);
		if (symid == MULT) {
			getsym();
			factor();
			strcpy(place2, nowitem);
			strcpy(place3, nextvar());//申请临时变量
			insmidcode("*", place1, place2, place3);
			continue;
		}
		if (symid == DIV) {
			getsym();
			factor();
			strcpy(place2, nowitem);
			strcpy(place3, nextvar());
			if (strcmp(place2, "0") == 0) {
				error(DIVIDEZERO);
			}
			insmidcode("/", place1, place2, place3);
			continue;
		}
	}
	strcpy(nowitem, place3);  //每一个项，计算后的值都在变量nowitem里面
	return;
}

//25.<因子>:: = <标识符> | <标识符>'['<表达式>']'| <无符号整数> | '('<表达式>')'| <函数调用语句>
//8.<无符号整数>::=   <数字>{<数字>}
void factor()
{
	char names[30], place3[30];
	//<标识符> | <标识符>'['<表达式>']'|<函数调用语句>
	if (symid == IDENT) {
		strcpy(names, id.c_str());
		getsym();
		//函数调用可以有左括号也可以没有左括号！！！
		//call, f, , a			a = f(...)
		//call, f, ,			a = f

		if (symid == LPARENT) {//解决有参数的函数调用问题
			getsym();
			valueofpara();
			if (symid != RPARENT) {
				error(LEFTPARENTLACK, 2);
				return;
			}
			int t = searchst(names, 1);
			if (t < 0) {
				if (t == -1 * FUNCTIONRETURNNULL)
					error(FUNCTIONRETURNNULL);					//函数无返回值，不能出现在表达式中	
				else if (t == -1 * FUNCTIONNOTFOUND)
					error(FUNCTIONNOTFOUND, 1);
				return;
			}

			if (maintable.element[t].paranum != paranum) {
				error(FORMALPARANUMUNMATCH);
				getsym();
			}

			strcpy(place3, nextvar());//生成临时变量
			insmidcode("call", names, "  ", place3);//将调用的返回值存放在临时变量里面
			strcpy(nowitem, place3);
			getsym();
			return;
		}
		else if (symid != LBRACK) {
			//解决单个字符，判断普通标识符和函数标识符的问题
			int t1, t2;
			t1 = searchst(names, 0);				//查表，查找到标识符对应的地址,常量或变量
			t2 = searchst(names, 1);				//查函数名是否存在
			strcpy(nowitem, names);

			if (t1 >= 0) {
				strcpy(nowitem, names);
				return;
			}
			else if (t2 > 0) {
				strcpy(place3, nextvar());//生成临时变量
				insmidcode("call", names, "  ", place3);//将调用的返回值存放在临时变量里面
				strcpy(nowitem, place3);
				return;
			}
			else {
				error(VARNOTDEFINE);
			}
		}
		if (symid == LBRACK) {      //解决是数组的问题
			getsym();
			int tmptype = factortype;
			expression();
			factortype = tmptype;
			char tmp[30];
			strcpy(tmp, nowitem);

			if (isdigit(nowitem[0])) {
				int arrnums = 0;
				arrnums = arrnum(names);
				if (atoi(tmp) >= arrnums) {
					printf("warning: Line:%d index of array out of boundary, which should be less than %d.\n", lnum, atoi(tmp));
				}
			}
			if (symid != RBRACK) {
				error(RIGHTBRACKLACK);
				return;
			}
			else {
				strcpy(nowitem, nextvar());
				insmidcode("geta", names, tmp, nowitem);
				getsym();
			}
		}
		return;
	}

	//'('<表达式>')'
	//23.<表达式>  :: = [+| -]<项>{<加法运算符><项>}
	if (symid == LPARENT) {
		getsym();
		expression();
		if (symid != RPARENT) {
			error(RIGHTPARENTLACK, 2);
			return;
		}
		getsym();
		return;
	}

	//<无符号整数> 
	//8.<无符号整数>::=   <数字>{<数字>}
	if (symid == INTCON) {
		sprintf(nowitem, "%d", 1 * num);
		factortype = INT;
		getsym();
		return;
	}
	error(EXPRESSIONERROR);                  //表达式缺失或错误
	return;
}