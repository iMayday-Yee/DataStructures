//  Menu for Linear Table On Sequence Structure
//-------------------------------------------------
//1.InitList		7.LocateElem
//2.DestroyList		8.PriorElem
//3.ClearList		9.NextElem
//4.ListEmpty		10.ListInsert
//5.ListLength		11.ListDelete
//6.GetElem			12.ListTrabverse
//0.Exit
//-------------------------------------------------
#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1				//几个状态返回值的宏定义
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10			//代码中常数的宏定义
using namespace std;

typedef int status;   				//返回值类型定义
typedef char ElemType; 				//数据元素类型定义
typedef struct node{  				//链式表结点的结构定义
	ElemType data;
	float xishu;
	int cishu;
	struct node *next;
}node;
typedef struct List{  				//链表的结构定义
	node* head; 	  					//链表的头结点
	int num_node;						//链表结点数
	int len_list;	  					//多项式的长度
}List;

int Init_flag[10]={0};				//判断x号线性表是否已被初始化
int i;
int get_i;
int op;
int which_List;
int insert_position;
int delete_position;
int position;
int num_a,num_b,num_c;
int print_which_list;
ElemType e;
ElemType insert_e;
ElemType delete_e;
List *pList0,list[100];
List *pLista,*pListb,*pListc;
List *List_print;

status InitList(List* L)
{
	L->head=(node *)malloc(sizeof(node));
	L->head->next=NULL;
	L->num_node=0;
	L->len_list=0;
	if(L)
		return OK;
	else
		return ERROR;
}

status DestroyList(List* L)
{
	node* Q;
	node* P=L->head;
	while(P!=NULL)
	{
		Q=P;
		P=P->next;
		free(Q);
	}
	L->head=NULL;
	L->num_node=0;
	return OK;
}

status ClearList(List* L)
{
	node* Q;
	node* P=L->head->next;
	while(P!=NULL)
	{
		Q=P;
		P=P->next;
		free(Q);
	}
	L->head->next=NULL;
	L->num_node=0;
	return OK;
}

status ListEmpty(List* L)//判断链表是否为空表
{
	if(L->num_node==0)	//如果结点个数为0，则表明为空表
		return TRUE;
	else				//如果结点个数不为0，则表明不为空表
		return FALSE;
}

int ListLength(List* L)//求链表的长度
{
	return L->num_node;//直接返回线性表结构体中的结点个数
}

status GetElem(List* L,int i,ElemType* e)
{
	if(i>=1&&i<=L->num_node)
	{
		position=0;
		node* P=L->head;
		for(;position<i;position++)
			P=P->next;
		*e=P->data;
		return OK;
	}
	else
		return ERROR;
}

int LocateElem(List* L,ElemType e)
{
	position=0;
	node* P=L->head;
	while(position<L->num_node)
	{
		P=P->next;
		position++;
		if(P->data==e)
			return position;
	}
	return ERROR;
}

status PriorElem(List* L,ElemType cur_e,ElemType *pre_e)
{
	position=0;
	node* P=L->head->next;
	node* Q=L->head;
	while(position<L->num_node-1)
	{
		Q=P;
		P=P->next;
		position++;
		if(P->data==cur_e)
		{
			*pre_e=Q->data;
			return OK;
		}
	}
	return ERROR;
}

status NextElem(List* L,ElemType cur_e,ElemType *next_e)
{
	position=0;
	node* P=L->head;
	node* Q=L->head->next;
	while(position<L->num_node-1)
	{
		P=P->next;
		Q=Q->next;
		position++;
		if(P->data==cur_e)
		{
			*next_e=Q->data;
			return OK;
		}
	}
	return ERROR;
}

status ListInsert(List* L,int i,ElemType e)
{
	if((i>=1)&&(i<=L->num_node))
	{
		node* P=L->head;
		node* Q=(node*)malloc(sizeof(node));
		position=0;
		while(position<i-1)
		{
			P=P->next;
			position++;
		}
		Q->next=P->next;
		P->next=Q;
		Q->data=e;
		L->num_node++;
		return OK;
	}
	else if(i==L->num_node+1)
	{
		node* P=L->head;
		while(P->next!=NULL)
			P=P->next;
		node* Q=(node*)malloc(sizeof(node));
		P->next=Q;
		Q->data=e;
		Q->next=NULL;
		L->num_node++;
		return OK;
	}
	return ERROR;
}

status ListDelete(List* L,int i,ElemType* e)
{
	node* P;
	if(i>=1&&i<=L->num_node)
	{
		position=0;
		P=L->head;
		while(position<i-1)
		{
			P=P->next;
			position++;
		}
		node* Q=P->next;
		P->next=Q->next;
		*e=Q->data;
		free(Q);
		L->num_node--;
		return OK;
	}
	else
		return ERROR;
}

