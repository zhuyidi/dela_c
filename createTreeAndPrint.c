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

void createBiTree(BITREE **root);   //由于主函数中定义的是树的根指针而非根结点, 所以这里要用**
void visit(USERTYPE data);
void preOrder(BITREE *root);
void inOrder(BITREE *root);
void postOrder(BITREE *root);

void postOrder(BITREE *root)
{
    if(root)
    {
        postOrder(root->Lchild);
        postOrder(root->Rchild);
        visit(root->data);
    }
}

void inOrder(BITREE *root)
{
    if(root)
    {
        inOrder(root->Lchild);
        visit(root->data);
        inOrder(root->Rchild);
    }
}

void preOrder(BITREE *root)
{
    if(root)
    {
        visit(root->data);
        preOrder(root->Lchild);
        preOrder(root->Rchild);
    }
}

void visit(USERTYPE data)
{
    //访问该结点

    printf("%c", data);
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
    preOrder(tree);
    printf("\n");

    inOrder(tree);
    printf("\n");

    postOrder(tree);
    printf("\n");

    return 0;
}
