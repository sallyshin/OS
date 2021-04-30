#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int cq[MAX];
int front = 0;
int rear = 0;

void enque(int val)
{
    if ( (rear + 1) % MAX == front ) {
        printf("queue is full!\n");
        exit(EXIT_FAILURE);
    }
    cq[++rear] = val;
}

int deque()
{
    int ret;

    if (front == rear) {
        printf("queue is empty!\n");
        exit(EXIT_FAILURE);
    }
    front = (front + 1) % MAX;
    return cq[front];
}

int main()
{

    enque(1);
    enque(2);
    enque(1);
    enque(2);
    enque(1);
    enque(2);
    enque(1);
    enque(2);
    enque(1);
    enque(2);
    enque(1);
    enque(2);
    enque(1);
    enque(2);
    printf("%d\n", deque());
    printf("%d\n", deque());
}