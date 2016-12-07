/*************************************************************************
	> File Name: STACK.h
	> Author: zhuyidi
	> Mail: 1311243087@qq.com
	> Created Time: Mon 31 Oct 2016 10:48:11 AM CST
 ************************************************************************/

#ifndef _STACK_H
#define _STACK_H

#include<malloc.h>

typedef unsigned char boolean;

#define TRUE    1
#define FALSE   0

typedef struct{
    USER_TYPE *stack;
    int maxRoom;
    int top;
}STACK;

boolean initStack(STACK **head, int maxRoom);   //栈的初始化
void destroyStack(STACK **head);                //栈的销毁(传参为控制头指针的首地址)
boolean isStackFull(STACK head);               //判栈满
boolean isStackEmpty(STACK head);              //判栈空
boolean push(STACK *head, USER_TYPE value);
boolean pop(STACK *head, USER_TYPE *value);
boolean readTop(STACK head, USER_TYPE *value);

boolean readTop(STACK head, USER_TYPE *value)
{
    if(TRUE == isStackEmpty(head))
    {
        return FALSE;
    }

    *value = head.stack[--head.top];

    return FALSE;
}

boolean pop(STACK *head, USER_TYPE *value)
{
    if(TRUE == isStackEmpty(*head))
    {
        return FALSE;
    }

    *value = head->stack[--head->top];

    return TRUE;
}

boolean push(STACK *head, USER_TYPE value)
{
    if(TRUE == isStackFull(*head))
    {
        return FALSE;
    }

    head->stack[head->top++] = value;

    return TRUE;
}

boolean isStackEmpty(STACK head) 
{
    if(head.top == 0)
    {
        return TRUE;
    }

    return FALSE;
}

boolean isStackFull(STACK head)
{
    if(head.top == head.maxRoom)      //也可写成>=, 因为此处由于c语言的特性, 
    {                                   //数组下标从0开始, 所以当top==maxRoom时, 就说明栈已满
        return TRUE;
    }                           
    
    return FALSE;
}

void destroyStack(STACK **head)
{
    //先free stack成员所申请的一段内存空间
    free((*head)->stack);

    //再free 控制头指针指向的空间, 并将控制头指针赋值为NULL
    free(*head);
    *head = NULL;
}

boolean initStack(STACK **head, int maxRoom)
{
    if(NULL != *head)
    {
        return FALSE; 
    }
    
    *head = (STACK *)malloc(sizeof(STACK));

    if(NULL == (*head))
    {
        return FALSE;
    }

    (*head)->stack = (USER_TYPE *)malloc(sizeof(USER_TYPE)*maxRoom);

    if(NULL == (*head)->stack)
    {
        free(*head);    //当stack成员申请空间失败时, 一定要先释放控制头指针, 然后将控制头指针恢复为NULL

        (*head) = NULL;
        return FALSE;
    }
    
    (*head)->maxRoom = maxRoom;
    (*head)->top = 0;

    return TRUE;
}

#endif
