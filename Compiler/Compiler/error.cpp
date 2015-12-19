#include "def.h"
#include "glob.h"

int errnum = 0;

void error(int _errsig, int signal) {
	int errtype = -1;
	errnum++;
	printf("error %d: line %d, column %d: near \"%s\" : ",
		errnum, cnum == 0 ? lnum - 1 : lnum, cnum == 0 ? prllen : cnum + 1, prid.c_str());
	//错误类型
	switch (_errsig) {

	case  NOSUCHFILE:				errtype = QUIT;				printf("no such file\n");			break;
	case  FILEINCOMPLETE:			errtype = DONOTHING;		printf("file incomplete\n");		break;
	case  DOUBLEQUOTESLACK:			errtype = DONOTHING;		printf("double quotes lack\n");		break;
	case  UNACCEPTATLECHAR:			errtype = DONOTHING;		printf("unacceptable char\n");		break;
	case  SINGLEQUOTESLACK:			errtype = DONOTHING;		printf("single quotes lack\n");		break;
	case  OUTOFTABLE:				errtype = QUIT;				printf("out of table\n");			break;
	case  SYMBOLCONFLICT:			errtype = DONOTHING;		printf("symbol conflict\n");		break;
	case  CSTDEFINEFAIL:			errtype = CS;				printf("constance define failed\n");    break;
	case  VARNOTINIT:				errtype = DONOTHING;		printf("variant not init\n");			break;
	case  UNKNOWRIGHTSYM:			errtype =
		signal == 0 ? CS :
		signal == 1 ? IWFIRWE :
		-1;
		printf("unknow right symbol\n");				break;
	case  SEMICOLONLACK:			errtype =
		signal == 0 ? DIWFIRWB :
		signal == 1 ? IWFRSPIFCV :
		signal == 2 ? IWFIRWE :
		-1;
		printf("semicolon lack\n");						break;
	case  KEYWORDERROR:
		errtype = signal == 0 ? DIWFIRWB :
			signal == 1 ? CLR :
			signal == 2 ? IWFRSPIFCV :
			printf("keyword error\n");					break;
	case  IDENTIFIERLACK:			errtype =
		signal == 0 ? ICA :
		signal == 1 ? CLR :
		signal == 2 ? IWFRSPIFCV :
		signal == 3 ? IWFIRWE :
		signal == 4 ? IWFXXXANE :
		-1;
		printf("identifier lack\n");					break;
	case  RIGHTBRACKLACK:			errtype =
		signal == 0 ? IWFXXXANE :
		signal == 1 ? IWFRSPIFCV :
		-1;
		printf("right brack lack\n");					break;
	case  FUNCTIONNOTFOUND:			errtype =
		signal == 0 ? IWFIRWE :
		signal == 1 ? IWFXXXANE :
		-1;
		printf("function not found\n");					break;
	case  FORMALPARANUMUNMATCH:		errtype =
		signal == 0 ? DONOTHING :
		signal == 1 ? IWFIRWE :
		-1;
		printf("formal para num unmatch\n");			break;
	case  VARNOTDEFINE:				errtype =
		signal == 0 ? DONOTHING :
		signal == 1 ? IWFIRWE :
		-1;
		printf("var not define\n");						break;
	case  LEFTPARENTLACK:			errtype =
		signal == 0 ? ICA :
		signal == 1 ? IWFIRWE :
		signal == 2 ? IWFXXXANE :
		-1;
		printf("left parent lack\n");					break;
	case  RIGHTPARENTLACK:			errtype =
		signal == 0 ? ICA :
		signal == 1 ? IWFIRWE :
		signal == 2 ? IWFXXXANE :
		-1;
		printf("right parent lack\n");					break;
	case  IMMLACK:					errtype = IWFRSPIFCV;  printf("immediate lack\n");				break;
	case  LBRACKLACK:				errtype = IC;		   printf("left brack lack\n");				break;
	case  FUNCTIONRETURNNULL:		errtype = IWFXXXANE;   printf("function return null\n");		break;
	case  EXPRESSIONERROR:			errtype = IWFXXXANE;   printf("expression error\n");			break;
	case  UNACCEPTABLESENTENCE:		errtype = IWFIRWE;	   printf("unacceptable sentence\n");		break;
	case  ASSIGNCONST:				errtype =
		signal == 0 ? IWFIRWE :
		signal == 1 ? IWFIRWE :
		-1;
		printf("assign const\n");						break;
	//case  RBRACKLACK:				errtype = DONOTHING;	printf("right brack lack\n");			break;
	case  NONERETURN:				errtype = DONOTHING;	printf("none return\n");				break;
	case  PLUSMINULACK:				errtype = IWFIRWE;		printf("+/- lack\n");					break;
	case  MAINLACK:					errtype = DONOTHING;	printf("main lack\n");					break;
	case  MOREWORD:					errtype = DONOTHING;	printf("more word\n");					break;
	case  CONSTNOTINIT:				errtype = CS;			printf("const not init\n");				break;
	case  PERIODLACK:				errtype = DONOTHING;	printf("predix lack\n");				break;
	case  COLONLACK:				errtype = ICA;			printf("colon lack\n");					break;
	case  ARRAYLENGTHLACK:			errtype = CS;			printf("array length lack\n");			break;
	case  OFLACK:					errtype = DONOTHING;	printf("of lack\n");					break;
	case  BEGINLACK:				errtype = DIWFIRWB;		printf("begin lack\n");					break;
	case  ENDLACK:					errtype = DONOTHING;	printf("end lack\n");					break;
	case  DIVIDEZERO:				errtype = DONOTHING;	printf("divide zero\n");				break;
	case  DOWNTOLACK:				errtype = DIWFIRWB;		printf("downto/to lack\n");				break;
	case  DOLACK:					errtype = DIWFIRWB;		printf("do lack\n");					break;
	case  UNKNOWN:					errtype = DONOTHING;	printf("Unknow error occurs!\n"); break;
	case  COMMALACK:				errtype = DONOTHING;	printf("，lack\n");						break;
	case  ARRAYLACK:				errtype = DONOTHING;	printf("array is missing\n");			break;
	case  UNKNOWNOPRRATOR:			errtype = DONOTHING;		printf("unknow relation operator\n");	break;
	case  RETURNTYPELACK:			errtype = DONOTHING;	printf("function lack of return_type\n"); break;
	default:						errtype = QUIT;			printf("Unknow error occurs! [error code: %d]\n", _errsig);
	}

	//错误处理
	switch (errtype) {
	case QUIT:
		system("pause");
		exit(0);
		break;
	case DONOTHING:
		break;
	case ICA:
		while (symid != INTTK && symid != CHARTK && symid != ARRAYTK) {
			if (symid == -1)
			{
				system("pause");    exit(0);
			}
			getsym();
		}
		break;
	case DIWFIRWB:
		//DOTK IFTK WHILETK FORTK IDENT READTK WRITETK BEGINTK
		while (symid!=DOTK && symid != IFTK && symid != FORTK && 
			symid != IDENT && symid != READTK && symid != WRITETK && symid!=BEGINTK) {
			if (symid == -1) { system("pause");    exit(0); }
			getsym();
		}
		break;
	case CS:
		while (symid != COMMA && symid != SEMICN) {
			if (symid == -1) { system("pause");    exit(0); }
			getsym();
		}
		break;
	case CLR:
		while (symid != COMMA && symid != LPARENT && symid != RPARENT) {
			if (symid == -1) { system("pause");    exit(0); }
			getsym();
		}
		break;
	case IWFRSPIFCV:
		while (symid != IFTK && symid != WHILETK && symid != FORTK && symid != READTK
			&& symid != WRITETK && symid != INTTK && symid != CHARTK) {
			if (symid == -1) { system("pause");    exit(0); }
			getsym();
		}
		break;
	case IWFIRWE:
		////{IFTK WHILETK FORTK IDENT READTK WRITETK ELSETK}
		while (symid != IFTK && symid != WHILETK && symid != FORTK && symid != IDENT
			&& symid != READTK && symid != WRITETK && symid != THENTK ) {
			if (symid == -1) { system("pause");    exit(0); }
			getsym();
		}
		break;
	case IWFXXXANE:
		while (symid != IFTK && symid != WHILETK && symid != FORTK && symid != LBRACK && symid != IDENT 
			&& symid != READTK && symid != WRITETK && symid != SEMICN && symid != ELSETK && symid != RPARENT
			&& symid != COMMA && symid != PLUS && symid != MINU && symid != MULT && symid != DIV
			&& symid != LSS && symid != LEQ && symid != GRE && symid != GEQ && symid != NEQ && symid != EQL) {
			if (symid == -1) { system("pause");    exit(0); }
			getsym();
		}
		break;
	case IC:
		while (symid != INTCON) {
			if (symid == -1) { system("pause"); exit(0); }
			getsym();
		}
	default:
		break;
	}

}