status ListTrabverse(List* L)
{
	if(L->num_node==0)
		return ERROR;
	else
	{
		node* P=L->head->next;
		while(P->next!=NULL)
		{
			printf("%c",P->data);
			P=P->next;
		}
		printf("%c\n",P->data);
		return OK;
	}
}

status CreatList(List* L)
{
	node* P=L->head;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		node* Q=(node*)malloc(sizeof(node));
		cin>>Q->xishu>>Q->cishu;
		if(i>=2&&(Q->cishu==P->next->cishu))
		{
			P->next->xishu+=Q->xishu;
			continue;
		}
		Q->next=P->next;
		P->next=Q;
		L->len_list++;
	}
	if(L->len_list==n)
		return OK;
	else
		return ERROR;
}

void ShowList(List* L)
{
	node* P=L->head;
	int is_0=1;
	int is_1st=1;
	while(P->next!=NULL)
	{
		P=P->next;
		if(P->xishu!=(int)(P->xishu))	//如果系数不为整数
		{
			if(P->xishu<0)		//如果系数为负数
			{
				if((P->cishu!=0)&&(P->cishu!=1))
					printf("%.1fx^%d",P->xishu,P->cishu);
				else if(P->cishu==0)
					printf("%.1f",P->xishu);
				else
					printf("%.1fx",P->xishu);
			}
			else				//如果系数为正数
			{
				if(is_1st!=1)
					printf("+");
				if((P->cishu!=0)&&(P->cishu!=1))
					printf("%.1fx^%d",P->xishu,P->cishu);
				else if(P->cishu==0)
					printf("%.1f",P->xishu);
				else
					printf("%.1fx",P->xishu);
			}
			is_0=0;
		}
		else         //如果系数为整数
		{
			if(P->xishu==0)
				continue;
			else if(P->xishu<0)
			{
				if(P->xishu==-1)
				{
					if((P->cishu!=0)&&(P->cishu!=1))
						printf("-x^%d",P->xishu,P->cishu);
					else if(P->cishu==0)
						printf("-1",P->xishu);
					else
						printf("-x",P->xishu);
				}
				else
				{
					if((P->cishu!=0)&&(P->cishu!=1))
						printf("%.0fx^%d",P->xishu,P->cishu);
					else if(P->cishu==0)
						printf("%.0f",P->xishu);
					else
						printf("%.0fx",P->xishu);
				}
			}
			else
			{
				if(is_1st!=1)
					printf("+");
				if(P->xishu==1)
				{
					if((P->cishu!=0)&&(P->cishu!=1))
						printf("x^%d",P->xishu,P->cishu);
					else if(P->cishu==0)
						printf("1",P->xishu);
					else
						printf("x",P->xishu);
				}
				else
				{
					if((P->cishu!=0)&&(P->cishu!=1))
						printf("%.0fx^%d",P->xishu,P->cishu);
					else if(P->cishu==0)
						printf("%.0f",P->xishu);
					else
						printf("%.0fx",P->xishu);
				}
			}
			is_0=0;
		}
		is_1st=0;
	}
	if(is_0==1)
		printf("0");
	printf("\n");
}

void Insert2(List* L,float xi_shu,int ci_shu)
{
	node* P=L->head;
	while(P->next!=NULL)
		P=P->next;
	node* Q=(node*)malloc(sizeof(node));
	Q->next=P->next;
	P->next=Q;
	Q->cishu=ci_shu;
	Q->xishu=xi_shu;
	L->len_list++;
}

void AddList(List* L1,List* L2,List* L3)
{
	node* P=L1->head;
	node* Q=L2->head;
	int flag_P=1;
	int flag_Q=1;
	while(P->next||Q->next)
	{
		if((P->next!=NULL)&&(flag_P==1))
			P=P->next;
		if((Q->next!=NULL)&&(flag_Q==1))
			Q=Q->next;
		if(P->cishu==Q->cishu)
		{
			Insert2(L3,P->xishu+Q->xishu,P->cishu);
			flag_P=1;
			flag_Q=1;
		}
		else if(P->cishu>Q->cishu)
		{
			Insert2(L3,P->xishu,P->cishu);
			flag_P=1;
			flag_Q=0;
		}
		else
		{
			Insert2(L3,Q->xishu,Q->cishu);
			flag_P=0;
			flag_Q=1;
		}
	}
}

