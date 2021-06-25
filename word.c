/* word.c -- main.c�Ľӿ��ļ������ڷ��ú���Դ��										*/
/* ��main.cһ�����																	*/ 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "word.h"										/* ����Lklist��String		*/

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

// ���Ա������������
// ������ͷ����β���Ŀձ�
Status List_Initialize(LkList *pList)					// ��ʼ������һ���յ����Ա� ����ͷָ���βָ��
{

	Status s = success;
	Node *p = (Node*)malloc(sizeof(Node));

	if(p){
		// ��ʼʱ���������һ���ڵ�Ϊ��
		// ͷ���ҲΪβ���
		p->next = NULL;
		pList->head = p;
		pList->tail = p;
	} else {
		// �ڴ����ʧ��
		s = fatal;
	}

	return s;
}
/*
    ��β�巨�����������β
*/
Status List_TailInsert(LkList *pList, const String src) // ������β������һ���ڵ�����
{
	Status s = success;

    // ����һ���½ڵ�
    Node *p = (Node*)malloc(sizeof(Node));
    if(p) {
        /*
            1�����ַ������Ƶ�����ڵ�������
            2��������ֵ��ʼֵΪ1
            3�������ɵĽڵ�p��nextֵΪNULL
            4������β�ն˽ڵ�ָ�������ɵĽڵ�p
			5��p��Ϊ��һ�ֵ�����β���ڵ�
        */
        StringCopy(p->word.str,src);
        p->word.count = 1;
        p->next = NULL;
        pList->tail->next = p;
        pList->tail = p;
    } else {
        // �ڴ����ʧ��
        s = fatal;
    }

	return s;
}
Status List_Destory(LkList *pList)						// �����������Ա�����ͷָ���βָ��ָ���
{
	Node *p,*q;
	/*
		pָ���һ���ڵ㣬���pû����β
		�ͼ���ѭ���壬�ͷ���һ���ڵ�
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
void List_Locate(const String src,LkList *pList,bool flag)		// �����ַ����������Ա���Ŀ
{
    Node *p = pList->head->next;
    Node *q = NULL;
    while(p)
    {
        // ���������������β������������������1
        if(StringCompare(p->word.str,src)){
            
			if(!flag)p->word.count++;
//			else p->word.count = 0;
			// ����в��ҵ����δʴ�������������ɾ������ڵ� 
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
    // ѭ������βҲû���ҵ����Ǿ�ֱ�Ӳ����β
    if(p == NULL){
    	List_TailInsert(pList,src);
	}
}
void List_Output(LkList list)							// ������Ա��ÿ����Ŀ����
{
    Node *p;
    for(p=list.head->next; p; p=p->next)
    {
        StringPrint(p->word.str);
        printf("������%d\n",p->word.count);
    }
    putchar('\n');
}

// �ַ�������
void StringPrint(const String src)						// ����ַ���
{
    int i = 1;
    while(i < src[0])
    {
        putchar(tolower(src[i++]));
    }
	putchar(' ');
}
void StringCopy(String des,const String src)			// �ַ�����ֵ
{
    int i = 1;
    // 1��ѭ������Դ�ַ�����ֵ��Ŀ���ַ���
    while(i < src[0])
    {
        des[i] = src[i];
        i++;
    }
    // 2������ַ����ĳ��ȸ�ֵ��Ŀ���ַ���
    des[0] = src[0];
}
bool StringCompare(const String s1, const String s2)	// �ַ����Ƚϣ������ִ�Сд
{
    bool flag = true;
    // 1���ȶ��ַ����ĳ������Ƚ�
    //  ������Ȳ��ȣ��������ַ����϶������
    if(s1[0] != s2[0]){
        return false;
    }

    // 2���������һ�������αȽ������ַ����е�ÿ���ַ�
    int i = 1;
    while(i < s2[0])
    {
        // ���ַ���תΪСд�ַ�
		// �����ִ�Сд���бȽ�
		if(tolower(s1[i]) != tolower(s2[i])){
           flag = false;
           break;
        }
        i++;
    }
    return flag;
}

// ������
void SelectSort(LkList *pList)						// ѡ������
{
	Node *q,*p,temp;
	// ѡ������
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

// �ļ���������
void ReadFILE(FILE *fp, LkList *pList,bool flag)                 // ���ļ��е����ݴ����ŵ�������
{
    // 3����ȡ����
	char str[N];
	int i = 1;
	char last = -1, next;
//	bool flag = true;
	while((next=fgetc(fp)) != EOF)
    {
        /*
            1�������ǰ��ȡ���ַ�����ĸ
			�ͼ��뵽�ַ�����
        */
        if(isalpha(next)){
            str[i++] = next;
        }

        /*
            2�������ǰ�ַ�������ĸ 
            ����һ���ַ�����ĸ�ͽ�������ַ�
            ����׼������ѯ����
        */
        if(isalpha(last) && !isalpha(next)){
            str[0] = i;
            i = 1;
            // ���ε������ĸ���µļ򵥴ʻ�
			if(str[0] > 4){
	            List_Locate(str,pList,flag);	
			}	
        }
        // 3��������һ���ַ�
        last = next;
    }
    // ���ļ�βû�н����ľ��ʱ
    if((next==EOF) && isalpha(last)){
    	str[0] = i;
        i = 1;
		List_Locate(str,pList,flag);
	}

    // Text code ���һ������
//  List_Output(pList);

}
void WriteFILE(FILE *fp,LkList list)                   // �����д�뵽�ļ���
{
    Node *p;
    int i = 1;
    fputs("С��3�εĲ���ͳ��\n",fp), 
    fputs("�ܵ�ͳ�ƽ�����£�\n",fp);
    for(p=list.head->next; p; p=p->next)
    {
    	// С��3�εĲ����洢 
		if(p->word.count > 3){
    		fprintf(fp,"%d��",i++);
	        PutStringFile(p->word.str,fp);
	        fprintf(fp,"\t������%d\n",p->word.count);
	        // ÿʮ�����ʼ���һ���ָ��� 
			if((i-1)%10 == 0){
	        	fputs("------------------------------\n",fp);
			}	
		}
    }
    putchar('\n');
}
void PutStringFile(const String src, FILE *fp)          // ���ַ���д���ļ���
{
    // ���ļ���д���ַ���
    int i = 1;
    while(i < src[0])
    {
        fputc(tolower(src[i++]),fp);
    }
}
