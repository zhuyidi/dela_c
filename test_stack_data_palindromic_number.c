/*************************************************************************
	> File Name: data_palindromic_number.c
	> Author: zhuyidi
	> Mail: 1311243087@qq.com
	> Created Time: Fri 21 Oct 2016 10:26:19 AM CST
 ************************************************************************/

#include<stdio.h>
#include<malloc.h>
#include<string.h>

#define MAXSIZE 20
#define TRUE    1
#define FALSE   0

typedef struct SeqStack
{
    char data[MAXSIZE];
    int top;
}SeqStack;

SeqStack *initSepStack();
int pushSepstack(SeqStack *stack, char chars);
int fullSepstack(SeqStack *stack);
int popSepstack(SeqStack *stack, char *tmp);
int emptySepstack(SeqStack *stack);

int emptySepstack(SeqStack *stack)
{
    if(stack->top == -1)
    {
        return TRUE;
    }

    return FALSE;
}

int popSepstack(SeqStack *stack, char *tmp)
{
    if(emptySepstack(stack))
    {
        return FALSE;
    }

    *tmp = stack->data[stack->top];
    stack->top--;
    
    return TRUE;
}

int fullSepstack(SeqStack *stack)
{
    if(stack->top == MAXSIZE - 1)
    {
        return TRUE;
    }

    return FALSE;
}

int pushSepstack(SeqStack *stack, char chars)
{
    if(fullSepstack(stack))
    {
        return FALSE;
    }

    stack->top++;
    stack->data[stack->top] = chars;

    return TRUE;
}

SeqStack *initSepStack()
{
    SeqStack *stack;

    stack = (SeqStack *)malloc(sizeof(SeqStack));
    stack->top = -1;

    return stack;
}

int main(int argc,char *argv[])
{
    char number[MAXSIZE] = {0};
    SeqStack *stack;
    char tmp;
    int i;
    int len;

    scanf("%s", number);

    stack = initSepStack();
    
    len = strlen(number);

    for(i = len/2-1; i >= 0; i--)
    {
        if(!pushSepstack(stack, number[i]))
        {
            return -1;
        }
    }

    for(i = len-1; i > len/2; i--)
    {
        if(!popSepstack(stack, &tmp))
        {
            return -1;
        }

        if(tmp != number[i])
        {
            printf("no\n");
            return 0;
        }
    }

    printf("yes\n");
    return 0;
}
