/*
	��Ŀ�����������V1.1��
	������Ա�� ������
	QQ��1733100391
*/
/* main.c -- ���ڴ���һƪӢ�������г��ִ������ĵ��ʣ�ʹ�õ����ݽṹΪ���� */
/* ��word.cһ�����															*/
#include <stdio.h>
#include <stdlib.h>					/* �ṩexit()ԭ��			*/
#include <windows.h> 				/* �ṩSleep()ԭ��			*/
#include <direct.h>					/* �ṩgetcwd()ԭ��			*/
#include <time.h>
#include <mycon.h>
#include <conio.h>
#include "word.h"					/* ����Lklist��String		*/
#define LEN 200						/* �ļ�������				*/

/*
    ����ԭ�ͣ�char* getcwd(char* buffer, int len);
    ������buffer��ָ����ǰ����Ŀ¼�ľ���·��copy��buffer��ָ���ڴ�ռ䣬 len��buffer�ĳ��ȡ�
    ����ֵ����ȡ�ɹ��򷵻ص�ǰ����Ŀ¼������·������ʧ���򷵻�false����NULL����
    �ú�������ͷ�ļ�Ϊ<direct.h>
*/
void Initialized(String msg);										 				// ��ʼ��
void ShowInterface(String msg);														// չʾ����
void AccessProcessing(FILE *read,FILE *write,FILE *skip,LkList *pList,bool flag);	// ���ڴ����û�����
String GetDirs(String file,int len);
int main (int argc,const char * argv[])
{
	// һ����ʼ��������棬���ر���
	FILE *read,*write,*skip;
	char inputfile[LEN],outputfile[LEN],skipfile[LEN],dirfile[LEN];
	srand(time(NULL));
	LkList list;
	bool flag = true;
	String msg = "���������V1.1��";
	Initialized(msg);
	ShowInterface(msg);

	// ������ȡ��ǰ�ļ�Ŀ¼�����������ó־û��洢���ļ� 
	String dir = getcwd(dirfile,LEN-50);
	if(dir = NULL){
		puts("��ȡ��ǰ����Ŀ¼ʧ�ܣ��˳�ϵͳ��");
		exit(fail);
	}
	strcpy(outputfile,dirfile);
	strcat(outputfile,"\\ͳ�ƽ��.txt");
	strcpy(skipfile,dirfile);
	strcat(skipfile,"\\���ε���.txt");
	 
	// ������ȡ�û�������ļ��������Զ���ȡ��Ҳ�����ֶ������ȡ ������ͨ�������ж�ȡ
	Status s = fail;
	// 1���鿴�Ƿ��������в��� 
	if(argc <= 1){

		// 2��û�������в���������Զ���ȡ�ĵ��� 
		strcpy(inputfile,dirfile);
		strcat(inputfile,"\\Ӣ���ĵ�.txt"); 
		// 3������޷��Զ����ļ����ֶ������ĵ�������ȡ 
		if((read = fopen(inputfile,"rt")) == NULL) {
			puts("\n�Զ���ʧ�ܣ��ļ��������ڵ�ǰĿ¼�����ǲ�֧�ֵĸ�ʽ�����ֶ������ĵ���\n");	
			
			/* �ֶ������ļ��� */
			do {
				puts("\n�������ĵ�����");
				int t = scanf("%150[^ \n]",inputfile);
				if(t) {
					strcat(inputfile,".txt");
					break;
				} else {
					puts("�ļ����������ļ������Ϸ�,����������");
					rewind(stdin);
					continue;
				}
			} while(true);
		} else {
			puts("�Զ���ȡ�ĵ��ɹ���");
			s = success;
			Sleep(2000); 
		}
	} else {
		// 4���������в����ͻ�ȡ�����в�����Ϊ�ļ��� 
		int len = strlen(argv[1]);
		// ���������ļ��� 
		if(len <= 150){
			strcpy(inputfile,argv[1]);
			strcat(inputfile,".txt");
		} else {
			puts("���ĵ�ʧ�ܣ��ļ����������߳��������쳣���˳�����");
			exit(EXIT_FAILURE);
		}		
	}

	// �ġ���Ҫ������ļ��������ձ����ڴ洢��������
	if(List_Initialize(&list) != success) {
		puts("��ʼ�����Ա�ʧ�ܣ������Ƿ����ڴ���ã��˳�����");
		exit(EXIT_FAILURE);
	}	
	// ����Զ���ȡʧ�ܣ������ֶ�������������в��������ļ� 
	if((s==fail) && ((read=fopen(inputfile,"rt"))==NULL)) {
		printf("\n%s��ʧ�ܣ��ļ��������ڵ�ǰĿ¼�����ǲ�֧�ֵĸ�ʽ���˳�����\n",inputfile);
		exit(EXIT_FAILURE);
	} 
	if((write=fopen(outputfile,"wt")) == NULL) {
		printf("\n%s��ʧ�ܣ��ļ��������ڵ�ǰĿ¼�����ǲ�֧�ֵĸ�ʽ���˳�����\n",outputfile);
		exit(EXIT_FAILURE);
	}
	if((skip=fopen(skipfile,"rt")) == NULL) {
		puts("���ε����ı������ڣ��������δ���");
		flag = false;
	}

	// �塢��ȡ���ݲ�������
	AccessProcessing(read,write,skip,&list,flag);

	// �����ر��ļ����ͷ��ڴ�
	if(!List_Destory(&list)) {
		puts("�������Ա�ʧ�ܣ��˳�ϵͳ��");
		exit(EXIT_FAILURE); // exit_failure
	}
	if(fclose(read)) {
		puts("�ļ��ر�ʧ�ܣ���鿴�ļ��Ƿ����");
		exit(EXIT_FAILURE);
	}
	if(fclose(write)) {
		puts("�ļ��ر�ʧ�ܣ���鿴�ļ��Ƿ����");
		exit(EXIT_FAILURE);
	}
	if(flag && fclose(skip)) {
		puts("�ļ��ر�ʧ�ܣ���鿴�ļ��Ƿ����");
		exit(EXIT_FAILURE);
	}

	puts("�ټ�����ӭ�´�ʹ�ñ����\n��������˳����");
	getch();
	return 0;
}

