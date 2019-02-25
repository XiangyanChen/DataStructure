#define MAXSIZE 100
#define ElemType char
#define BOOL int
#define TRUE 1
#define FALSE 0

typedef struct{
    ElemType data[MAXSIZE];
    int front, rear;
}Queue;

static void InitQueue(Queue *queue);   //初始化队列
static BOOL IsEmpty(Queue *queue); //判断是否为空
static void EnQueue(Queue *queue, ElemType x); //入队
static void DeQueue(Queue *queue, ElemType *x);    //出队

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
