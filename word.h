/* word.h -- main.c��ͷ�ļ������ڷ��ú���ԭ�ͺ���������								*/
/* ��word.c��main.cһ�����															*/ 
#ifndef _WORD_H_
#define _WORD_H_
#include <stdbool.h>				/* C99���� 					*/
#define  N 50						/* ��ʼ����ĵ����ַ������� */

typedef char* String;	// Ԥ����ַ�������
typedef int Status; 	// �������״̬����ֵ

enum Status{
	success = 1, fail = 0,
	/* �ڴ����ʧ�� */
	fatal = -1,
	/* �����ռ����Խ�� */
	range_error = -2
};

//	���ʵĽṹ�壬����������ַ����ͼ���������
typedef struct _word{
	char str[N];
	int count;
}Word;

typedef struct _node{			// �����ڵ�Ľṹ��
	Word word;					// ���ڵ��е�Ԫ������
	struct _node *next;			// ָ����һ���ڵ��ָ��
}Node,*NodePtr;					// �ڵ㣬�ڵ��ָ��

typedef struct _lklist{			// ��ʽ���Ա�Ľṹ Linked List
	Node *head;					// �����ͷ���ָ��
	Node *tail;					// �����β���ָ��
}LkList,*LkListPtr;				// �������������ָ��

// ���Ա������������
Status List_Initialize(LkList *pList);						// ��ʼ������һ���յ����Ա� ����ͷָ���βָ��
Status List_TailInsert(LkList *pList, const String src);	// ������β������һ���ڵ�����
Status List_Destory(LkList *pList);							// �����������Ա�����ͷָ���βָ��ָ���
void List_Locate(const String src,LkList *pList,bool flag);	// �����ַ����������Ա���Ŀ
void List_Output(LkList list);								// ������Ա��ÿ����Ŀ����
// �ַ�������
void StringPrint(const String src);							// ����ַ���
void StringCopy(String des,const String src);				// �ַ�����ֵ
bool StringCompare(const String s1, const String s2);		// �ַ����Ƚϣ������ִ�Сд
// ������
void SelectSort(LkList *pList); 							// ѡ������
// �ļ���������
void ReadFILE(FILE *fp, LkList *pList,bool flag);      		// ���ļ��е����ݴ����ŵ�������
void WriteFILE(FILE *fp,LkList list);                  	 	// ������д�뵽�ļ���
void PutStringFile(const String src, FILE *fp);        	 	// ���ַ���д���ļ���
#endif
