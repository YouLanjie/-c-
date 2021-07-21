#include "../include/head.h"                              //引用头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	printf("\033[?25l");
	while (1) {
		Clear
		printf("\033[1;33m\033[7;11H1.查看作业\033[7;37H2.编辑、添加作业\033[8;11H3.删除作业\033[8;374.查看帮助\033[9;11H5.退出\033[0m");                   //主页。
		menu("首页菜单",1,1);
		switch (input()) {
			case 0x30:
			case 0x35:
				printf("\033[?25h");
				Clear
				return 0;
				break;
			case 0x31:
				Clear
				rbook();
				break;
			case 0x32:
				Clear
				wbook();
				break;
			case 0x33:
				Clear
				dbook();
				break;
			case 0x34:
				Clear
				help();
				break;
		}
	}
	printf("\033[?25h");
	Clear
	return 0;
}

void rbook() {
	/* 文件指针 */
	FILE *fp;
	/* 保存文件名的连表 */
	struct List *pHead, *pNext, *pEnd, *pTemp;
	/* 文件目录 */
	char b[39]="./";
	/* 文件名 */
	char b2[25];
	/* 文件内容保存and文件名 */
	char f[200];
	int count = 0;
	
	printf("\t\t请选择要查看的作业：\n");
	system("ls ./ > list.txt");
	fp = fopen("list.txt", "r");
	pHead = pNext = pEnd = (struct List *)malloc(sizeof(struct List));
	while (fgets(f, 200, fp) != NULL) {
		count++;
		if (count > 1) {
			pNext = (struct List *)malloc(sizeof(struct List));
		}
		f[strlen(f) -1] = '\n';
		strcpy(pNext -> filename,f);
		pEnd -> pNext = pNext;
		pEnd = pNext;
		if (count > 50) {
			fclose(fp);
			free(pHead);
			printf("内存不足！\n");
			input();
			return;
		}
	}
	fclose(fp);
	remove("list.txt");

	pNext = pHead;
	while (pNext != NULL) {
		puts(pNext -> filename);
		pNext = pNext -> pNext;
	}

	scanf("%s",b2);
	strcat(b,b2);
	
	Clear
	fp = fopen(b,"r");
	if(!fp) {
		perror("\033[1;31m[fopen]\033[0m");
		printf("按下任意键返回");
		input();
		Clear
		return;
	}
	printf("作业内容：\n");
	while (fgets(f, 200, fp) != NULL) {
		fgets(f, 200, fp);
		printf("%s",f);
	}
	printf("\n\n\n");
	fclose(fp);

	printf("按0回到首页：");
	input();
	
	Clear
	return;
}

void wbook()
{
	FILE *books;

	char fbook[150];
	char *f=fbook;
	
	char b[39]="src/file/book/";
	char *p=b;
	char b2[25];
	char *p2=b2;
	
	printf("\t\t请选择要编辑的作业\n");
	system("ls src/file/book");
	printf("\n");
	scanf("%s",p2);
	getchar();                                     //防止gets();函数失效。
	strcat(p,p2);
	
	Clear
	
	if((books=fopen(p,"w"))==NULL)                 //判断是否产生错误。
	{
		printf("\t       错误，无法正常打开文件\n\n");

		sleep(1);

		Clear
		main();                                //防止在发生错误时被强制退出。
		Clear
		return;                                //在系统发出错误警告前关闭程序(自欺欺人)。
	}
	
	printf("请输入：\n");
	while(strcmp(f,"*")!=0)
	{
		scanf("%s",f);
		if(strcmp(f,"*")==0)                   //以"*"符号判断是否结束输入。
		{
			printf("\n\n输入结束！\n");
		}
		else
		{
			fprintf(books,"%s\n",f);
		}
	}
	printf("请输入\"0\"以退出：");
	scanf("%s",f);
	fclose(books);
	Clear
	return;
}

void dbook()
{
	char filename[45];
	char file[50]="src/file/book/";
	
	printf("\t\t请选择要删除的文件：\n");
	system("ls src/file/book");
	printf("\n");
	scanf("%s",filename);
	strcat(file,filename);
	
	Clear
	
	if(remove(file)==0)
	{
		printf("\t\t      删除成功\n");
	}
	else
	{
		printf("\t\t      删除失败\n");
	}
	Clear
	return;
}

void help() {
	printf("                系统帮助\n   tip1:添加作业时只需输入不存在的文件名就可以了。\n   tip2:编辑作业时每换一行就会自动保存。\n   tip3:编辑作业时想退出只需换行后输入符合\"*\"即可。\n   tip3:想要退出系统只需输入数字\"5\"即可。\n");
	getchar();
	return;
}
