//원형 큐 - 버퍼 크기 고정, 정수 보관
#include <stdio.h>

#define QUEUE_SIZE  10
#define NEXT(index)   ((index+1)%QUEUE_SIZE)  //원형 큐에서 인덱스를 변경하는 매크로 함수

typedef struct Queue //Queue 구조체 정의
{
    int buf[QUEUE_SIZE];//저장소
    int front; //꺼낼 인덱스(가장 오래전에 보관한 데이터가 있는 인덱스)
    int rear;//보관할 인덱스
}Queue;

void InitQueue(Queue *queue);//큐 초기화
int IsFull(Queue *queue); //큐가 꽉 찼는지 확인
int IsEmpty(Queue *queue); //큐가 비었는지 확인
void Enqueue(Queue *queue, int data); //큐에 보관
int Dequeue(Queue *queue); //큐에서 꺼냄

int main(void)
{
    int i;
    Queue queue;

    InitQueue(&queue);//큐 초기화
    for (i = 1; i <= 5; i++)//1~5까지 큐에 보관
    {
        Enqueue(&queue, i);
    }
    while (!IsEmpty(&queue))//큐가 비어있지 않다면 반복
    {
        printf("%d ", Dequeue(&queue));//큐에서 꺼내온 값 출력
    }
    printf("\n");
    return 0;
}

void InitQueue(Queue *queue)
{
    queue->front = queue->rear = 0; //front와 rear를 0으로 설정
}
int IsFull(Queue *queue)
{
    //원형 큐에서 꽉 찼는지 비었는지 체크할 수 있게 rear 다음 공간은 빈 상태를 유지합니다.
    return NEXT(queue->rear) == queue->front;//다음 rear가 front와 같으면 꽉 찬 상태
}
int IsEmpty(Queue *queue)
{
    return queue->front == queue->rear;    //front와 rear가 같으면 빈 상태
}
void Enqueue(Queue *queue, int data)
{
    if (IsFull(queue))//큐가 꽉 찼을 때
    {
        printf("큐가 꽉 찼음\n");
        return;
    }
    queue->buf[queue->rear] = data;//rear 인덱스에 데이터 보관
    queue->rear = NEXT(queue->rear); //rear를 다음 위치로 설정
}
int Dequeue(Queue *queue)
{
    int re = 0;
    if (IsEmpty(queue))//큐가 비었을 때
    {
        printf("큐가 비었음\n");
        return re;
    }
    re = queue->buf[queue->front];//front 인덱스에 보관한 값을 re에 설정
    queue->front = NEXT(queue->front);//front를 다음 위치로 설정
    return re;
}