void ShowInterface(String msg)									// չʾ����
{
	puts("��ӭʹ�ñ���������������ͳ��һƪtxt��ʽӢ���ĵ��г��ִ������ĵ���\n");
	Sleep(1000);
	puts("��ܰ��ʾ: �ĵ���Ҫ�ͳ�����ͬһ·���£��ļ�����Ҫ����Ŷ�����������ĵ�����ѽ�");
	puts("���������ǰĿ¼�µ�\"������.txt\"�ļ��У����û����ᴴ��һ���µ��ı��ļ���");
	puts("���ĵ��������������4����ĸ���µļ򵥴ʻ㣬����û����Լ���Ҫ�ֶ����εĵ��ʣ�");
	puts("�����½�һ���ļ����ļ������������ε���.txt����������޷����ҵ����û����ָ����");
	puts("���ļ���ΪӢ���ĵ�.txt���������Զ���ȡ�ĵ��������û��ֶ������ĵ���"); 
	Sleep(2000);
	cls();
	gotoxy(40-strlen(msg)/2,0);
	puts(msg);
	set_color(0,rand()%15+1);
}

void Initialized(String msg)
{
	// ���ò���
	set_title(msg);
	set_size(100,30);
	set_color(0,rand()%15+1);
}
void AccessProcessing(FILE *read,FILE *write,FILE * skip,LkList *pList,bool flag)	// ���ڴ����ļ��е�����
{

	// 1�����ļ��ж�ȡ���ݲ�����������ŵ����Ա���
	puts("\n��ʼ��ȡ�ļ��ʹ���������...");
	ReadFILE(read,pList,false);
	Sleep(2000);
	puts("��ȡ�ļ����������ݳɹ�");
	Sleep(2000);
	// 2����������ı����ڲ�������
	if(flag) {
		ReadFILE(skip,pList,flag);
		puts("���δ�����...");
		Sleep(2000);
	}
	// 3���������򲢽����д����һ���ĵ���
	SelectSort(pList);
	puts("��Ŀ���ļ�д�봦������...");
	WriteFILE(write,*pList);
	Sleep(2000);
	puts("д��ɹ��������˳�����");
}
