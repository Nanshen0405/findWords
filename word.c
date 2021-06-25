/* word.c -- main.c的接口文件，用于放置函数源码										*/
/* 与main.c一起编译																	*/ 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "word.h"										/* 定义Lklist、String		*/

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

// 线性表基本操作函数
// 创建带头结点和尾结点的空表
Status List_Initialize(LkList *pList)					// 初始化创建一个空的线性表 ，带头指针和尾指针
{

	Status s = success;
	Node *p = (Node*)malloc(sizeof(Node));

	if(p){
		// 初始时，链表的下一个节点为空
		// 头结点也为尾结点
		p->next = NULL;
		pList->head = p;
		pList->tail = p;
	} else {
		// 内存分配失败
		s = fatal;
	}

	return s;
}
/*
    （尾插法）插入链表表尾
*/
Status List_TailInsert(LkList *pList, const String src) // 从链表尾部插入一个节点数据
{
	Status s = success;

    // 生成一个新节点
    Node *p = (Node*)malloc(sizeof(Node));
    if(p) {
        /*
            1、把字符串复制到链表节点数据上
            2、计数器值初始值为1
            3、新生成的节点p的next值为NULL
            4、将表尾终端节点指向新生成的节点p
			5、p作为新一轮的链表尾部节点
        */
        StringCopy(p->word.str,src);
        p->word.count = 1;
        p->next = NULL;
        pList->tail->next = p;
        pList->tail = p;
    } else {
        // 内存分配失败
        s = fatal;
    }

	return s;
}
Status List_Destory(LkList *pList)						// 销毁整个线性表，包括头指针和尾指针指向的
{
	Node *p,*q;
	/*
		p指向第一个节点，如果p没到表尾
		就继续循环体，释放下一个节点
	*/
	p = pList->head;
	while(p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	return success;
}
void List_Locate(const String src,LkList *pList,bool flag)		// 根据字符串查找线性表项目
{
    Node *p = pList->head->next;
    Node *q = NULL;
    while(p)
    {
        // 如果不相等做插入表尾操作，相等则计数器加1
        if(StringCompare(p->word.str,src)){
            
			if(!flag)p->word.count++;
//			else p->word.count = 0;
			// 如果有查找到屏蔽词存在于链表中则删除这个节点 
			else{
				if(q) {
					q->next = p->next;
				} else {
					pList->head->next = p->next;
				}
				free(p);
			}
            break;
        }
        q=p,p = p->next;
    }
    // 循环到表尾也没有找到，那就直接插入表尾
    if(p == NULL){
    	List_TailInsert(pList,src);
	}
}
void List_Output(LkList list)							// 输出线性表的每个项目数据
{
    Node *p;
    for(p=list.head->next; p; p=p->next)
    {
        StringPrint(p->word.str);
        printf("次数：%d\n",p->word.count);
    }
    putchar('\n');
}

// 字符串函数
void StringPrint(const String src)						// 输出字符串
{
    int i = 1;
    while(i < src[0])
    {
        putchar(tolower(src[i++]));
    }
	putchar(' ');
}
void StringCopy(String des,const String src)			// 字符串赋值
{
    int i = 1;
    // 1、循环遍历源字符串赋值给目标字符串
    while(i < src[0])
    {
        des[i] = src[i];
        i++;
    }
    // 2、最后将字符串的长度赋值给目标字符串
    des[0] = src[0];
}
bool StringCompare(const String s1, const String s2)	// 字符串比较，不区分大小写
{
    bool flag = true;
    // 1、先对字符串的长度作比较
    //  如果长度不等，则两个字符串肯定不相等
    if(s1[0] != s2[0]){
        return false;
    }

    // 2、如果长度一样，依次比较两个字符串中的每个字符
    int i = 1;
    while(i < s2[0])
    {
        // 将字符都转为小写字符
		// 不区分大小写进行比较
		if(tolower(s1[i]) != tolower(s2[i])){
           flag = false;
           break;
        }
        i++;
    }
    return flag;
}

// 排序函数
void SelectSort(LkList *pList)						// 选择排序
{
	Node *q,*p,temp;
	// 选择排序
	for(p=pList->head->next; p; p=p->next)
	{
		for(q = p->next; q; q=q->next)
		{
			if(p->word.count < q->word.count){
				temp.word = p->word;
				p->word =  q->word;
				q->word = temp.word;
			}
		}
	}
}

// 文件操作函数
void ReadFILE(FILE *fp, LkList *pList,bool flag)                 // 将文件中的数据处理后放到链表里
{
    // 3、读取数据
	char str[N];
	int i = 1;
	char last = -1, next;
//	bool flag = true;
	while((next=fgetc(fp)) != EOF)
    {
        /*
            1、如果当前读取的字符是字母
			就加入到字符串里
        */
        if(isalpha(next)){
            str[i++] = next;
        }

        /*
            2、如果当前字符不是字母 
            且上一个字符是字母就结束这个字符
            串并准备做查询操作
        */
        if(isalpha(last) && !isalpha(next)){
            str[0] = i;
            i = 1;
            // 屏蔽掉五个字母以下的简单词汇
			if(str[0] > 4){
	            List_Locate(str,pList,flag);	
			}	
        }
        // 3、覆盖上一个字符
        last = next;
    }
    // 当文件尾没有结束的句号时
    if((next==EOF) && isalpha(last)){
    	str[0] = i;
        i = 1;
		List_Locate(str,pList,flag);
	}

    // Text code 输出一遍链表
//  List_Output(pList);

}
void WriteFILE(FILE *fp,LkList list)                   // 将结果写入到文件中
{
    Node *p;
    int i = 1;
    fputs("小于3次的不做统计\n",fp), 
    fputs("总的统计结果如下：\n",fp);
    for(p=list.head->next; p; p=p->next)
    {
    	// 小于3次的不做存储 
		if(p->word.count > 3){
    		fprintf(fp,"%d、",i++);
	        PutStringFile(p->word.str,fp);
	        fprintf(fp,"\t次数：%d\n",p->word.count);
	        // 每十个单词加上一个分割线 
			if((i-1)%10 == 0){
	        	fputs("------------------------------\n",fp);
			}	
		}
    }
    putchar('\n');
}
void PutStringFile(const String src, FILE *fp)          // 将字符串写入文件中
{
    // 向文件中写入字符串
    int i = 1;
    while(i < src[0])
    {
        fputc(tolower(src[i++]),fp);
    }
}
