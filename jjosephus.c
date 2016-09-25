/*************************************************************************
	> File Name: josephus.c
	> Author: zhuyidi
	> Mail: 1311243087@qq.com
	> Created Time: Wed 21 Sep 2016 08:13:30 PM CST
 ************************************************************************/

#include<stdio.h>
#include<malloc.h>

typedef struct List
{
    int nov;
    int number;
    struct List *next;
}List;

int startNum;

void initList(List *head);
void printList(List *head);
void dealList(List *head);

void dealList(List *head)
{
    List *p;
    List *q;
    List *r;
    int i;

    q = head;

    while(head->next != head)
    {
        for(p = q->next, i = 1; i != startNum; p = p->next, i++)
        {
            if(p->next == head)
            {
                p = p->next;
            }

            q = p;
        }
        
        q->next = p->next;
        startNum = p->number;
        printf("%d ", p->nov);
        r = p;
        free(r);
        
        i = 1;                      
        if(q->next == head)
        {
            q = q->next;
        }
    }
}

void initList(List *head)
{
    List *rear;
    List *p;
    int n;
    int num;
    int i = 0;
    int j = 1;

    head->next = head;
    rear = head;

    //输入总人数
    scanf("%d", &n);

    //输入初始密码
    scanf("%d", &startNum);

    for(i = 0; i < n; i++)
    {
        p = (List *)malloc(sizeof(List));
        
        //输入每个人的密码
        scanf("%d", &num);
        p->nov = j++;
        p->number = num;
        rear->next = p;
        rear = p;
        rear->next = head;
    }
}

int main(int argc,char *argv[])
{
    List head = {0};
    
    initList(&head);
    dealList(&head);

}
