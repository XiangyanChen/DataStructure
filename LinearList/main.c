#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define INCREMENT 50

typedef int BOOL;
#define TRUE 1
#define FALSE 0
typedef char ElemType;

typedef struct{
    ElemType data[SIZE]; //元素数组
    int length; //长度
    int capacity;   //容量
}SqList;

void InitList(SqList* list); //初始化顺序表
BOOL Insert(SqList* list, ElemType e, int i);   //插入
BOOL Delete(SqList* list, ElemType e);   //删除
BOOL IsEmpty(SqList* list);  //判断为空

int main()
{
    SqList list;
    InitList(&list);
    printf("%d\n", IsEmpty(&list));
    Insert(&list, 'a', 1);
    printf("%d\n", IsEmpty(&list));
    Delete(&list, 'b');
    printf("%d\n", IsEmpty(&list));
    Delete(&list, 'a');
    printf("%d\n", IsEmpty(&list));
    return 0;
}

void InitList(SqList* list){
    list->length = 0;
    list->capacity = SIZE;
}

BOOL Insert(SqList* list, ElemType e, int pos){   //i的范围1<=pos<=n
    int i;
    ++list->length;
    for (i = list->length; i > pos-1; --i){
        list->data[list->length] = list->data[list->length-1];
    }
    list->data[pos-1] = e;
    return TRUE;
}

BOOL Delete(SqList* list, ElemType e){
    int i, j;
    for (i = 0; i < list->length; ++i){
        if (list->data[i] == e){    //找到该元素
            for (j = i; j < list->length; ++j){
                list->data[j] = list->data[j+1];
                --list->length;
                return TRUE;
            }
        }
    }
    return FALSE;
}

BOOL IsEmpty(SqList* list){
    if (list->length == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}
