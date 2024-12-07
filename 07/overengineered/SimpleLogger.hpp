#pragma once
#include <iostream>
#include <pthread.h>
#include <vector>

#define __THREADED 1
#define __NOT_THREADED 0

typedef struct
{
    int level;
    std::string Name;
}Trace_level;

class Logger
{
    enum threading
    {
        THREADED = __THREADED,
        NOT_THREADED = __NOT_THREADED
    };

public:
    Logger(int is_threaded, std::string start_trace_level, std::string log_path);
    ~Logger();
    
    int level_depth = 1;
    
    std::vector<std::string> messages;
    std::vector<Trace_level> levels;

    void add_trace_level(std::string name);
    void log(std::string message, std::string trace_level_name);
private:
    pthread_mutex_t m_mutex_lock;
    enum threading m_is_t;
    std::string m_log_path;
};
