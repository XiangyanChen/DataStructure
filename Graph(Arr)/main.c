#include <stdio.h>
#include <stdlib.h>
#define INFINTE 65535
#define MAXSIZE 100
#include "stack.c"

typedef char VertexType;                //顶点类型应由用户定义
typedef int EdgeType;                   //边上的权值类型应由用户定义

enum VISITE{
      WHITE=0, GRAY=1, BLACK=2
};

typedef struct graph{
    VertexType vexs[MAXSIZE];            //顶点表
    EdgeType   arc[MAXSIZE][MAXSIZE];       //邻接矩阵
    int numNodes, numEdges;
}Graph;

int visited[200];

void CreateGraph(Graph* graph); //创建图
VertexType* FirstAdjVex(Graph graph, VertexType data);  //获取第一邻接点
VertexType* NextAdjVex(Graph graph, VertexType data, VertexType adj);   //获取下一邻接点
void DFSTraversal(Graph graph); //深度优先遍历
void DFSByStack(Graph graph, VertexType vex);
BOOL IsLoop(Graph graph, VertexType vex);

int main(){
    int i, j;
    Graph graph;
    CreateGraph(&graph);
    //打印邻接矩阵
    for (i = 0; i < graph.numNodes; ++i){
        for (j = 0; j < graph.numNodes; ++j){
            printf("%d ", graph.arc[i][j]);
        }
        printf("\n");
    }

    VertexType* adj = FirstAdjVex(graph, 'A');
    VertexType x = *adj;
    printf("%c ", x);
    adj = NextAdjVex(graph, 'A', x);
    x = *adj;
    printf("%c ", x);
    x = *adj;
    adj = FirstAdjVex(graph, 'D');
    printf("%c\n", *adj);
    for (i = 0; i < 200; ++i){
        visited[i] = 0;
    }
    DFSTraversal(graph);

    return 0;
}

void CreateGraph(Graph* graph){
    int i, j;
    //先把图的邻接矩阵置为0(0表示没边，1表示有边)
    for (i = 0; i < graph->numNodes; ++i){
        for (j = 0; j < graph->numNodes; ++j){
            graph->arc[i][j] = 0;
        }
    }
    //printf("请输入顶点数, 边数：");
    //scanf("%d %d", &graph->numNodes, &graph->numEdges);
    //getchar();
    graph->numNodes = 6;
    graph->numEdges = 6;
    /*
    for (i = 0; i < graph->numNodes; ++i){
        printf("请输入顶点：");
        scanf("%c", &graph->vexs[i]);
        getchar();  //消除空白符
    }
    */
    graph->vexs[0] = 'A';
    graph->vexs[1] = 'B';
    graph->vexs[2] = 'C';
    graph->vexs[3] = 'D';
    graph->vexs[4] = 'E';
    graph->vexs[5] = 'F';
    VertexType start, end;
    /*
    for (i = 0; i < graph->numEdges; ++i){
        printf("请输入起点， 终点：");
        scanf("%c %c", &start, &end);
        getchar();  //消除空白符
        int startIndex, endIndex;
        for (j = 0; j < graph->numNodes; ++j){  //找到起始点,终点
            if (start == graph->vexs[j]){
                startIndex = j;
            }
            if (end == graph->vexs[j]){
                endIndex = j;
            }
        }
        graph->arc[startIndex][endIndex] = 1;
        //如果是无向图，需要双向保存
        graph->arc[endIndex][startIndex] = 1;
    }
    */
    graph->arc[0][2] = 1;
    graph->arc[0][3] = 1;
    graph->arc[3][1] = 1;
    graph->arc[2][4] = 1;
    graph->arc[3][5] = 1;
    graph->arc[4][5] = 1;
    //如果是无向图，需要保存两个边
    graph->arc[2][0] = 1;
    graph->arc[3][0] = 1;
    graph->arc[1][3] = 1;
    graph->arc[4][2] = 1;
    graph->arc[5][3] = 1;
    graph->arc[5][4] = 1;
}


VertexType* FirstAdjVex(Graph graph, VertexType vex){
    //先找到data这个结点
    int i, j;
    for (i = 0; i < graph.numNodes; ++i){
        if (graph.vexs[i] == vex){
            for (j = 0; j < graph.numNodes; ++j){
                if (graph.arc[i][j] == 1){  //找到第一个邻接点
                    return &(graph.vexs[j]);
                }
            }
        }
    }
    return NULL;    //这步说明没找到
}


VertexType* NextAdjVex(Graph graph, VertexType vex, VertexType adj){
    int vexIndex, adjIndex, i;
    for (i = 0; i < graph.numNodes; ++i){
        if (graph.vexs[i] == vex){
            vexIndex = i;
        }
        if (graph.vexs[i] == adj){
            adjIndex = i;
        }
    }
    for (i = adjIndex + 1; i < graph.numNodes; ++i){  //从当前邻接点的后面寻找
        if (graph.arc[vexIndex][i] == 1){
            return &(graph.vexs[i]);
        }
    }
    return NULL;    //这步说明没找到
}

/* 深度优先遍历 */
void DFSTraversal(Graph graph){
    int i;
    //IsLoop(graph, graph.vexs[i]);
    printf("DFS:");
    IsLoop(graph, graph.vexs[0]);
    /*
    for (i = 0; i < graph.numNodes; ++i){
        if (visited[graph.vexs[i]] == WHITE) {
            IsLoop(graph, graph.vexs[i]);
            //DFSByStack(graph, graph.vexs[i]);
        }
    }
    */
}

void DFSByStack(Graph graph, VertexType vex){
    VertexType x;
    VertexType *p;
    Stack stack;
    InitStack(&stack);
    Push(&stack, vex);
    visited[vex] = 1;
    printf("%c ", vex);
    while (!IsEmpty(stack)){
        ElemType e;
        Pop(&stack, &e);    //出栈
        for (p = FirstAdjVex(graph, e); p != NULL; p=NextAdjVex(graph, e, x)){
            x = *p;
            if (visited[x] != 1){    //没访问过
                Push(&stack, e);
                Push(&stack, x);//如果有未访问过的就压栈
                printf("%c ", x);
                visited[x] = 1;
                break;
            }
        }
    }
}

BOOL IsLoop(Graph graph, VertexType vex){
    visited[vex] = GRAY;
    //printf("%c ", vex);
    VertexType *p;
    VertexType x;
    for (p = FirstAdjVex(graph, vex); p != NULL; p=NextAdjVex(graph, vex, x)){
        x = *p;
        if (visited[x] == WHITE){    //没访问过
            IsLoop(graph, x);

        }
        /*
        else if (visited[x] == BLACK){
            printf("\nloop:%c->%c\n", vex, x);
        }
        */
    }
    printf("%c ", x);
    visited[vex] = BLACK;
}
