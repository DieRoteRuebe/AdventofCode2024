#include "Threadpool.h"



Threadpool::Threadpool(int QUEUE_SIZE, int THREAD_COUNT, Logger *logger)
{
    Threadpool::L = logger;
    Threadpool::L->add_trace_level("THREADPOOL");
    Threadpool::thread_count = THREAD_COUNT;
    Threadpool::threads = new pthread_t[THREAD_COUNT];
    Threadpool::queue_size = QUEUE_SIZE;
    pthread_mutex_init(&(Threadpool::lock), nullptr);
    pthread_cond_init(&(Threadpool::notify), nullptr);
    Threadpool::shutdown = false;
    
    for(int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_create(&(Threadpool::threads[i]), NULL, Threadpool::worker_wrapper,this);
    }

};

Threadpool::~Threadpool()
{
    delete[] Threadpool::threads;
    Threadpool::threadpool_destroy();
};

void* Threadpool::worker_wrapper(void* arg)
{
    Threadpool *pool = static_cast<Threadpool *>(arg);
    return pool->threads_work(arg);
    return nullptr;
};


void* Threadpool::threads_work(void* argv)
{   
    std::string logmsg;
    //Get Thread ID:
    pthread_mutex_lock(&(Threadpool::lock));
    std::string trace_level;
    int thread_nr = Threadpool::thread_counter++;
    trace_level ="THREAD-"+std::to_string(thread_nr);
    if(L != nullptr)
    {
          L->add_trace_level(trace_level);  
    }
    pthread_mutex_unlock(&(Threadpool::lock));
    pthread_t thread_id = pthread_self();
    while(!Threadpool::shutdown)
    {
              
        //Lock the Tasks Queue
        pthread_mutex_lock(&(Threadpool::lock));


        //Wait while Queue is empty and Shutdown-Flag is not set
        while(Threadpool::tasks.empty() && !Threadpool::shutdown)
        {
            if(Threadpool::L != nullptr)
            {
                logmsg = "System-ID: "+std::to_string(thread_id)+": Is sitting iddle...";
                L->log(logmsg, (trace_level));
            }
            //printf("Thread-ID: %d System-ID: %ld: Is sitting iddle...\n",thread_nr, thread_id);
            pthread_cond_wait(&(Threadpool::notify), &(Threadpool::lock));
            if(Threadpool::L != nullptr)
            {
                L->log("System-ID: "+std::to_string(thread_id)+": was notified", (trace_level));
            }
            
        }
        //Cancel all the Threads if Shutdown-Flag is set
        if(Threadpool::shutdown)
        {
            if(Threadpool::L != nullptr)
            {
                L->log("System-ID: "+std::to_string(thread_id)+": Shutdown Signal was issued, shutting down...", (trace_level));
            }
            continue;
        }

        task_t task;
        //Get Task out of Tasksqueue
        if(!Threadpool::tasks.empty())
        {
            task = Threadpool::tasks.back();
            Threadpool::tasks.pop_back();


            pthread_mutex_unlock(&(Threadpool::lock));
            if(Threadpool::L != nullptr)
            {
                L->log("System-ID: "+std::to_string(thread_id)+": Working on:", (trace_level));
            }
            thread_connection con;
            con.arg = task.arg;
            con.thread_id = &thread_nr;
            con.l = Threadpool::L;
            void* arg = static_cast<void*>(&con);
            (*(task.function))(arg); 
        }
        else{
            pthread_mutex_unlock(&(Threadpool::lock));
        }
        //Unlock Task Queue
    }
    if(Threadpool::L != nullptr)
    {
        L->log("System-ID: "+std::to_string(thread_id)+": Leaving Workloop", (trace_level));
    }
    pthread_mutex_unlock(&(Threadpool::lock));
    pthread_exit(NULL);
    return NULL;
};

int Threadpool::threadpool_add_task(void (*function)(void *), void* arg)
{
    pthread_mutex_lock(&(Threadpool::lock));

    if(Threadpool::tasks.size()== Threadpool::queue_size)
    {
        pthread_mutex_unlock(&(Threadpool::lock));
        return -1;
    }

    task_t t;
    t.function = function;
    t.arg = arg;
    Threadpool::tasks.push_back(t);

    pthread_cond_signal(&(Threadpool::notify));
    pthread_mutex_unlock(&(Threadpool::lock));

    return 0;
};

void Threadpool::threadpool_destroy()
{
    if(Threadpool::L != nullptr)
    {
        Threadpool::L->log("Destroying Mutex and Threads", "THREADPOOL");
    }
    


    pthread_mutex_destroy(&(Threadpool::lock));
    pthread_cond_destroy(&(Threadpool::notify));

}

void Threadpool::join_threads()
{
    pthread_mutex_lock(&(Threadpool::lock));
    int size = Threadpool::tasks.size();
    pthread_mutex_unlock(&(Threadpool::lock));
    while(size > 0)
    {
        pthread_mutex_lock(&(Threadpool::lock));
        size = Threadpool::tasks.size();
        pthread_mutex_unlock(&(Threadpool::lock));

    }
}

void Threadpool::threadpool_stop_threads()
{
    
    pthread_mutex_lock(&(Threadpool::lock));
    Threadpool::shutdown = true;
    if(Threadpool::L != nullptr)
    {
        Threadpool::L->log("Dispatching Stopp Singal...", "THREADPOOL");
    }
    pthread_cond_broadcast(&(Threadpool::notify));
    pthread_mutex_unlock(&(Threadpool::lock));

    for(int i = 0; i < Threadpool::thread_count; i++)
    {
        pthread_join((Threadpool::threads[i]), NULL);
    }
}
