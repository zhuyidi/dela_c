/*************************************************************************
	> File Name: stack_palindromic_number.c
	> Author: zhuyidi
	> Mail: 1311243087@qq.com
	> Created Time: Wed 02 Nov 2016 11:49:06 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>

typedef char USER_TYPE;

#include"STACK.h"

int main(int argc,char *argv[])
{
    STACK *numStack = NULL;
    char number[50] = {0};
    char tmp;
    int len = 0;
    int i = 0;

    printf("请输入一个数:");
    scanf("%s", number);
    len = strlen(number);

    initStack(&numStack, len/2);

    for(i = len/2-1; i >= 0; i--)
    {
        if(!push(numStack, number[i]))
        {
            printf("push error\n");
            return -1;
        }
    }
   
    i = len - 1;
    while(!isStackEmpty(*numStack))
    {
        if(!pop(numStack, &tmp))
        {
            printf("pop error\n");
            return -1;
        }
        
        if(tmp != number[i--])
        {
            printf("no\n");
            return -1;
        }
    }

    printf("yes\n");

    destroyStack(&numStack);
    return 0;
}
