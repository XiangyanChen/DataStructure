#include <stdio.h>

typedef struct BiTnode{
    char data;
    struct BiTnode *lchild, *rchild;
}*BiTree, BiTNode;

void PreOrder(BiTree T);	//前序遍历
void InOrder(BiTree T);	//中序遍历
void PostOrder(BiTree T);	//后序遍历
void CreateBiTree(BiTree* T);	//创建树
int Depth(BiTree T);

int main() {
    BiTree T;
    CreateBiTree(&T);
    printf("PreOrder:");
    PreOrder(T);
    printf("\n");
    printf("InOrder:");
    InOrder(T);
    printf("\n");
    printf("PostOrder:");
    PostOrder(T);
    printf("\n");
    printf("Depth:%d", Depth(T));
    printf("\n");
    return 0;
}

void CreateBiTree(BiTree* T) {   //以先序遍历创建树
    char ch;
    if ((ch = getchar()) == '\n')
    {
        return;
    }
    if (ch == '#')
    {
        (*T) = NULL;
    }
    else
    {
        *T = (BiTNode *)malloc(sizeof(BiTNode));
        (*T)->data = ch;
        CreateBiTree(&((*T)->lchild)); //因为要传入一个(struct BiTnode *lchild)的指针，也就是指针的指针
        CreateBiTree(&((*T)->rchild));
    }
}

void PreOrder(BiTree T) {
    if (T != NULL) {
        printf("%c ", T->data);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BiTree T) {
    if (T != NULL) {
        InOrder(T->lchild);
        printf("%c ", T->data);
        InOrder(T->rchild);
    }
}

void PostOrder(BiTree T) {
    if (T != NULL) {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        printf("%c ", T->data);
    }
}

int Depth(BiTree T) {
    if(T == NULL) {
        return 0;
    } else {
        int m = Depth(T->lchild);
        int n = Depth(T->rchild);
        if (m > n) {
            return (m+1);
        }
        else {
            return (n+1);
        }
    }
}
