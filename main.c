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
   Copyright (c) [Year] [name of copyright holder]
   [Software Name] is licensed under Mulan PSL v2.
   You can use this software according to the terms and conditions of the Mulan PSL v2. 
   You may obtain a copy of Mulan PSL v2 at:
            http://license.coscl.org.cn/MulanPSL2 
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.  
   See the Mulan PSL v2 for more details.  


                     Mulan Permissive Software License��Version 2

   Mulan Permissive Software License��Version 2 (Mulan PSL v2)
   January 2020 http://license.coscl.org.cn/MulanPSL2

   Your reproduction, use, modification and distribution of the Software shall be subject to Mulan PSL v2 (this License) with the following terms and conditions: 
   
   0. Definition
   
      Software means the program and related documents which are licensed under this License and comprise all Contribution(s). 
   
      Contribution means the copyrightable work licensed by a particular Contributor under this License.
   
      Contributor means the Individual or Legal Entity who licenses its copyrightable work under this License.
   
      Legal Entity means the entity making a Contribution and all its Affiliates.
   
      Affiliates means entities that control, are controlled by, or are under common control with the acting entity under this License, ��control�� means direct or indirect ownership of at least fifty percent (50%) of the voting power, capital or other securities of controlled or commonly controlled entity.

   1. Grant of Copyright License

      Subject to the terms and conditions of this License, each Contributor hereby grants to you a perpetual, worldwide, royalty-free, non-exclusive, irrevocable copyright license to reproduce, use, modify, or distribute its Contribution, with modification or not.

   2. Grant of Patent License 

      Subject to the terms and conditions of this License, each Contributor hereby grants to you a perpetual, worldwide, royalty-free, non-exclusive, irrevocable (except for revocation under this Section) patent license to make, have made, use, offer for sale, sell, import or otherwise transfer its Contribution, where such patent license is only limited to the patent claims owned or controlled by such Contributor now or in future which will be necessarily infringed by its Contribution alone, or by combination of the Contribution with the Software to which the Contribution was contributed. The patent license shall not apply to any modification of the Contribution, and any other combination which includes the Contribution. If you or your Affiliates directly or indirectly institute patent litigation (including a cross claim or counterclaim in a litigation) or other patent enforcement activities against any individual or entity by alleging that the Software or any Contribution in it infringes patents, then any patent license granted to you under this License for the Software shall terminate as of the date such litigation or activity is filed or taken.

   3. No Trademark License

      No trademark license is granted to use the trade names, trademarks, service marks, or product names of Contributor, except as required to fulfill notice requirements in Section 4.

   4. Distribution Restriction

      You may distribute the Software in any medium with or without modification, whether in source or executable forms, provided that you provide recipients with a copy of this License and retain copyright, patent, trademark and disclaimer statements in the Software.

   5. Disclaimer of Warranty and Limitation of Liability

      THE SOFTWARE AND CONTRIBUTION IN IT ARE PROVIDED WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED. IN NO EVENT SHALL ANY CONTRIBUTOR OR COPYRIGHT HOLDER BE LIABLE TO YOU FOR ANY DAMAGES, INCLUDING, BUT NOT LIMITED TO ANY DIRECT, OR INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM YOUR USE OR INABILITY TO USE THE SOFTWARE OR THE CONTRIBUTION IN IT, NO MATTER HOW IT��S CAUSED OR BASED ON WHICH LEGAL THEORY, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

   6. Language

      THIS LICENSE IS WRITTEN IN BOTH CHINESE AND ENGLISH, AND THE CHINESE VERSION AND ENGLISH VERSION SHALL HAVE THE SAME LEGAL EFFECT. IN THE CASE OF DIVERGENCE BETWEEN THE CHINESE AND ENGLISH VERSIONS, THE CHINESE VERSION SHALL PREVAIL.

   END OF THE TERMS AND CONDITIONS

   How to Apply the Mulan Permissive Software License��Version 2 (Mulan PSL v2) to Your Software

      To apply the Mulan PSL v2 to your work, for easy identification by recipients, you are suggested to complete following three steps:

      i Fill in the blanks in following statement, including insert your software name, the year of the first publication of your software, and your name identified as the copyright owner; 

      ii Create a file named ��LICENSE�� which contains the whole context of this License in the first directory of your software package;

      iii Attach the statement to the appropriate annotated syntax at the beginning of each source file.


   Copyright (c) [Year] [name of copyright holder]
   [Software Name] is licensed under Mulan PSL v2.
   You can use this software according to the terms and conditions of the Mulan PSL v2. 
   You may obtain a copy of Mulan PSL v2 at:
               http://license.coscl.org.cn/MulanPSL2 
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.  
   See the Mulan PSL v2 for more details.  
*/

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
