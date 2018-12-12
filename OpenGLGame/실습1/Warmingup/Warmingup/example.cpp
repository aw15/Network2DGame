#include"stdafx.h":
#include<process.h>

int main()
{
	int ch, i;
	FILE* fp=nullptr;
	char s[] = "test";
	char c = '\n';
	fopen_s(&fp, "c:\\test.txt", "wt");
	
	fprintf(fp, "%s%c", s,c);
	fclose(fp);
	system("type test.txt");
}