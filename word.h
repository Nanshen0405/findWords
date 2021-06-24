/* word.h -- main.c的头文件，用于放置函数原型和其他参数								*/
/* 与word.c、main.c一起编译															*/ 
#ifndef _WORD_H_
#define _WORD_H_
#include <stdbool.h>				/* C99特性 					*/
#define  N 50						/* 初始定义的单词字符串长度 */

typedef char* String;	// 预设的字符串类型
typedef int Status; 	// 函数结果状态返回值

enum Status{
	success = 1, fail = 0,
	/* 内存分配失败 */
	fatal = -1,
	/* 连续空间访问越界 */
	range_error = -2
};

//	单词的结构体，包含储存的字符串和计数器变量
typedef struct _word{
	char str[N];
	int count;
}Word;

typedef struct _node{			// 链表单节点的结构体
	Word word;					// 单节点中的元素数据
	struct _node *next;			// 指向下一个节点的指针
}Node,*NodePtr;					// 节点，节点的指针

typedef struct _lklist{			// 链式线性表的结构 Linked List
	Node *head;					// 链表的头结点指针
	Node *tail;					// 链表的尾结点指针
}LkList,*LkListPtr;				// 单链表，单链表的指针

// 线性表基本操作函数
Status List_Initialize(LkList *pList);						// 初始化创建一个空的线性表 ，带头指针和尾指针
Status List_TailInsert(LkList *pList, const String src);	// 从链表尾部插入一个节点数据
Status List_Destory(LkList *pList);							// 销毁整个线性表，包括头指针和尾指针指向的
void List_Locate(const String src,LkList *pList,bool flag);	// 根据字符串查找线性表项目
void List_Output(LkList list);								// 输出线性表的每个项目数据
// 字符串函数
void StringPrint(const String src);							// 输出字符串
void StringCopy(String des,const String src);				// 字符串赋值
bool StringCompare(const String s1, const String s2);		// 字符串比较，不区分大小写
// 排序函数
void SelectSort(LkList *pList); 							// 选择排序
// 文件操作函数
void ReadFILE(FILE *fp, LkList *pList,bool flag);      		// 将文件中的数据处理后放到链表里
void WriteFILE(FILE *fp,LkList list);                  	 	// 将链表写入到文件中
void PutStringFile(const String src, FILE *fp);        	 	// 将字符串写入文件中
#endif
