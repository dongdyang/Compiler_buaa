#pragma once
#ifndef compiler_glob_h
#define compiler_glob_h
/*--------------------库文件声明---------------------------*/
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;
/*--------------------全局作用---------------------------*/
extern int constedge;
extern char* itoa(int i);

/*--------------------文件操作---------------------------*/

extern ofstream lexrst, midcoderst, symtablehis, asmrst;
extern FILE* src;											//源文件
#define rsT asmrst

/*--------------------词法分析---------------------------*/
extern void getch();
extern int getsym();

extern int kwdnum ;											//关键字的数目
extern int cnum;											//char所从行缓冲区读到的位置的指针
extern int ch ;												//every char
extern string id;											//sym的实际内容
extern string prid;											//前一个标识符的类型
extern int num ;											//存储数字的大小时用
extern int symid;											//标识符id号
extern string sym;											//标识符内容
extern int llen;											//行缓冲技术时指针所指向的位置
extern int prllen;											//前行缓冲技术时指针所指向的位置
extern int line[500];										//行缓冲技术的行
extern int backupline[500];									//错误处理行，行缓冲技术的行
extern int lnum;											//行的数目
extern char *word[];
extern char *wsym[];

/*--------------------符号表-----------------------------*/
/*********
*                  symbol table
*  name    kind    value   address     paranum
*
*
**********/
#define MAXIDENLEN      30
#define MAXSYMTABLENUM  200
//	kind的域
#define CONST       0   //常亮
#define VARIABLE    1   //变量
#define FUNCTION    2   //函数
#define PROCEDURE	22	//过程
#define PARA        3   //参数
#define CINT		4	//常量int类型
#define CCHAR		5	//常量char类型
#define AINT		6	//数组int类型
#define ACHAR		7	//数组char类型
#define VINT		8	//变量int类型
#define VCHAR		9	//变量char类型

//需添加一个标签来区别  函数标识符与普通标识符
typedef struct {
	char name[MAXIDENLEN];  //identifier name
	int kind;               
	int value;              //2对函数来说返回char，1对于函数来说返回为Int，0返回值为void（对应procedure）
	int address;            //记录相对位置
	int paranum;            //参数个数
	bool is_return;
}symb;

typedef struct {
	symb element[MAXSYMTABLENUM];
	int index;							//总的索引
	int ftotal;							//分程序总数
	int findextable[MAXSYMTABLENUM];	//从1开始，分程序索引数组，function index table,用于将函数程序之间区别开来,记录的是function在总的index中的序号，也就是使用“栈”的思想
}symtable;
extern symtable maintable;

extern int  value;						//保存常量的值；对于子程序，0表示void，1表示int
extern int  address;					//变量的地址；函数返回值的地址
extern int  paranum;					//全局变量，用来处理函数定义，因为函数的参数个数只能在参数表子程序执行结束之后才知道，所以只能在后面才插入符号表信息
extern int  kind;						//正在处理的标志符的类型
extern char name[MAXIDENLEN];			//标志符的名字，包括常量变量和函数
extern char nowitem[200];
extern int returnnum;					//记录是否有返回值
extern char procname[100];

/*---------------------语法语义分析-------------------------*/
extern int mf;
void pushtable(char* name, int kind, int value, int address, int paranum, int isVec = 0);
void flushst();
int searchst(char* name, int flag, int flag2 = 0);

void wprogram();
void program();
void conststate();
void constdef();
void varstate();
void parametertable();
void complexsentence();
void sentencelist();
void ifsentence();
void condition();
void expression();
void loopsentence();
void assignsentence();
void sentence();
void valueofpara();
void readsentence();
void writesentence();
void item();
void factor();
int arrnum(char *name);

/*--------------------中间代码四元式----------------------*/
extern void insmidcode(char* op, char* t1, char* t2, char* t3);
extern void insmidcode(char* op, int t1, int t2, char* t3);
extern void insmidcode(char* op, char t1, int t2, char* t3);
char* nextlab();
char* nextvar();

#define MAXMIDCODE 1000
extern int midcodeiter;
extern int labelcnt;
extern int varcnt;

typedef struct {
	char op[10];
	char var1[200];
	char var2[30];
	char var3[30];
}fourvarcode;
extern fourvarcode midcode[MAXMIDCODE];


