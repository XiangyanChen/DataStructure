#include <stdio.h>
#include <stdlib.h>

#define ElemType char
#define MAXSIZE 100
#define BOOL int
#define FALSE 0
#define TRUE  1

typedef struct{
    ElemType data[MAXSIZE];
    int front, rear;
}Queue;

void InitQueue(Queue *queue);   //初始化队列
BOOL IsEmpty(Queue *queue); //判断是否为空
void EnQueue(Queue *queue, ElemType x); //入队
void DeQueue(Queue *queue, ElemType *x);    //出队

int main()
{
    Queue q;
    InitQueue(&q);
    ElemType e;
    printf("%d\n", IsEmpty(&q));
    EnQueue(&q, 'a');
    EnQueue(&q, 'b');
    DeQueue(&q, &e);
    printf("%c\n", e);
    printf("%d\n", IsEmpty(&q));
    DeQueue(&q, &e);
    printf("%c\n", e);
    printf("%d\n", IsEmpty(&q));
    return 0;
}

void InitQueue(Queue *queue){
    queue->front = 0;
    queue->rear = 0;
}

void EnQueue(Queue *queue, ElemType e){
    queue->data[queue->rear] = e;
    queue->rear = (queue->rear + 1) % MAXSIZE;
}

void DeQueue(Queue *queue, ElemType *e){
    *e = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAXSIZE;
}

BOOL IsEmpty(Queue *queue){
    if (queue->front == queue->rear) {
        return TRUE;
    } else {
        return FALSE;
    }
}