void MinusList(List* L1,List* L2,List* L3)
{
	node* P=L1->head;
	node* Q=L2->head;
	int flag_P=1;
	int flag_Q=1;
	while(P->next||Q->next)
	{
		if((P->next!=NULL)&&(flag_P==1))
			P=P->next;
		if((Q->next!=NULL)&&(flag_Q==1))
			Q=Q->next;
		if(P->cishu==Q->cishu)
		{
			Insert2(L3,(P->xishu)-(Q->xishu),P->cishu);
			flag_P=1;
			flag_Q=1;
		}
		else if(P->cishu>Q->cishu)
		{
			Insert2(L3,P->xishu,P->cishu);
			flag_P=1;
			flag_Q=0;
		}
		else
		{
			Insert2(L3,-Q->xishu,Q->cishu);
			flag_P=0;
			flag_Q=1;
		}
	}
}

int main()
{
	op=1;
	while(op)
	{	
		cin>>op;
		if(Init_flag[which_List]!=1&&(op!=1&&op!=19))//如果还没有创建该线性表
			printf("请先创建%d号线性表！\n",which_List);
		else
			switch(op)
			{
				case 1:
					if(InitList(pList0)==OK)	//线性表创建成功
					{
						printf("%d号线性表创建成功!",which_List);
						Init_flag[which_List]=1;
					}
					else						//线性表创建失败
						printf("%d号线性表创建失败!",which_List);
					break;
				case 2:
					if(DestroyList(pList0)==OK)	//线性表销毁成功
					{
						printf("%d号线性表销毁成功!",which_List);
						Init_flag[which_List]=0;
					}
					else						//线性表销毁失败
						printf("%d号线性表销毁成功!",which_List);
					break;
				case 3:
					if(ClearList(pList0)==OK)   //清空线性表成功
						printf("%d号线性表清空成功!",which_List);
					else						//清空线性表失败
						printf("%d号线性表清空失败!",which_List);
					break;
				case 4:
					if(ListEmpty(pList0)==TRUE)	//该链表为空表
						printf("%d号链表为空表\n",which_List);
					else						//该链表不为空表
						printf("%d号链表不为空表\n",which_List);
					break;
				case 5:
					printf("%d号该链表长度为%d\n",ListLength(pList0));//该链表长度为ListLength(pList0)
					break;
				case 6:
					cin>>get_i;			//输入你要获取的元素的位置i
					if(GetElem(pList0,get_i,&e)==ERROR)
						printf("NoElem\n");		//如果没有这个位置，输出NoElem
					else
						printf("%c\n",e);		//如果有这个位置，输出该位置处元素e  
					break;
				case 7:
					cin>>e;
					if(LocateElem(pList0,e)==ERROR)
						printf("NoElem\n");		//如果没有找到，输出NoElem
					else
						printf("%d\n",LocateElem(pList0,e));//如果找到了，输出所找元素位置LocateElem(pList0,e)
					break;
				case 8:
					if(PriorElem(pList0,e,&e)==ERROR)
						printf("NoElem\n");		//如果没有前驱，输出NoElem
					else
						printf("%c\n",e);		//如果有前驱，输出前驱e
					break;
				case 9:
					if(NextElem(pList0,e,&e)==ERROR)
						printf("NoElem\n");		//如果没有后继，输出NoElem
					else
						printf("%c\n",e);		//如果有后继，输出前驱e
					break;
				case 10:
					cin>>insert_position>>insert_e;//输入要插入的位置i和元素e
					if(ListInsert(pList0,insert_position,insert_e)==OK)
						;						//插入成功，保留该代码段后续可以输出提示信息
					else
						;						//插入失败，保留该代码段后续可以输出提示信息
					break;
				case 11:
					cin>>delete_position;	//输入要删除的元素位置
					if(ListDelete(pList0,delete_position,&delete_e)==OK)
						printf("%c\n",delete_e);	//如果删除成功，输出被删除元素数据
					else
						printf("NoElem\n");			//如果删除失败，输出NoElem
					break;
				case 12:
					if(ListTrabverse(pList0)==ERROR)
						;						//遍历失败，保留该代码段后续可以输出提示信息
					else
						;						//遍历成功，保留该代码段后续可以输出提示信息
					break;
				case 19:
					cin>>which_List;	//输入要切换的链表的序号
					pList0=&list[which_List];	//将当前工作链表指针值换成选择的链表的地址
					break;
				case 21:
					if(CreatList(pList0)==OK)
						;
					else
						;
					break;
				case 22:
					cin>>print_which_list;
					List_print=&list[print_which_list];
					ShowList(List_print);
					break;
				case 23:
					cin>>num_a>>num_b>>num_c;
					pLista=&list[num_a];
					pListb=&list[num_b];
					pListc=&list[num_c];
					ClearList(pListc);
					AddList(pLista,pListb,pListc);
					break;
				case 24:
					cin>>num_a>>num_b>>num_c;
					pLista=&list[num_a];
					pListb=&list[num_b];
					pListc=&list[num_c];
					ClearList(pListc);
					MinusList(pLista,pListb,pListc);
					break;
				case 0:
					break;
			}//end of switch
  	}//end of while
}//end of main()
