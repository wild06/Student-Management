#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <stdlib.h>

typedef struct Student
{
	char name[20];
	int num;
	float score;
	char address[20];
}Std;

typedef struct Node
{
	Std data;
	struct Node* next;
}LNode, * LinkList;

LinkList List;

LinkList createList()
{
	LinkList headnode = (LinkList)malloc(sizeof(LNode));
	headnode->next = NULL;
	return headnode;
}

LinkList createNode(Std data)
{
	LinkList newnode = (LinkList)malloc(sizeof(LNode));
	newnode->data = data;
	newnode->next = NULL;
	return newnode;
}

void insertNode(LinkList headnode, Std data)
{
	LinkList newnode = createNode(data);
	while (headnode->next != NULL)
	{
		headnode = headnode->next;
	}
	newnode->next = headnode->next;
	headnode->next = newnode;
}

void deleteNode(LinkList headnode, int num)
{
	LinkList PreNode = headnode;
	LinkList Nodetail = headnode->next;
	while (Nodetail->data.num!=num)
	{
		PreNode = Nodetail;
		Nodetail = Nodetail->next;
	}
	PreNode->next = Nodetail->next;
	free(Nodetail);
}

void PrintList(LinkList headnode)
{
	if(headnode->next == NULL)
	{
		printf("空链表\n");
		return;
	} 
	LinkList pmove = headnode->next;
	printf("姓名\t序号\t分数\t地址\n");	
	while (pmove != NULL)
	{
		printf("%s\t%d\t%0.1f\t%s\n", pmove->data.name, pmove->data.num, pmove->data.score, pmove->data.address);
		pmove = pmove->next;
	}
	printf("\n");
}

void deleteAllNode(LinkList headnode)
{
	LinkList pmove = headnode->next;
	LinkList e;
	while (pmove != NULL)
	{
		e = pmove;
		pmove = pmove->next;
		free(e);
	}
	// 释放头节点
	free(headnode);
	// 将List指向NULL，表示链表已清空
	List = NULL;
}


void WriteintoFile(LinkList headnode, char *filename)
{
	FILE* fp = fopen(filename,"w");
	if (headnode == NULL)
	{
		fclose(fp);
		return;
	}
	LinkList pmove = headnode->next;
	while (pmove != NULL)
	{
		fprintf(fp,"%s\t%d\t%f\t%s\n",pmove->data.name,pmove->data.num,pmove->data.score,pmove->data.address);
		pmove = pmove->next;
	}
	fclose(fp);
}

void ReadfromFile(LinkList headnode, char *filename)
{
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		fp = fopen(filename, "w+");
	}
	Std data;
	while(fscanf(fp,"%s\t%d\t%f\t%s\n",data.name,&data.num,&data.score,data.address)!=EOF)
	{
		insertNode(List, data);
	}
	fclose(fp);
}

void Createmenu()
{
	printf("\t\t欢迎来到学生管理系统\n");
	printf("\t\t1.添加学生信息\n");
	printf("\t\t2.删除学生信息\n");
	printf("\t\t3.打印学生信息\n");
	printf("\t\t4.删除所有学生信息\n");
	printf("\t\t5.退出系统\n");
	printf("请输入您的操作码\n");
}

void Keydown()
{
	int key = 0;
	scanf("%d", &key);
	Std data;
	switch (key)
	{
	case 1:
		printf("请输入学生的所有信息：\n");
		scanf("%s%d%f%s", data.name, &data.num, &data.score, data.address);
		insertNode(List, data);
		WriteintoFile(List, "Std.txt");
		break;
	case 2:
		printf("请输入您想删除的学生的序号:\n");
		int num;
		scanf("%d", &num);
		deleteNode(List, num);
		WriteintoFile(List, "Std.txt");
		break;
	case 3:
		printf("以下是所有的学生信息\n");
		PrintList(List);
		break;
	case 4:
		deleteAllNode(List);
		WriteintoFile(List, "Std.txt");
		break;
	case 5:
		printf("期待您的下次使用\n");
		system("pause");
		exit(0);
		break;
	}
}

int main()
{
	List = createList();
	ReadfromFile(List, "Std.txt");
	while (1)
	{
		Createmenu();
		Keydown();
		system("pause");
		system("cls");
	}
	return 0;
}