/*----------------------错误处理--------------------------*/
extern void error(int _errsig, int signal = 0);
extern int errnum;


/*-----------------------汇编----------------------------*/

typedef struct {
	char name[100];
	int level;
}constvarlevel;//变量所在层数
extern constvarlevel cvlevel[1000];
extern int cvl;

typedef struct {
	char name[100];
	int kind;
	int paranum;
	bool isParaVar[20];
	int level;
}funcclass;
extern vector<funcclass> fc;
//函数表

typedef struct {
	char name[100];
	int address;
	int kind;
	int cnt;	
	//int level;
}tempvaraddress;//变量表
extern tempvaraddress addrtable[1000];
//临时变量在栈中的地址表
typedef struct {
	int symbnum;
	int cnt;
}cntstruct;
extern cntstruct cnttable[200];
extern int ap;
extern int mi;
extern int sp;
extern int varreg[200];

int varaddr(char *name);
int findvartable(char *name);
void midcode2asm();
void mips_find_var(char* var, char* inst, char* reg, int type = 0, int addr = 0,int addrtype=0);
void insertaddress(int kind, int addr = -1, int nmi = -1);
void pushstack(char* item = "0", int lenth = 1);
void beginasm();
void inittempvar();
void funcasm();
void dataseg();
void jmpasm();
void printint();
void callasm();
void setlabasm();
void addasm();
void subasm();
void mulasm();
void divasm();
void greasm();
void geqasm();
void lssasm();
void leqasm();
void eqlasm();
void neqasm();
void assasm();
void aassasm();
void assaasm();
void rdasm();
void wtasm();
void fupaasm(int index);
void retasm();
void paraasm();
void jneasm();
void intcharasm();
void constdefasm();
void intcharaasm();
void constvarasm();
void enterfunc();

/*------------------------优化-----------------------*/
#define OPTFLAG 0			//优化开关
extern FILE* optcodefile;
int isconst(char name[]);
void savesreg();
void loadsreg();
void cnt(char * name);
void cntopt();
void printOptimize();
void delsetlab();
void delpublic();
void combine();
void scan();
bool cmpcnt(cntstruct a, cntstruct b);

#endif

/*
系统调用		syscall
取立即数		li $s1, 100			$s1 = 100
加				add s1,s2,$s3		s3=s1+$s2
立即数加		addi s1,s2,100		s3=s1+100
立即数减		subi s1,s2,100		s3=s1-100
减				sub s1,s2,$s3		s3=s1-$s2
乘				mult s2,s3			Hi，Lo=s2?s3
除				div s2,s3			Lo=s2/s3	Hi=s2 mods 3
取字			lw s1,100(s2)		s1=memory[s2+100]
存字			sw s1,100(s2)		memory[s2+100]=s1
beq				beq s1,s2,100		if（s1==s2） goto PC+4+400
bne				beq s1,s2,100		if（$s1！=$s2） goto PC+4+400
slt				slt s1,s2, $s3		if（s2<s3） $s1=1;	else $s1=0;
j				j 2000				goto 8000
jr				ja $ra				goto $ra
jal				jal 2500			$ra=PC+4;goto 10000;
*/

/*
= , 2 , , temp			temp = 2;
[]= , a , i , t			a[i] = t;    数组赋值语句

数组变量声明	
inta, 0, num, name
chara,0, num, name

int , , , a 				int a;
//这个由原来的int, , ,a 更新为int , , ,a, level(所在层数)
//char同理,const也一样
const,int,5 , a			const a = 5;


*,1,10, 
char, , 30, a			var a:array[30] of char;
fupa, , , a				a is a function parameter
call, f , , a			a = f()
call, f , ,				f()
<=, a , b ,				a <= b
<>,
jne , , , lable			if not satisfy(==false) then jump
jmp , , , label			jump to label
lab:, , , labx			set label
geta, a , n , b			b = a[n]
ret , , , (e)			f:=(expression);
wt , a , b , symbol		write("a", b)			symbol存的是b的类型
rd , , , a				read(a)
func,int, , f			start of function f:integer
para,int, , a			f(a:integer; ...)
end , , , ,				end 结束当前函数
lab:, , , label$NO		设定一个label
*/