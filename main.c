/*
	项目：单词乐软件V1.1版
	开发人员： 兰柯万
	QQ：1733100391
*/
/* main.c -- 用于处理一篇英文文章中出现次数最多的单词，使用的数据结构为链表 */
/* 与word.c一起编译															*/
#include <stdio.h>
#include <stdlib.h>					/* 提供exit()原型			*/
#include <windows.h> 				/* 提供Sleep()原型			*/
#include <direct.h>					/* 提供getcwd()原型			*/
#include <time.h>
#include <mycon.h>
#include <conio.h>
#include "word.h"					/* 定义Lklist、String		*/
#define LEN 200						/* 文件名长度				*/

/*
   Copyright (c) [Year] [name of copyright holder]
   [Software Name] is licensed under Mulan PSL v2.
   You can use this software according to the terms and conditions of the Mulan PSL v2. 
   You may obtain a copy of Mulan PSL v2 at:
            http://license.coscl.org.cn/MulanPSL2 
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.  
   See the Mulan PSL v2 for more details.  


                     Mulan Permissive Software License，Version 2

   Mulan Permissive Software License，Version 2 (Mulan PSL v2)
   January 2020 http://license.coscl.org.cn/MulanPSL2

   Your reproduction, use, modification and distribution of the Software shall be subject to Mulan PSL v2 (this License) with the following terms and conditions: 
   
   0. Definition
   
      Software means the program and related documents which are licensed under this License and comprise all Contribution(s). 
   
      Contribution means the copyrightable work licensed by a particular Contributor under this License.
   
      Contributor means the Individual or Legal Entity who licenses its copyrightable work under this License.
   
      Legal Entity means the entity making a Contribution and all its Affiliates.
   
      Affiliates means entities that control, are controlled by, or are under common control with the acting entity under this License, ‘control’ means direct or indirect ownership of at least fifty percent (50%) of the voting power, capital or other securities of controlled or commonly controlled entity.

   1. Grant of Copyright License

      Subject to the terms and conditions of this License, each Contributor hereby grants to you a perpetual, worldwide, royalty-free, non-exclusive, irrevocable copyright license to reproduce, use, modify, or distribute its Contribution, with modification or not.

   2. Grant of Patent License 

      Subject to the terms and conditions of this License, each Contributor hereby grants to you a perpetual, worldwide, royalty-free, non-exclusive, irrevocable (except for revocation under this Section) patent license to make, have made, use, offer for sale, sell, import or otherwise transfer its Contribution, where such patent license is only limited to the patent claims owned or controlled by such Contributor now or in future which will be necessarily infringed by its Contribution alone, or by combination of the Contribution with the Software to which the Contribution was contributed. The patent license shall not apply to any modification of the Contribution, and any other combination which includes the Contribution. If you or your Affiliates directly or indirectly institute patent litigation (including a cross claim or counterclaim in a litigation) or other patent enforcement activities against any individual or entity by alleging that the Software or any Contribution in it infringes patents, then any patent license granted to you under this License for the Software shall terminate as of the date such litigation or activity is filed or taken.

   3. No Trademark License

      No trademark license is granted to use the trade names, trademarks, service marks, or product names of Contributor, except as required to fulfill notice requirements in Section 4.

   4. Distribution Restriction

      You may distribute the Software in any medium with or without modification, whether in source or executable forms, provided that you provide recipients with a copy of this License and retain copyright, patent, trademark and disclaimer statements in the Software.

   5. Disclaimer of Warranty and Limitation of Liability

      THE SOFTWARE AND CONTRIBUTION IN IT ARE PROVIDED WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED. IN NO EVENT SHALL ANY CONTRIBUTOR OR COPYRIGHT HOLDER BE LIABLE TO YOU FOR ANY DAMAGES, INCLUDING, BUT NOT LIMITED TO ANY DIRECT, OR INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM YOUR USE OR INABILITY TO USE THE SOFTWARE OR THE CONTRIBUTION IN IT, NO MATTER HOW IT’S CAUSED OR BASED ON WHICH LEGAL THEORY, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

   6. Language

      THIS LICENSE IS WRITTEN IN BOTH CHINESE AND ENGLISH, AND THE CHINESE VERSION AND ENGLISH VERSION SHALL HAVE THE SAME LEGAL EFFECT. IN THE CASE OF DIVERGENCE BETWEEN THE CHINESE AND ENGLISH VERSIONS, THE CHINESE VERSION SHALL PREVAIL.

   END OF THE TERMS AND CONDITIONS

   How to Apply the Mulan Permissive Software License，Version 2 (Mulan PSL v2) to Your Software

      To apply the Mulan PSL v2 to your work, for easy identification by recipients, you are suggested to complete following three steps:

      i Fill in the blanks in following statement, including insert your software name, the year of the first publication of your software, and your name identified as the copyright owner; 

      ii Create a file named “LICENSE” which contains the whole context of this License in the first directory of your software package;

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
    函数原型：char* getcwd(char* buffer, int len);
    参数：buffer是指将当前工作目录的绝对路径copy到buffer所指的内存空间， len是buffer的长度。
    返回值：获取成功则返回当前工作目录（绝对路径），失败则返回false（即NULL）。
    该函数所属头文件为<direct.h>
*/
void Initialized(String msg);										 				// 初始化
void ShowInterface(String msg);														// 展示界面
void AccessProcessing(FILE *read,FILE *write,FILE *skip,LkList *pList,bool flag);	// 用于处理用户请求
String GetDirs(String file,int len);
int main (int argc,const char * argv[])
{
	// 一、初始化软件界面，加载变量
	FILE *read,*write,*skip;
	char inputfile[LEN],outputfile[LEN],skipfile[LEN],dirfile[LEN];
	srand(time(NULL));
	LkList list;
	bool flag = true;
	String msg = "单词乐软件V1.1版";
	Initialized(msg);
	ShowInterface(msg);

	// 二、读取当前文件目录，以用于设置持久化存储到文件 
	String dir = getcwd(dirfile,LEN-50);
	if(dir = NULL){
		puts("读取当前工作目录失败，退出系统！");
		exit(fail);
	}
	strcpy(outputfile,dirfile);
	strcat(outputfile,"\\统计结果.txt");
	strcpy(skipfile,dirfile);
	strcat(skipfile,"\\屏蔽单词.txt");
	 
	// 三、读取用户输入的文件名、可自动读取，也可以手动输入读取 还可以通过命令行读取
	Status s = fail;
	// 1、查看是否有命令行参数 
	if(argc <= 1){

		// 2、没有命令行参数则进行自动获取文档名 
		strcpy(inputfile,dirfile);
		strcat(inputfile,"\\英文文档.txt"); 
		// 3、如果无法自动打开文件则手动输入文档名来获取 
		if((read = fopen(inputfile,"rt")) == NULL) {
			puts("\n自动打开失败，文件不存在于当前目录或者是不支持的格式，请手动输入文档名\n");	
			
			/* 手动输入文件名 */
			do {
				puts("\n请输入文档名：");
				int t = scanf("%150[^ \n]",inputfile);
				if(t) {
					strcat(inputfile,".txt");
					break;
				} else {
					puts("文件名过长或文件名不合法,请重新输入");
					rewind(stdin);
					continue;
				}
			} while(true);
		} else {
			puts("自动获取文档成功！");
			s = success;
			Sleep(2000); 
		}
	} else {
		// 4、有命令行参数就获取命令行参数作为文件名 
		int len = strlen(argv[1]);
		// 设置输入文件名 
		if(len <= 150){
			strcpy(inputfile,argv[1]);
			strcat(inputfile,".txt");
		} else {
			puts("打开文档失败，文件名过长或者出现其他异常，退出程序！");
			exit(EXIT_FAILURE);
		}		
	}

	// 四、打开要处理的文件、建立空表用于存储单词数据
	if(List_Initialize(&list) != success) {
		puts("初始化线性表失败！请检查是否有内存可用，退出程序。");
		exit(EXIT_FAILURE);
	}	
	// 如果自动获取失败，再用手动输入或者命令行参数来打开文件 
	if((s==fail) && ((read=fopen(inputfile,"rt"))==NULL)) {
		printf("\n%s打开失败，文件不存在于当前目录或者是不支持的格式，退出程序\n",inputfile);
		exit(EXIT_FAILURE);
	} 
	if((write=fopen(outputfile,"wt")) == NULL) {
		printf("\n%s打开失败！文件不存在于当前目录或者是不支持的格式，退出程序\n",outputfile);
		exit(EXIT_FAILURE);
	}
	if((skip=fopen(skipfile,"rt")) == NULL) {
		puts("屏蔽单词文本不存在，不做屏蔽处理");
		flag = false;
	}

	// 五、读取数据并处理结果
	AccessProcessing(read,write,skip,&list,flag);

	// 六、关闭文件，释放内存
	if(!List_Destory(&list)) {
		puts("销毁线性表失败，退出系统！");
		exit(EXIT_FAILURE); // exit_failure
	}
	if(fclose(read)) {
		puts("文件关闭失败，请查看文件是否存在");
		exit(EXIT_FAILURE);
	}
	if(fclose(write)) {
		puts("文件关闭失败，请查看文件是否存在");
		exit(EXIT_FAILURE);
	}
	if(flag && fclose(skip)) {
		puts("文件关闭失败，请查看文件是否存在");
		exit(EXIT_FAILURE);
	}

	puts("再见，欢迎下次使用本软件\n按任意键退出软件");
	getch();
	return 0;
}

