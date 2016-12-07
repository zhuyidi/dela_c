/*************************************************************************
	> File Name: createTreeAndPrint.c
	> Author: zhuyidi
	> Mail: 1311243087@qq.com
	> Created Time: Thu 24 Nov 2016 05:45:06 PM CST
 ************************************************************************/

#include<stdio.h>
#include<malloc.h>

typedef char USERTYPE;

typedef struct BITREE
{
    USERTYPE data;
    struct BITREE *Lchild;
    struct BITREE *Rchild;
}BITREE;

int leafNode = 0;
int oneNode = 0;
int twoNode = 0;
int i = 0;
USERTYPE leaf[100] = {0};

void createBiTree(BITREE **root);   //由于主函数中定义的是树的根指针而非根结点, 所以这里要用**
void calculate(BITREE *root);

void calculate(BITREE *root)
{
    if(root)
    {
        if(root->Lchild && root->Rchild)
        {
            twoNode++;
        }

        if((root->Lchild && !root->Rchild) || (!root->Lchild && root->Rchild))
        {
            oneNode++;
        }

        if(!root->Lchild && !root->Rchild)
        {
            leafNode++;
            leaf[i++] = root->data;
        }

        calculate(root->Lchild);
        calculate(root->Rchild);
    }
}

void createBiTree(BITREE **root)
{
    char ch;
    ch = getchar();

    if(ch == '#')
    {
        root = NULL;
    }
    else
    {
        *root = (BITREE *)malloc(sizeof(BITREE));
        (*root)->data = ch;
        createBiTree(&((*root)->Lchild));
        createBiTree(&((*root)->Rchild));
    }
}

int main(int argc,char *argv[])
{
    BITREE *tree = NULL;    //为什么要定义根指针而不是根结点, 因为一棵树也存在没有一个结点的情况

    createBiTree(&tree);
   
    calculate(tree);
    printf("%d %d %d\n", leafNode, oneNode, twoNode);
    printf("%s\n", leaf);

    return 0;
}
