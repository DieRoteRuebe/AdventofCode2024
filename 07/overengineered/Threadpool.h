#pragma once

#include <pthread.h>
#include <vector>
#include <atomic>
#include <stdio.h>
#include <mutex>
#include "SimpleLogger.hpp"


//Task Stuct:
typedef struct
{
    void (*function)(void *);
    void *arg;
}task_t;

typedef struct  
{
    void *arg;      //arg für die Funktion selbst
    Logger *l;      //Logger
    int *thread_id;  //thread id
}thread_connection;


class Threadpool
{
public:
    Threadpool(int QUEUE_SIZE, int THREAD_COUNT, Logger *logger);
    ~Threadpool();

    Logger *L;
    std::mutex id_mutex;
    int thread_counter = 1;
    pthread_mutex_t lock;               // Mutex für die Synchronisierung
    pthread_cond_t notify;              // Condition Variable zur Benachrichtigung von Threads
    pthread_t *threads;               
    std::vector<task_t> tasks;          // Task Queue
    std::atomic_bool shutdown;          // Flag für das Beenden des Pools
    int queue_size;
    int thread_count;
    std::atomic_bool join;
    void threadpool_stop_threads();     // Sinc Threads and stop
    void join_threads();    // wait for Queue to be empty and threads done working

    int threadpool_add_task(void (*function)(void *), void* arg);
private:
    static void* worker_wrapper(void *arg);
    void* threads_work(void* argv);     // Work Function
    void threadpool_destroy();          // Destory Mutexes and Threads
    
};
