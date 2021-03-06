//원형 큐 - 동적 생성, 정수 보관

#include <stdio.h>
#include <stdlib.h>

#define NEXT(index,QSIZE)   ((index+1)%QSIZE)  //원형 큐에서 인덱스를 변경하는 매크로 함수

typedef struct Queue //Queue 구조체 정의
{
    int *buf;//저장소
    int qsize;
    int front; //꺼낼 인덱스(가장 오래전에 보관한 데이터가 있는 인덱스)
    int rear;//보관할 인덱스
    int count;//보관 개수

}Queue;

Queue *NewQueue(int qsize);//생성자
void DeleteQueue(Queue *queue);//소멸자
int IsFull(Queue *queue); //큐가 꽉 찼는지 확인
int IsEmpty(Queue *queue); //큐가 비었는지 확인
void Enqueue(Queue *queue, int data); //큐에 보관
int Dequeue(Queue *queue); //큐에서 꺼냄

int main(void)
{
    int i;
    Queue *queue = NewQueue(10);//동적 생성

    for (i = 1; i <= 5; i++)//1~5까지 큐에 보관
    {
        Enqueue(queue, i);
    }
    while (!IsEmpty(queue))//큐가 비어있지 않다면 반복
    {
        printf("%d ", Dequeue(queue));//큐에서 꺼내온 값 출력
    }
    printf("\n");

    DeleteQueue(queue);//소멸
    return 0;
}

void InitQueue(Queue *queue, int qsize);//큐 초기화
Queue *NewQueue(int qsize)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));//동적 메모리 할당
    InitQueue(queue, qsize);//큐 초기화
    return queue;
}
void InitQueue(Queue *queue, int qsize)
{
    queue->buf = (int *)malloc(sizeof(int)*qsize);//버퍼를 동적 메모리 할당
    queue->qsize = qsize;
    queue->front = queue->rear = 0; //front와 rear를 0으로 설정
    queue->count = 0;//보관 개수를 0으로 설정
}

void DisposeQueue(Queue *queue);//큐 해제화
void DeleteQueue(Queue *queue)
{
    DisposeQueue(queue);//버퍼 메모리 해제
    free(queue);//큐 메모리 해제
}
void DisposeQueue(Queue *queue)
{
    free(queue->buf);//버퍼 메모리 해제
}

int IsFull(Queue *queue)
{
    return queue->count == queue->qsize;//보관 개수가 qsize와 같으면 꽉 찬 상태
}
int IsEmpty(Queue *queue)
{
    return queue->count == 0;    //보관 개수가 0이면 빈 상태
}
void Enqueue(Queue *queue, int data)
{
    if (IsFull(queue))//큐가 꽉 찼을 때
    {
        printf("큐가 꽉 찼음\n");
        return;
    }
    queue->buf[queue->rear] = data;//rear 인덱스에 데이터 보관
    queue->rear = NEXT(queue->rear, queue->qsize); //rear를 다음 위치로 설정
    queue->count++;//보관 개수를 1 증가
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
    queue->front = NEXT(queue->front, queue->qsize);//front를 다음 위치로 설정
    queue->count--;//보관 개수를 1 감소
    return re;
}