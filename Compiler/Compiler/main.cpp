#include "glob.h"
#include "def.h"
//项目->属性->配置属性->C / C++->预处理器->预处理器定义，增加：_CRT_SECURE_NO_DEPRECATE

FILE* optcodefile;
FILE* src;
ofstream lexrst, midcoderst, asmrst, symtablehis;

int main(int argc, char **argv) {
	char filename[500] = "in";
	printf("输入文件名称（默认读取目录下的in.txt文件,若为默认直接回车):\n");
	char tempsrc[500];
	gets_s(tempsrc);//C11标准
	if (strlen(tempsrc) > 2) {
		if (tempsrc[0] == '\"') {
			strcpy_s(filename, tempsrc + 1);
			filename[strlen(filename) - 1] = 0;
		}
		else {
			strcpy_s(filename, tempsrc);
		}
	}
	fopen_s(&src, filename, "r");
	printf("成功读入\n");
	lexrst.open("lexrst");
	midcoderst.open("midcode");
	symtablehis.open("symbolTable");
	asmrst.open("rst.asm");
	if (src == NULL)
	{
		error(NOSUCHFILE);
		system("pause");
		return 0;
	}

	symtablehis << "index name kind value address paranum isVec" << endl;

	wprogram();
	if (mf < 1) error(MAINLACK);
	do  getsym(); while (ch == '\n' || ch == ' ' || ch == '\t');
	if (symid != -1)  error(MOREWORD);
	if (errnum == 0) {
		printf("\n\n编译成功，没有语法语义错误!\n\n");
		//scan();          //扫描四元式结构数组，完成优化
		//printf("优化后的四元式 生成完成...\n");
		midcode2asm();   //生成汇编码
		printf("汇编指令 生成完成...\n");
	}
	lexrst.close();
	midcoderst.close();
	symtablehis.close();
	asmrst.close();
	fclose(src);

	printf("\n-----------------------------\n");
	if (errnum == 0)
	{
		printf("Compile Success.\n");
	}
	printf("Errors:\t%d\tTotal Line: %d\n", errnum, lnum);
	system("pause");
	return 0;
}
