/* word.c -- main.c�Ľӿ��ļ������ڷ��ú���Դ��										*/
/* ��main.cһ�����																	*/ 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "word.h"										/* ����Lklist��String		*/

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
