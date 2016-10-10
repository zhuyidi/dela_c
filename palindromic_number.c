/*************************************************************************
	> File Name: palindromic_number.c
	> Author: zhuyidi
	> Mail: 1311243087@qq.com
	> Created Time: Mon 10 Oct 2016 08:25:27 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[])
{
    int number;
    int numbertmp;
    char tmp1[10] = {0};
    char tmp2[10] = {0};
    int i;
    int len;

    scanf("%d", &number);

    sprintf(tmp1, "%d", number);

    len = strlen(tmp1);
    
    for(i = 0; i < len; i++)
    {
        tmp2[len-i-1] = tmp1[i];
    }

    numbertmp = atoi(tmp2);

    if(number == numbertmp)
    {
        printf("yes\n");
    }
    else
    {
        printf("no\n");
    }
}
