/*************************************************************************
	> File Name: queue_palindrpmic_number.c
	> Author: zhuyidi
	> Mail: 1311243087@qq.com
	> Created Time: Wed 02 Nov 2016 09:16:38 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>

typedef char USER_TYPE;

#include"QUEUE.h"

int main(int argc,char *argv[])
{
    QUEUE *numQueue = NULL;
    char number[50] = {0};
    char tmp;
    int len = 0;
    int i = 0;

    printf("请输入一个数:");
    scanf("%s", number);
    len = strlen(number);

    initQueue(&numQueue, len/2);

    for(i = 0; i <= len/2 - 1; i++)
    {
        if(!inputQueue(numQueue, number[i]))
        {
            printf("inputQueue error\n");
            return -1;
        }
    }

    i = len - 1;

    while(!isQueueEmpty(*numQueue))
    {
        if(!outputQueue(numQueue, &tmp))
        {
            printf("outputQueue error\n");
            return -1;
        }

        if(tmp != number[i--])
        {
            printf("no\n");
            return -1;
        }
    }

    printf("yes\n");

    destroyQueue(&numQueue);
    return 0;
}
