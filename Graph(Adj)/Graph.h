#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#define MaxSize 100
typedef char ElemType;

typedef int BOOL;
#define FALSE 0
#define TRUE  1

typedef struct{
    ElemType data[MaxSize];
    int front, rear;
}SqQueue;


#endif // GRAPH_H_INCLUDED
