#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define STATE_INIT (0)

typedef struct {
    pthread_t th; 
    int state;
} my_thread_t;

my_thread_t *thd;
pthread_mutex_t lock;

void *routine(void *arg) {
    pthread_mutex_lock(&lock);
    printf("routine: begin\n");
    printf("routine: state is %d\n", thd->state);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void myWaitThread(my_thread_t *p) {
    pthread_join(p->th, NULL); // 2
}

my_thread_t *myCreateThread(void *(*start_routine)(void *)) {
    my_thread_t *p = malloc(sizeof(my_thread_t));
    if (p == NULL) 
        return NULL;
    p->state = STATE_INIT; // 3
    pthread_create(&p->th, NULL, start_routine, NULL); // 4
    // turn the sleep off to avoid the fault, sometimes...
    sleep(1);
    return p;
}

int main(int argc, char *argv[]) {
    pthread_mutex_init(&lock, NULL);

    printf("ordering: begin\n");

    pthread_mutex_lock(&lock);
    thd = myCreateThread(routine);
    pthread_mutex_unlock(&lock);
    myWaitThread(thd);
    printf("ordering: end\n");
    return 0;
}
