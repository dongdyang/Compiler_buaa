#pragma once
#ifndef compiler_def_h
#define compiler_def_h

/*-----------------------标识符-------------------------*/
//需按字典序来排
#define ARRAYTK		0
#define BEGINTK		1
#define CHARTK		2
#define CONSTTK		3	
#define DOTK		4
#define DOWNTK		5
#define ELSETK		6
#define ENDTK		7
#define FORTK		8
#define FUNCTK		9
#define IDENT       10	
#define IFTK		11
#define INTTK		12
#define OFTK		13
#define PROCETK		14
#define READTK		15
#define THENTK		16
#define TOTK		17
#define VARTK		18
#define WHILETK		19
#define WRITETK		20
//以上为关键字，以下符号不需要按照字典序
#define ASSIGN      21	//:=
#define SEMICN      22	//;
#define COMMA       23	//,
#define STRCON      24	//strcon
#define PLUS        25	//+
#define MINU        26	//-
#define MULT        27	//*
#define PERIOD      28	//.
#define DIV         29	// /
#define COLON       30	//:
#define LSS         31	//<
#define QMARK       32	//' single quotation
#define LEQ         33	//<=
#define DQMARK      34	//"	double
#define GRE         35	//>
#define LPARENT     36	//(
#define GEQ         37	//>=
#define RPARENT     38	//)
#define EQL         39	//=      两个使用场景：1、条件运算的关系运算符，等价于"=="；2、为常数的赋值的等号
#define LBRACK      40	//[
#define NEQ         41	//<>
#define RBRACK      42	//]
#define INTCON		43	//举例：10
#define CHARCON		44	//举例：'a'

/*-----------------------错误类型-------------------------*/
#define NOSUCHFILE				404	//文件不存在
#define FILEINCOMPLETE			0	//文件不完整	
#define DOUBLEQUOTESLACK		1	//双引号缺失
#define UNACCEPTATLECHAR		2	//不可以接受的char
#define SINGLEQUOTESLACK		3	//单引号缺失
#define OUTOFTABLE				4	//符号表
#define SYMBOLCONFLICT			5	//字符串冲突
#define CSTDEFINEFAIL			6   //常量声明失败
#define VARNOTINIT				7   //变量未初始化
#define UNKNOWRIGHTSYM			8   //等号右边字符非法
#define SEMICOLONLACK			9   //丢失“；”
#define KEYWORDERROR			10  //关键字错误
#define IDENTIFIERLACK			11  //丢失标志符
#define RIGHTBRACKLACK			12  //丢失“]”
#define FUNCTIONNOTFOUND		13  //调用函数未定义
#define FORMALPARANUMUNMATCH	14  //形参个数不匹配
#define VARNOTDEFINE			15  //未定义变量
#define LEFTPARENTLACK			16  //丢失“（”
#define RIGHTPARENTLACK			17  //丢失“）”
#define IMMLACK					18  //丢失立即数
#define LBRACKLACK				19	//丢失“[”
#define FUNCTIONRETURNNULL		20  //函数无返回值却被用于参数
#define EXPRESSIONERROR			21  //表达式缺失或错误
#define UNACCEPTABLESENTENCE	22  //句子不合法
#define ASSIGNCONST				23  //给常数赋值
#define OFLACK					24	//缺失of
#define NONERETURN				25  //缺少返回值
#define PLUSMINULACK			26  //缺少‘+’或‘-’
#define MAINLACK				27  //缺少main函数
#define MOREWORD				28  //main函数后面有多余字符
#define CONSTNOTINIT			29  //常量没有初始化
#define PERIODLACK				30	//缺失主程序后的点号"."
#define COLONLACK				31	//缺失：
#define ARRAYLENGTHLACK			32	//数组缺失长度
#define DOLACK					33	//缺失do
#define BEGINLACK				34  //缺失begin
#define ENDLACK					35	//缺失end
#define DIVIDEZERO				36	//除数为0
#define DOWNTOLACK				37	//downto/to缺失
#define COMMALACK				38	//逗号缺失
#define ARRAYLACK				39	//数组元素不存在
#define UNKNOWNOPRRATOR			40	//未定义关系运算符
#define RETURNTYPELACK			41	//函数缺少返回值类型
#define PARANUMZERO				42  //函数（） 内参数个位为0
#define UNKNOWN					50	//未知错误

#define QUIT				1		//直接退出程序
#define DONOTHING			2		//不做任何处理
#define ICA					3		//跳到下一个类型声明符号INTTK/CHARTK/ARRAYTK		
#define DIWFIRWB			4		//跳到下一个以下集合的元素
//{ DOTK IFTK WHILETK FORTK IDENT READTK WRITETK BEGINTK}
#define CS					5		//跳到下一个逗号或者分号
#define CLR					6		//跳到下一个逗号或者括号
#define IWFRSPIFCV			7		//跳到下一个语句列的FIRST集合元素之一
#define IWFIRWE				8		//跳到下一个以下集合的元素：
//{IFTK WHILETK FORTK IDENT READTK WRITETK ELSETK}
#define IWFXXXANE			9		//跳到下一个以下集合的元素：
//{ IFTK WHILETK FORTK IDENT RETURNTK READTK WRITETK SEMICN ELSETK RPARENT COMMA PLUS MINU MULT DIV LSS LEQ GRE GEQ NEQ EQL}
#define	IC					10		//跳到INTCON;


#endif