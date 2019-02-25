#include "Graph.h"

void InitQueue(SqQueue *queue);
BOOL QueueEmpty(SqQueue *queue);
void EnQueue(SqQueue *queue, ElemType x);
void DeQueue(SqQueue *queue, ElemType *x);


void InitQueue(SqQueue *queue){
    queue->front = 0;
    queue->rear = 0;
}

BOOL QueueEmpty(SqQueue *queue){
    if (queue->front == queue->rear) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void EnQueue(SqQueue *queue, ElemType x){
    queue->data[queue->rear] = x;
    queue->rear = (queue->rear + 1) % MaxSize;
}


void DeQueue(SqQueue *queue, ElemType *x){
    *x = queue->data[queue->front];
    queue->front = (queue->front + 1) % MaxSize;
}
