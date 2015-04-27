// producer_consumer.cpp
//////////////////////////////////////////////////////////////////////
// ��һ����������������Ʒ����Щ��Ʒ���ṩ�����ɸ�������ȥ���ѣ�Ϊ��ʹ�����ߺ��������ܲ���ִ�У�
// ������֮������һ���ж���������Ļ���أ������߽��������Ĳ�Ʒ����һ���������У������߿��Դӻ�
// ������ȡ�߲�Ʒ�������ѣ����������ߺ������߶����첽��ʽ���еģ������Ǳ��뱣��ͬ��������������
// ���ߵ�һ���յĻ�������ȡ��Ʒ��Ҳ��������������һ���Ѿ�װ����Ʒ����δ��ȡ�ߵĻ�������Ͷ�Ų�Ʒ��
//////////////////////////////////////////////////////////////////////

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define  BUFFER_LENGTH  100
int buffer[BUFFER_LENGTH] = { 0 };
int front = 0, rear = -1; // ��������ǰ�˺�β��
int size = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t full_cond = PTHREAD_COND_INITIALIZER;

bool producer_wait = false;
bool consumer_wait = false;

void *producer(void *arg);
void *consumer(void *arg);

int main(int argc, char **argv)
{
    pthread_t producer_id;
    pthread_t consumer_id;

    pthread_create(&producer_id, NULL, producer, NULL);
    
    pthread_create(&consumer_id, NULL, consumer, NULL);

    sleep(1);

    return 0;
}

void *producer(void *arg)
{
    pthread_detach(pthread_self());
    
    while (true)
    {
        pthread_mutex_lock(&mutex);
        if (size == BUFFER_LENGTH) // ����������������ȴ�; ��������²�Ʒ
        {
            printf("buffer is full. producer is waiting...\n");
            producer_wait = true;
            pthread_cond_wait(&full_cond, &mutex);
            producer_wait = false;
        }
        // ��β�����һ����Ʒ
        rear = (rear + 1) % BUFFER_LENGTH;
        buffer[rear] = rand() % BUFFER_LENGTH;
        printf("producer produces the item %d: %d\n", rear, buffer[rear]);
        ++size;
        if (size == 1) // �����ǰsize=1, ˵����ǰsize=0, �������ڵȴ�����������߷��ź�
        {
            while (true)
            {
                if (consumer_wait)
                {
                    pthread_cond_signal(&empty_cond);
                    break;
                }
            }
        }
        pthread_mutex_unlock(&mutex);
    }
}

void *consumer(void *arg)
{
    pthread_detach(pthread_self());
    
    while (true)
    {
        pthread_mutex_lock(&mutex);
        if (size == 0) // ����������ѿգ��ȴ�; �������Ѳ�Ʒ
        {
            printf("buffer is empty. consumer is waiting...\n");
            consumer_wait = true;
            pthread_cond_wait(&empty_cond, &mutex);
            consumer_wait = false;
        }
        // ��ǰ������һ����Ʒ
        printf("consumer consumes an item%d: %d\n", front, buffer[front]);
        front = (front + 1) % BUFFER_LENGTH;
        --size;
        if (size == BUFFER_LENGTH-1) // �����ǰsize=BUFFER_LENGTH-1��˵����ǰ�������ڵȴ�����������߷��ź�
        {
            while (true)
            {
                if (producer_wait)
                {
                    pthread_cond_signal(&full_cond);
                    break;
                }
            }
        }
        pthread_mutex_unlock(&mutex);
    }
}


