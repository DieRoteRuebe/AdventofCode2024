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
    void *arg;       //arg for function
    Logger *l;       //Logger
    int *thread_id;  //thread id
}thread_connection;


class Threadpool
{
public:
    Threadpool(int QUEUE_SIZE, int THREAD_COUNT, Logger *logger);
    ~Threadpool();

    void threadpool_stop_threads();     // Sinc Threads and stop even if work is still in qeue
    void join_threads();                // wait for Queue to be empty and threads doing work -> then issue shutdown and stop_threads

    int threadpool_add_task(void (*function)(void *), void* arg);
private:
    static void* worker_wrapper(void *arg);
    void* threads_work(void* argv);     // Work Function
    void threadpool_destroy();          // Destory Mutexes and Threads

    bool threads_stopped;
    Logger *L;
    std::mutex id_mutex;
    int thread_counter = 1;
    pthread_mutex_t lock;               // Mutex for synchronizing
    pthread_cond_t notify;              // Condition Variable to notify threads in cond_wait
    pthread_t *threads;               
    std::vector<task_t> tasks;          // Task Queue
    std::atomic_bool shutdown;          // Flag to shutdown threads
    int queue_size;
    int thread_count;
    
};
