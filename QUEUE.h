/*************************************************************************
	> File Name: QUEUE.h
	> Author: zhuyidi
	> Mail: 1311243087@qq.com
	> Created Time: Wed 02 Nov 2016 11:04:32 AM CST
 ************************************************************************/

#ifndef _QUEUE_H
#define _QUEUE_H

#include<malloc.h>

typedef unsigned char boolean;

#define TRUE    1
#define FALSE   0

typedef struct
{
    USER_TYPE *queue;
    int maxRoom;
    int front;
    int rear;
    int curNumber;
}QUEUE;

boolean initQueue(QUEUE **head, int maxRoom);
boolean isQueueEmpty(QUEUE head);
boolean isQueueFull(QUEUE head);
boolean inputQueue(QUEUE *head, USER_TYPE value);
boolean outputQueue(QUEUE *head, USER_TYPE *value);
void destroyQueue(QUEUE **head);

void destroyQueue(QUEUE **head)
{
    free((*head)->queue);
    free(*head);
    
    *head = NULL;
}

boolean outputQueue(QUEUE *head, USER_TYPE *value)
{
    if(TRUE == isQueueEmpty(*head))
    {
        return FALSE;
    }

    head->front = (head->front+1) % head->maxRoom;
    *value = head->queue[head->front];
    head->curNumber--;
    
    return TRUE;
}

boolean inputQueue(QUEUE *head, USER_TYPE value)
{
    if(TRUE == isQueueFull(*head))
    {
        return FALSE;
    }
    
    head->rear = (head->rear+1) % head->maxRoom;
    head->queue[head->rear] = value;
    head->curNumber++;

    return TRUE;
}

boolean isQueueFull(QUEUE head)
{
    if(head.curNumber == head.maxRoom)
    {
        return TRUE;
    }

    return FALSE;
}

boolean isQueueEmpty(QUEUE head)
{
    if(0 == head.curNumber)
    {
        return TRUE;
    }

    return FALSE;
}

boolean initQueue(QUEUE **head, int maxRoom)
{
    if((*head) != NULL)
    {
        return FALSE;
    }

    (*head) = (QUEUE *)malloc(sizeof(QUEUE));

    if(NULL == (*head))
    {
        return FALSE;
    }

    (*head)->queue = (USER_TYPE *)malloc(sizeof(USER_TYPE)*maxRoom);

    if(NULL == (*head)->queue)
    {
        free(*head);
        *head = NULL;

        return FALSE;
    }

    (*head)->maxRoom = maxRoom;
    (*head)->front = 0;
    (*head)->rear = 0;
    (*head)->curNumber = 0;

    return TRUE;
}

#endif
