#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int head;
    int tail;
} Queue;

void create(Queue* my_queue) {
    my_queue->head = -1;
    my_queue->tail = -1;
}

void enqueue(Queue* my_queue, char data)
{
    if (my_queue->tail == MAX_SIZE - 1)
    {
        printf("Queue is full\n");
        return;
    }
    my_queue->data[++my_queue->tail] = data;
}

void print(Queue* my_queue)
{
    printf("Queue: ");
    for (int i = my_queue->head + 1; i <= my_queue->tail; i++)
    {
        printf("%c ", my_queue->data[i]);
    }
    printf("\n");
}

void peek(Queue* my_queue)
{
    if (my_queue->head == my_queue->tail)
    {
        printf("Queue is empty\n");
        return;
    }
    printf("%c\n", my_queue->data[my_queue->head + 1]);
}

void dequeue(Queue* my_queue)
{
    if (my_queue->head == my_queue->tail)
    {
        printf("Error (nothing to dequeue)\n");
        return;
    }
    my_queue->head++;
}

bool is_full(Queue* my_queue)
{
    return my_queue->tail == MAX_SIZE - 1;
}

void data_count(Queue* my_queue)
{
    printf("%d\n", my_queue->tail - my_queue->head);
}

void head(Queue* my_queue)
{
    if (my_queue->head == my_queue->tail)
    {
        printf("Queue is empty\n");
        return;
    }
    printf("%d\n", my_queue->head+2);
}

void tail(Queue* my_queue)
{
    if (my_queue->head == my_queue->tail)
    {
        printf("Queue is empty\n");
        return;
    }
    printf("%d\n", my_queue->tail+1);
}


bool is_empty(Queue* my_queue)
{
    return my_queue->head == my_queue->tail;
}

bool is_member(Queue* my_queue, char data)
{
    for (int i = my_queue->head + 1; i <= my_queue->tail; i++)
    {
        if (my_queue->data[i] == data)
        {
            return true;
        }
    }
    return false;
}

void replace(Queue* my_queue, char new_data)
{
    if (is_empty(my_queue)) {
        printf("Queue is empty\n");
        return;
    }

    my_queue->data[my_queue->tail] = new_data;
}

void clear(Queue* my_queue)
{
    my_queue->head = -1;
    my_queue->tail = -1;
}

// 나만의 기능 1: 큐의 요소를 한 칸 회전시키는 함수
void rotate(Queue* my_queue) {
    if (is_empty(my_queue)) {
        printf("Queue is empty\n");
        return;
    }
    
    char temp = my_queue->data[my_queue->head + 1]; // 맨 앞 요소 저장
    dequeue(my_queue); // 맨 앞 요소 제거
    enqueue(my_queue, temp); // 맨 앞 요소를 맨 뒤로 이동
}

// 나만의 기능 2: 큐에서 특정 데이터가 몇 개 있는지 세어 반환하는 함수
int count(Queue* my_queue, char data) {
    int count = 0;
    for (int i = my_queue->head + 1; i <= my_queue->tail; i++) {
        if (my_queue->data[i] == data) {
            count++;
        }
    }
    return count;
}

// 나만의 기능 3: 큐의 맨 뒤 요소를 반환하는 함수
void peekBack(Queue* my_queue)
{
    if (my_queue->head == my_queue->tail)
    {
        printf("Queue is empty\n");
        return;
    }
    printf("%c\n", my_queue->data[my_queue->tail]);
}