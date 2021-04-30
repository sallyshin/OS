#include <stdio.h>
#include <pthread.h>
#include <unistd.h>     // usleep (micro sleep)
#define MAX 10 
#define PROD_SIZE 3
#define CONS_SIZE 7
#define PROD_ITEM 5
#define CONS_ITEM 2
 
/* homework */
/*----------*/
/* You need to make some variables (mutex, condition variables). */
/* Reference below variables, functions. */
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t fill = PTHREAD_COND_INITIALIZER;
/*----------*/
/* homework */
 
pthread_mutex_t m_id = PTHREAD_MUTEX_INITIALIZER;
int buffer[MAX]; // ! buffer is circular queue !
int count = 0;
int get_ptr = 0;
int put_ptr = 0;
int prod_id = 1;
int cons_id = 1;
 
/* homework */
// return buffer's value using get_ptr if successful,
// otherwise, -1
// consumer
int get()
{   
    if(get_ptr == put_ptr){ // 버퍼가 비어있으면
        printf("queue is empty!\n");
        return -1; // exit(EXIT_FAILURE)방법도 있다고한다
    } 
    get_ptr = (get_ptr + 1) % MAX;
    count--;
    return buffer[get_ptr];  // return buffer's value using put_ptr if successful
} 

/* homework */
// return buffer's value using put_ptr if successful,
// otherwise, -1
//producer
int put(int val)
{
    if((put_ptr + 1) % MAX == get_ptr){
        printf("buffer is full!\n");
        return -1; // otherwise, -1
    }
    buffer[put_ptr] = val;
    put_ptr = (put_ptr + 1) % MAX;
    count++;
    return buffer[put_ptr]; // return buffer's value using put_ptr if successful
}

void *producer(void *arg)
{
    pthread_mutex_lock(&m_id);
    int id = prod_id++;
    pthread_mutex_unlock(&m_id);
    for (int i = 0; i < PROD_ITEM; ++i) {
        usleep(10);
       /*----------------homework------------------- */
        pthread_mutex_lock(&m_id); // 다른 스레드 접근 못하게 뮤텍스 락
        while(count == MAX - 1) // 버퍼가 꽉 차면
            pthread_cond_wait(&empty, &m_id); // 소비자로부터 empty큐에 뭐가 있으면, 버퍼에 값을 넣기 위해 lock을 푼다
        int ret = put(i);
        pthread_cond_signal(&fill); // 버퍼에 값을 넣었으므로 fill큐에 신호전달, 소비자가 값 소비하게 해준다.
        pthread_mutex_unlock(&m_id);
        /* -------------------homework------------------ */
    
        if (ret == -1) {
            printf("can't put, becuase buffer is full.\n");
        } else {
            printf("producer %d PUT %d\n", id, ret);
        }
    }
    return NULL;
}
void *consumer(void *arg)
{
    pthread_mutex_lock(&m_id);
    int id = cons_id++;
    pthread_mutex_unlock(&m_id);
    for (int i = 0; i < CONS_ITEM; ++i) {
        usleep(10);

        /* -------------------homework------------------ */
        pthread_mutex_lock(&m_id);
        while (count == 0) { // buffer is emtpy
            pthread_cond_wait(&fill, &m_id); // 프로듀서가 값을 넣기 전까지 기다린다.
        }
        int ret = get();// buffer에 값 생겨서 소비자는 값 얻음
        pthread_cond_signal(&empty); // empty 신호 발생, producer은 값을 buffer로
        pthread_mutex_unlock(&m_id);
        /* -------------------homework------------------ */


        if (ret == -1) {
            printf("can't get, becuase buffer is empty.\n");
        } else {
            printf("consumer %d GET %d\n", id, ret);
        }
    }
    return NULL;
}
 
int main()
{
    pthread_t prod[PROD_SIZE];
    pthread_t cons[CONS_SIZE];

    for (int i = 0; i < PROD_SIZE; ++i)
        pthread_create(&prod[i], NULL, producer, NULL);
    for (int i = 0; i < CONS_SIZE; ++i)
        pthread_create(&cons[i], NULL, consumer, NULL);

    for (int i = 0; i < PROD_SIZE; ++i)
        pthread_join(prod[i], NULL);
    for (int i = 0; i < CONS_SIZE; ++i)
        pthread_join(cons[i], NULL);
 
    return 0;
}