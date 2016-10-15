/*************************************************************************
	> File Name: in_and_out_conversion.c
	> Author: zhuyidi
	> Mail: 1311243087@qq.com
	> Created Time: Fri 14 Oct 2016 08:38:55 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<malloc.h>

void inConversion(int num, unsigned char *charNum);
int outCoversion(unsigned char *charNum);

int outCoversion(unsigned char *charNum)
{
    int num = 0;
    
    num += (*charNum++) * 1;
    num += (*charNum) * 256;

    return num;
}

void inConversion(int num, unsigned char *charNum)
{
    //char charNum[5];      
    //不能用数组名称作为函数的返回值是因为:数组是定义在子函数里面的,是局部变量,
    //随着子函数的运行结束而将这段内存空间释放,那么这段内存空间的地址也无处可循,所以是错误的
    //解决方法: 1.将charNum定义成一个字符串指针 
    //          *定义成字符串指针也不行,因为字符串指针存储的是字符数组的首地址,字符数组的地址空间已经被释放,
    //           字符串指针指向的空间变成了垃圾数据,无法正确返回正确的数据
    //          2.定义charNum数组时加static,即:static char charNum[5];
    
    for(; num; charNum++)
    {
        *charNum = num&0x00ff;
        num = num >> 8;
    }
}

int main(int argc,char *argv[])
{
    int num = 0;
    unsigned char *charNum;

    charNum = (char *)malloc(sizeof(char)*3);
    scanf("%d", &num);

    inConversion(num, charNum);
   
    num = 0;
    num = outCoversion(charNum);
    
    printf("num:%d\n", num);
}
