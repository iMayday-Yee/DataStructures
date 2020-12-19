//Please open in GB2312 coding format
//author：余永岳	id：U201911746
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

int Init_flag[10]={0};//判断x号线性表是否已被初始化
int i;
int get_i;
int op;//操作序号
int which_List;//储存目前工作线性表的序号
int insert_position;
int delete_position;
int position;
int num_a,num_b,num_c;//用于多项式加减的序号
int print_which_list;//储存要输出的线性表的序号
ElemType e;
ElemType insert_e;
ElemType delete_e;
List *pList0,list[100];
List *pLista,*pListb,*pListc;//多项式加减的链表指针
List *List_print;//多项式输出的链表指针

status InitList(List* L)//1号功能，初始化表
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

status DestroyList(List* L)//2号功能，销毁表
{
	node* Q;
	node* P=L->head;//不保留头结点，全部free
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

status ClearList(List* L)//3号功能，清空表
{
	node* Q;
	node* P=L->head->next;//保留头结点，其他全部free
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

status ListEmpty(List* L)//4号功能，判断空表
{
	if(L->num_node==0)	//如果结点个数为0，则表明为空表
		return TRUE;
	else				//如果结点个数不为0，则表明不为空表
		return FALSE;
}

int ListLength(List* L)//5号功能，求表长
{
	return L->num_node;//直接返回线性表结构体中的结点个数
}

status GetElem(List* L,int i,ElemType* e)//6号功能，获得元素
{
	if(i>=1&&i<=L->num_node)
	{
		position=0;
		node* P=L->head;
		for(;position<i;position++)
			P=P->next;
		*e=P->data;//用e来返回所找元素
		return OK;
	}
	else
		return ERROR;
}

int LocateElem(List* L,ElemType e)//7号功能，查找元素
{
	position=0;
	node* P=L->head;
	while(position<L->num_node)
	{
		P=P->next;
		position++;
		if(P->data==e)
			return position;//用position来返回所找元素位置
	}
	return ERROR;
}

status PriorElem(List* L,ElemType cur_e,ElemType *pre_e)//8号功能，获得前驱
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
			*pre_e=Q->data;//用pre_e来返回所找元素前驱
			return OK;
		}
	}
	return ERROR;
}

status NextElem(List* L,ElemType cur_e,ElemType *next_e)//9号功能，获得后继
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
			*next_e=Q->data;//用next_e来返回所找元素后继
			return OK;
		}
	}
	return ERROR;
}

status ListInsert(List* L,int i,ElemType e)//10号功能，插入元素
{
	if((i>=1)&&(i<=L->num_node))//如果要插入的位置在链表中间
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
	else if(i==L->num_node+1)//如果要插入的位置在链表结尾
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
	else
		return ERROR;
}

status ListDelete(List* L,int i,ElemType* e)//11号功能，删除元素
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

status ListTrabverse(List* L)//12号功能，遍历表
{
	if(L->num_node==0)
		return ERROR;
	else
	{
		printf("遍历结果为: ");
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

status CreatList(List* L)//21号功能，建立多项式
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
			P->next->xishu+=Q->xishu;//如果同一个次数出现两边，则合并
			continue;
		}
		Q->next=P->next;
		P->next=Q;
		L->len_list++;
	}
	return OK;
}