void ShowInterface(String msg)									// 展示界面
{
	puts("欢迎使用本软件，本软件用于统计一篇txt格式英文文档中出现次数最多的单词\n");
	Sleep(1000);
	puts("温馨提示: 文档需要和程序在同一路径下，文件名不要过长哦，程序处理完文档，会把结");
	puts("果输出至当前目录下的\"处理结果.txt\"文件中，如果没有则会创建一个新的文本文件处");
	puts("理文档，程序本身会屏蔽4个字母以下的简单词汇，如果用户有自己需要手动屏蔽的单词，");
	puts("可以新建一个文件，文件名必须是屏蔽单词.txt，否则程序无法查找到。用户如果指定处");
	puts("理文件名为英文文档.txt，则程序会自动读取文档，无需用户手动输入文档名"); 
	Sleep(2000);
	cls();
	gotoxy(40-strlen(msg)/2,0);
	puts(msg);
	set_color(0,rand()%15+1);
}

void Initialized(String msg)
{
	// 设置参数
	set_title(msg);
	set_size(100,30);
	set_color(0,rand()%15+1);
}
void AccessProcessing(FILE *read,FILE *write,FILE * skip,LkList *pList,bool flag)	// 用于处理文件中的数据
{

	// 1、从文件中读取数据并处理，将结果放到线性表中
	puts("\n开始读取文件和处理数据中...");
	ReadFILE(read,pList,false);
	Sleep(2000);
	puts("读取文件并处理数据成功");
	Sleep(2000);
	// 2、如果屏蔽文本存在才做处理
	if(flag) {
		ReadFILE(skip,pList,flag);
		puts("屏蔽处理中...");
		Sleep(2000);
	}
	// 3、进行排序并将结果写入另一个文档中
	SelectSort(pList);
	puts("向目标文件写入处理结果中...");
	WriteFILE(write,*pList);
	Sleep(2000);
	puts("写入成功，即将退出程序");
}
