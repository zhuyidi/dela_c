#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct STU 
{
	int num;
	char name[20];
	char sex;
	short age;
	struct STU *next;
}STU;

void initList(STU *head);
void showList(STU head);
void deleList(STU *head);
STU *findPre(STU head, short oldAge);

STU *findPre(STU head, short oldAge)
{
	STU *p;
	STU *q = NULL;

	for(p = head.next; p && !( p->age == oldAge); p = p->next)
	{
		q = p;
	}
	return q;
}

void deletList(STU *head)
{
	STU *p;
	STU *q;
	STU *pre;
	short oldAge;

	printf("现在开始进行删除操作！\n");
	printf("请输入要删除节点的年龄值：\n");
	scanf("%hd", &oldAge);
	
	pre = findPre(*head, oldAge);
	
	if(pre->next == NULL)
	{
		printf("没有该年龄的学生, 删除失败！\n");
	}
	else
	{
		while(p)
		{
			pre = findPre(*head, oldAge);
			
			if(pre->next->next == NULL)
			{
				q = pre->next;
				pre->next = NULL;
				free(q);
			}
			else
			{
				if(pre == NULL)
				{
					pre = head->next;
				}
				q = pre->next;
				pre->next = q->next;
				free(q);
				
				p = pre->next;		
			}	
		}
	
		printf("删除成功！");
	}
}

void showList(STU head)
{
	STU *p;

	printf("当前学生信息如下：\n");
	for(p = head.next; p; p = p->next)
	{
		printf("%5d %10s %5c %5d\n", p->num, p->name, p->sex, p->age);
	}
	printf("\n");
}

void initList(STU *head)
{
	STU *p;
	STU *q;
	int num;
	char name[20];
	char sex;
	short age;

	printf("现在开始进行链表初始化！\n");
	printf("请输入学生的信息(当输入学号为0时，结束输入)：\n");

	scanf("%d", &num);
	
	while(num)
	{	
		scanf("%s", name);

		setbuf(stdin, NULL);
	
		scanf("%c", &sex);
		scanf("%hd", &age);
	
		p = (STU *)malloc(sizeof(STU));
		p->num = num;
		strcpy(p->name, name);
		p->sex = sex;
		p->age = age;
		p->next = NULL;
		
		if(head->next == NULL)
		{
			head->next = p;
		}
		else
		{
			q->next = p;
		}
		q = p;

		scanf("%d", &num);
	}
}

void main(void)
{
	STU head = {0};
	showList(head);

	deletList(&head);
	showList(head);
}
