#include <stdio.h>
#include <pthread.h>
   
static volatile int counter = 0;
static const int end = 10000000;
   
typedef struct { char *id; int val; } myarg;
  
pthread_mutex_t mutx; // 뮤텍스 선언

void *mythread(void *arg)
{
    myarg *ma = (myarg *) arg;
    printf("%s[%u]: begin\n", ma->id, (unsigned) pthread_self());
    pthread_mutex_lock(&mutx); // 다른 스레드 접근 제한
    for(int i = 0; i < end; i++) {
       --counter;
       ma->val++;
    }   
    pthread_mutex_unlock(&mutx); // 다른 스레드 접근 허용
    printf("%s[%u]: done\n", ma->id, (unsigned) pthread_self());
    return (void *) ma; 
}

int main()
{
    int state;

    state = pthread_mutex_init(&mutx, NULL); // mutex초기화 함수 호출

    printf("main[%u]: begin (counter = %d)\n", (unsigned) pthread_self(), counter);
    pthread_t t1, t2; 
    myarg ma1 = {"A", end };
    myarg ma2 = {"B", end };

    pthread_create(&t1, NULL, mythread, &ma1);
    pthread_create(&t2, NULL, mythread, &ma2);

    pthread_mutex_lock(&mutx); // 다른 스레드 접근 제한
    for(int i = 0; i < end; i++)
        counter++;
    pthread_mutex_unlock(&mutx);
    
    pthread_join(t1, (void **) &ma1); // 다른 스레드 접근 허용
    pthread_join(t2, (void **) &ma2); 

    printf("main[%u]: done (counter = %d) (ma1.val = %d)\n",
 (unsigned) pthread_self(), counter, ma1.val);
    pthread_mutex_destroy(&mutx); // 뮤텍스 삭제
    return 0;
}

