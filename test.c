/*************************************************************************
	> File Name: test.c
	> Author: zhuyidi
	> Mail: 1311243087@qq.com
	> Created Time: 2016年07月23日 星期六 09时05分49秒
 ************************************************************************/

#include<stdio.h>

int main(int argc,char *argv[])
{
    char *p;
    char sz[20] = "abc";
    int tree;

    p = sz;
    tree = 0;

    for(; *p; p = p + 1)
    {
        if(*p == 'b')
        {
            tree = 1;
        }
    }

    printf("tree = %d\n", tree);
}
