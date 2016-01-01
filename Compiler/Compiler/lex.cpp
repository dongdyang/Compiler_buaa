#include "glob.h"
#include "def.h"

//lex.cpp
//while (true) {
//	getsym();
//	if (_stricmp(id.c_str() ,".")==0) {
//		getsym();
//		break;
//	}
//}
//getch();


int prllen;
int ch = ' ';
int line[500], backupline[500];
int lnum = 0, cnum = 0, llen = 0;
int num;
int symid;

string id = "";
string sym;
string prid;

int kwdnum = 21;
//重要说明：INTTK为INTEGER；INTCON为int类型的数字，也就是1223,1，231这样的；同理CHARTK和CHARCON

char *word[] = {
	"array","begin", "char", "const",
	"do","downto", "else", "end",
	"for","function", "ident", "if","integer","of",
	"procedure", "read",
	"then","to", "var",
	"while", "write"
};
char *wsym[] = {
	"ARRAYTK", "BEGINTK", "CHARTK", "CONSTTK",
	"DOTK", "DOWNTK","ELSETK", "ENDTK",
	"FORTK", "FUNCTK", "IDENT","IFTK", "INTTK", "OFTK",
	"PROCETK", "READTK" ,
	"THENTK", "TOTK", "VARTK",
	"WHILETK", "WRITETK"
};

int getsym() {
	prid = id;
	id = "";
	while (isspace(ch) && ch != EOF) {
		getch();
	}
	if (ch == EOF) {
		symid = -1;
		return -1;
	}
	if (isalpha(ch)) {
		//必须要以字母开头
		while (isalpha(ch) || isdigit(ch)) {
			//ch = tolower(ch);
			id += ch;
			getch();
		}
		int i = 0, j = kwdnum - 1, k = 0;
		do {
			k = (i + j) / 2;
			if (_stricmp(id.c_str(), word[k]) <= 0) {
				j = k - 1;
			}
			if (_stricmp(id.c_str(), word[k]) >= 0) {
				i = k + 1;
			}
		} while (i <= j);
		if (i - 1 > j)
		{
			sym = wsym[k];
			symid = k;
		}
		else
		{
			sym = "IDENT";
			symid = IDENT;
		}
	}
	else if (isdigit(ch)) {
		sym = "INTCON";
		symid = INTCON;
		num = 0;
		while (isdigit(ch)) {
			id += ch;
			num = num * 10 + (int)(ch - '0');
			getch();
		}
		//数字超过范围的错误
	}
	else if (ch == ':') {
		id += ch;
		getch();
		if (ch == '=')
		{
			id += ch;
			sym = "ASSIGN";
			symid = ASSIGN;
			getch();
		}
		else
		{
			sym = "COLON";
			symid = COLON;
		}
	}
	else if (ch == '<') {
		id += ch;
		getch();
		if (ch == '=') {
			id += ch;
			sym = "LEQ";
			symid = LEQ;
			getch();
		}
		else if (ch == '>') {
			id += ch;
			sym = "NEQ";
			symid = NEQ;
			getch();
		}
		else {
			sym = "LSS";
			symid = LSS;
		}
	}
	else if (ch == '>') {
		id += ch;
		getch();
		if (ch == '=') {
			id += ch;
			sym = "GEQ";
			symid = GEQ;
			getch();
		}
		else {
			sym = "GRE";
			symid = GRE;
		}
	}
	else if (ch == '\"') {
		//注意：此处只输出值得内容，关于“”的判断在此处进行，不输出“”
		string tempstr;
		getch();
		while (ch == 32 || ch == 33 || (ch <= 126 && ch >= 35)) {
			tempstr += ch;
			getch();
		}
		if (ch == '\"') {
			getch();
			sym = "STRCON";
			symid = STRCON;
			id = tempstr;
		}
		else {
			error(DOUBLEQUOTESLACK);
			return -1;
		}
	}
	else if (ch == '\'') {
		//注意：此处只输出值得内容，关于‘’的判断在此处进行，不输出‘’
		getch();
		if (isalnum(ch) || isdigit(ch)) {
			id += ch;
			getch();
		}
		else {
			error(UNACCEPTATLECHAR);
			return -1;
		}
		if (ch == '\'') {
			sym = "CHARCON";
			symid = CHARCON;
			getch();
		}
		else {
			error(SINGLEQUOTESLACK);
			return -1;
		}
	}
	else {
		if (ch == '+') {
			sym = "PLUS";
			symid = PLUS;
		}
		else if (ch == '-') {
			sym = "MINU";
			symid = MINU;
		}
		else if (ch == '*') {
			sym = "MULT";
			symid = MULT;
		}
		else if (ch == '/') {
			sym = "DIV";
			symid = DIV;
		}
		else if (ch == ',') {
			sym = "COMMA";
			symid = COMMA;
		}
		else if (ch == ':') {
			sym = "COLON";
			symid = COLON;
		}
		else if (ch == ';') {
			sym = "SEMICN";
			symid = SEMICN;
		}
		else if (ch == '[') {
			sym = "LBRACE";
			symid = LBRACK;
		}
		else if (ch == '(') {
			sym = "LPARENT";
			symid = LPARENT;
		}
		else if (ch == ']') {
			sym = "RBRACK";
			symid = RBRACK;
		}
		else if (ch == ')') {
			sym = "RPARENT";
			symid = RPARENT;
		}
		else if (ch == '=') {
			sym = "EQL";
			symid = EQL;
		}
		else if (ch == '.') {
			sym = "PERIOD";
			symid = PERIOD;
		}
		id += ch;
		getch();
	}
	if (!strcmp(sym.c_str(), "INTTK")) {
		lexrst << sym << ' ' << num << endl;
	}
	else {
		lexrst << sym << ' ' << id << endl;
	}
	return 0;
}

void getch() {
	int i = 0;
	prllen = llen;
	if (cnum == llen && ~line[llen]) {
		ch = fgetc(src);
		while (ch == ' ' || ch == '\n' || ch == '\t') {
			if (ch == '\n') {
				lnum++;
			}
			backupline[i++] = ch;  //保存源文件的行，用于发生错误时输出
			ch = fgetc(src);
		}
		//保存过滤掉空白字符后的一行字符
		for (llen = 0; ch != '\n' && ch != EOF; llen++) {
			line[llen] = ch;
			backupline[i++] = ch;   //保存源文件的行，用于发生错误时输出
			ch = fgetc(src);
		}
		if (ch == EOF) {
			line[llen] = EOF;
		}
		else
			line[llen] = '\n';
		backupline[i] = '\0';

		cnum = 0;
		ch = '\n';
		lnum++;
	}
	else {
		ch = line[cnum++];
	}
}