void ShowList(List* L)//22号功能，输出多项式
{
	node* P=L->head;
	int is_0=1;
	int is_1st=1;
	while(P->next!=NULL)
	{
		P=P->next;
		if(P->xishu!=(int)(P->xishu))//如果系数不为整数
		{
			if(P->xishu<0)//如果系数为负数
			{
				if((P->cishu!=0)&&(P->cishu!=1))
					printf("%.1fx^%d",P->xishu,P->cishu);
				else if(P->cishu==0)
					printf("%.1f",P->xishu);
				else
					printf("%.1fx",P->xishu);
			}
			else//如果系数为正数
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
		else//如果系数为整数
		{
			if(P->xishu==0)//如果系数为0
				continue;
			else if(P->xishu<0)//如果系数为负数
			{
				if(P->xishu==-1)//如果系数为-1
				{
					if((P->cishu!=0)&&(P->cishu!=1))
						printf("-x^%d",P->xishu,P->cishu);
					else if(P->cishu==0)
						printf("-1",P->xishu);
					else
						printf("-x",P->xishu);
				}
				else//如果系数为其他负数
				{
					if((P->cishu!=0)&&(P->cishu!=1))
						printf("%.0fx^%d",P->xishu,P->cishu);
					else if(P->cishu==0)
						printf("%.0f",P->xishu);
					else
						printf("%.0fx",P->xishu);
				}
			}
			else//如果系数为正数
			{
				if(is_1st!=1)
					printf("+");
				if(P->xishu==1)//如果系数为1
				{
					if((P->cishu!=0)&&(P->cishu!=1))
						printf("x^%d",P->xishu,P->cishu);
					else if(P->cishu==0)
						printf("1",P->xishu);
					else
						printf("x",P->xishu);
				}
				else//如果系数为其他正数
				{
					if((P->cishu!=0)&&(P->cishu!=1))
						printf("%.0fx^%d",P->xishu,P->cishu);
					else if(P->cishu==0)
						printf("%.0f",P->xishu);
					else
						printf("%.0fx",P->xishu);
				}
			}
			is_0=0;//如果结果不为0，则is_0为0
		}
		is_1st=0;//判断是否为第一项，用来判断是否要输出+和-
	}
	if(is_0==1)
		printf("0");//如果is_0为1，说明结果为0，则直接输出0
	printf("\n");
}

void Insert2(List* L,float xi_shu,int ci_shu)//附加功能，插入多项式的项，给后面功能用
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

void AddList(List* L1,List* L2,List* L3)//23号功能，指定两个多项式相加
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

void MinusList(List* L1,List* L2,List* L3)//24号功能，指定两个多项式相减
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

int main()//开始main()函数
{
	printf(" Menu for Linear Table On Sequence Structure\n");
	printf("-------------------------------------------------\n");
	printf("0.Exit\t\t\t19.SetListnum\n");
	printf("1.InitList\t\t7.LocateElem\n");
	printf("2.DestroyList\t\t8.PriorElem\n");
	printf("3.ClearList\t\t9.NextElem\n");
	printf("4.ListEmpty\t\t10.ListInsert\n");
	printf("5.ListLength\t\t11.ListDelete\n");
	printf("6.GetElem\t\t12.ListTrabverse\n");
	printf("21.CreatList\t\t22.ShowList\n");
	printf("23.AddList\t\t24.MinusList\n");
	printf("-------------------------------------------------\n");
	printf("要开始，请先用19号功能选择一个线性表\n");
	op=1;
	while(op)
	{	
		cin>>op;
		if(Init_flag[which_List]!=1&&(op!=1&&op!=19))//如果还没有创建该线性表
			printf("该线性表还未创建！请先创建%d号线性表！\n",which_List);
		else
			switch(op)
			{
				case 1:
					if(InitList(pList0)==OK)	//线性表创建成功
					{
						printf("%d号线性表创建成功!\n",which_List);
						Init_flag[which_List]=1;
					}
					else						//线性表创建失败
						printf("%d号线性表创建失败!\n",which_List);
					break;
				case 2:
					if(DestroyList(pList0)==OK)	//线性表销毁成功
					{
						printf("%d号线性表销毁成功!\n",which_List);
						Init_flag[which_List]=0;
					}
					else						//线性表销毁失败
						printf("%d号线性表销毁成功!\n",which_List);
					break;
				case 3:
					if(ClearList(pList0)==OK)   //清空线性表成功
						printf("%d号线性表清空成功!\n",which_List);
					else						//清空线性表失败
						printf("%d号线性表清空失败!\n",which_List);
					break;
				case 4:
					if(ListEmpty(pList0)==TRUE)	//该链表为空表
						printf("%d号链表为空表\n",which_List);
					else						//该链表不为空表
						printf("%d号链表不为空表\n",which_List);
					break;
				case 5:
					printf("%d号链表长度为%d\n",which_List,ListLength(pList0));//该链表长度为ListLength(pList0)
					break;
				case 6:
					printf("输入你要获取的元素的位置i:\n");
					cin>>get_i;//输入你要获取的元素的位置i
					if(GetElem(pList0,get_i,&e)==ERROR)
						printf("没有这个位置\n");	//如果没有这个位置
					else
						printf("该位置处元素为%c\n",e);//如果所找位置上有元素，输出该元素
					break;
				case 7:
					printf("请输入要查找的元素e:\n");
					cin>>e;
					if(LocateElem(pList0,e)==ERROR)
						printf("没有找到该元素\n");//如果没有找到
					else
						printf("所找元素位置在%d\n",LocateElem(pList0,e));//如果找到了，输出所找元素位置LocateElem(pList0,e)
					break;
				case 8:
					if(PriorElem(pList0,e,&e)==ERROR)
						printf("该元素前驱不存在\n");//如果没有前驱
					else
						printf("该元素前驱为%c\n",e);//如果有前驱，输出前驱e
					break;
				case 9:
					if(NextElem(pList0,e,&e)==ERROR)
						printf("该元素后继不存在\n");//如果没有后继
					else
						printf("该元素后继为%c\n",e);//如果有后继，输出前驱e
					break;
				case 10:
					printf("请输入要插入的位置i和元素e:\n");
					cin>>insert_position>>insert_e;//输入要插入的位置i和元素e
					if(ListInsert(pList0,insert_position,insert_e)==OK)
						printf("插入成功\n");//插入成功
					else
						printf("插入失败\n");//插入失败
					break;
				case 11:
					printf("请输入要删除的元素位置:\n");
					cin>>delete_position;//输入要删除的元素位置
					if(ListDelete(pList0,delete_position,&delete_e)==OK)
						printf("删除成功，被删除元素为%c\n",delete_e);//如果删除成功，输出被删除元素数据
					else
						printf("该位置不存在元素\n");//如果删除失败
					break;
				case 12:
					if(ListTrabverse(pList0)==ERROR)
						printf("遍历失败\n");//遍历失败
					else
						;//遍历成功，函数中输出了遍历结果
					break;
				case 19:
					printf("请输入要切换的线性表的序号:\n");
					cin>>which_List;//输入要切换的链表的序号
					pList0=&list[which_List];//将当前工作链表指针值换成选择的链表的地址
					printf("当前工作线性表被切换为%d号\n",which_List);
					break;
				case 21:
					if(CreatList(pList0)==OK)
						printf("多项式创建成功\n");//创建多项式成功
					else
						printf("多项式创建失败\n");//创建多项式失败
					break;
				case 22:
					printf("请输入要输出的多项式的序号:\n");
					cin>>print_which_list;//输入要输出的多项式的序号
					List_print=&list[print_which_list];
					ShowList(List_print);
					break;
				case 23:
					printf("请输入要进行加法的两个多项式的序号以及储存结果的多项式序号:\n");
					cin>>num_a>>num_b>>num_c;
					pLista=&list[num_a];
					pListb=&list[num_b];
					pListc=&list[num_c];
					ClearList(pListc);//先将储存结果的多项式清空
					AddList(pLista,pListb,pListc);
					printf("两个多项式已相加\n");
					break;
				case 24:
					printf("请输入要进行减法的两个多项式的序号以及储存结果的多项式序号:\n");
					cin>>num_a>>num_b>>num_c;
					pLista=&list[num_a];
					pListb=&list[num_b];
					pListc=&list[num_c];
					ClearList(pListc);//先将储存结果的多项式清空
					MinusList(pLista,pListb,pListc);
					printf("两个多项式已相减\n");
					break;
				case 0:
					printf("谢谢使用！\n");
					break;
			}//结束switch
  	}//结束while
}//结束main()
