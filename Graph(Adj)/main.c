#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "Graph.h"
#define MAXVEX 100 /* 最大顶点数,应由用户定义 */
typedef char VertexType; /* 顶点类型应由用户定义 */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */

int visited[200];

typedef struct EdgeNode/* 边表结点  */
{
    int adjvex;/* 邻接点域,存储该顶点对应的下标 */
    EdgeType weight;/* 用于存储权值,对于非网图可以不需要 */
    struct EdgeNode *next; /* 链域,指向下一个邻接点 */
} EdgeNode;

typedef struct VextexNode/* 顶点表结点 */
{
    VertexType data;/* 顶点域,存储顶点信息 */
    EdgeNode *firstedge;/* 边表头指针 */
} VextexNode, AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;
    int numNodes, numEdges; /* 图中当前顶点数和边数 */
} GraphAdjList;

EdgeNode* FirstAdjVex(GraphAdjList graph, VertexType data);
EdgeNode* NextAdjVex(GraphAdjList graph, VertexType data, int adjvex);
void DFS(GraphAdjList graph, VertexType data);
void BFS(GraphAdjList graph, VertexType data);
void BFSTraverse(GraphAdjList graph);
int main()
{
    GraphAdjList graph;
    /*
    printf("请输入顶点数, 边数：");
    scanf("%d %d", &graph.numNodes, &graph.numEdges);
    getchar();
    */
    int i, j;
    /*
    for (i = 0; i < graph.numNodes; ++i){
        printf("请输入顶点：");
        scanf("%c", &graph.adjList[i].data);
        getchar();  //消除空白符
        graph.adjList[i].firstedge = NULL;
    }
    */

  //  int i, j;
    graph.numNodes = 6;
    graph.numEdges = 6;
    graph.adjList[0].data = 'A';
    graph.adjList[0].firstedge = NULL;
    graph.adjList[1].data = 'B';
    graph.adjList[1].firstedge = NULL;
    graph.adjList[2].data = 'C';
    graph.adjList[2].firstedge = NULL;
    graph.adjList[3].data = 'D';
    graph.adjList[3].firstedge = NULL;
    graph.adjList[4].data = 'E';
    graph.adjList[4].firstedge = NULL;
    graph.adjList[5].data = 'F';
    graph.adjList[5].firstedge = NULL;
    //getchar();

    for (i = 0; i < graph.numEdges; ++i){
        printf("请输入起点， 终点：");
        char start, end;
        VextexNode* startNode;  //找出弧尾结点，弧头结点
        scanf("%c %c", &start, &end);
        EdgeNode* newNode = (EdgeNode*)malloc(sizeof(EdgeNode));    //创建新节点
        for (j = 0; j < graph.numNodes; ++j){
            if (graph.adjList[j].data == start){
                startNode = &graph.adjList[j];
            }
            if (graph.adjList[j].data == end){

                newNode->adjvex = j;
                newNode->next = NULL;
            }
        }
        EdgeNode* edgeNode = startNode->firstedge;
        if (edgeNode != NULL){
            while(edgeNode->next != NULL){    //循环到最后一个结点
                edgeNode = edgeNode->next;
            }
            edgeNode->next = newNode;
        } else {
            startNode->firstedge = newNode;
        }
        getchar();
    }
    for (i = 0; i < graph.numEdges; ++i){
        printf("Vex:%c", graph.adjList[i].data);
        EdgeNode* edgeNode = graph.adjList[i].firstedge;
        if (edgeNode != NULL){
            printf(" ->Edge:%c", graph.adjList[edgeNode->adjvex].data);
            while(edgeNode->next != NULL){    //循环到最后一个结点
                edgeNode = edgeNode->next;
                printf(" ->Edge:%c", graph.adjList[edgeNode->adjvex].data);
            }
        }
        printf("\n");
    }
    for (i = 0; i < 200; ++i){
        visited[i] = 0;
    }
    printf("DFS:");
    DFS(graph, graph.adjList[0].data);
    printf("\n-----------\n");
    for (i = 0; i < 200; ++i){
        visited[i] = 0;
    }
    printf("BFS:");
    BFS(graph, graph.adjList[0].data);
    return 0;
}

/*
    寻找第一个边结点
*/
EdgeNode* FirstAdjVex(GraphAdjList graph, VertexType data){
    int i;
    for (i = 0; i < graph.numNodes; ++i){
        if (graph.adjList[i].data == data){ //找到结点
            //printf("ccc ");
            return graph.adjList[i].firstedge;
        }
    }
    return NULL;
}

/*
    寻找下一个边结点
*/
EdgeNode* NextAdjVex(GraphAdjList graph, VertexType data, int adjvex){
    int i;
    for (i = 0; i < graph.numNodes; ++i){
        if (graph.adjList[i].data == data){//找到结点
            EdgeNode* edgeNode = graph.adjList[i].firstedge; //找到第一个边结点
            while (edgeNode != NULL && edgeNode->adjvex != adjvex){
                edgeNode = edgeNode->next;
            }
            if (edgeNode != NULL){  //说明找到
                return edgeNode->next;
            } else {
                return NULL;
            }
        }
    }
    return NULL;
}

/*
    深度遍历
*/
void DFS(GraphAdjList graph, VertexType data){
    visited[data] = 1;
    printf("%c ", data);
    EdgeNode *p;
    for (p = FirstAdjVex(graph, data); p != NULL; p=NextAdjVex(graph, data, p->adjvex)){
        if (visited[graph.adjList[p->adjvex].data] != 1){    //没访问过
            DFS(graph, graph.adjList[p->adjvex].data);
        }
    }
}

/*
    广度遍历
*/
void BFSTraverse(GraphAdjList graph){
    int i;
    BFS(graph, graph.adjList[0].data);
    /*
    for (i = 0; i < graph.numNodes; ++i){
        if (visited[graph.adjList[i].data] != 1){
            BFS(graph, graph.adjList[i].data);
        }
    }
    */
}

/*
    广度遍历
*/
void BFS(GraphAdjList graph, VertexType data){
    SqQueue queue;
    InitQueue(&queue);
    EnQueue(&queue, data);
    ElemType x;
    EdgeNode *p;
    visited[data] = 1;
    while (!QueueEmpty(&queue)){
        DeQueue(&queue, &x);
        printf("%c ", x);
        for (p = FirstAdjVex(graph, x); p != NULL; p=NextAdjVex(graph, x, p->adjvex)){
            if (visited[graph.adjList[p->adjvex].data] != 1){
                EnQueue(&queue, graph.adjList[p->adjvex].data);
                visited[graph.adjList[p->adjvex].data] = 1;
            }
        }
    }
}
