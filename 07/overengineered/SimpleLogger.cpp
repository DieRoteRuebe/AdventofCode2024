#include "SimpleLogger.hpp"
#include <chrono>
#include <ctime>

Logger::Logger(int is_threaded, std::string start_trace_level_name, std::string log_path)
{
    Logger::m_log_path = log_path;
    if(is_threaded == __THREADED)
    {
        Logger::m_is_t = THREADED;
        pthread_mutex_init(&(Logger::m_mutex_lock), nullptr);

    }
    else{
        Logger::m_is_t = NOT_THREADED;
    }
    Logger::add_trace_level(start_trace_level_name);
};

Logger::~Logger()
{

};


void Logger::log(std::string message, std::string trace_level_name)
{
    if(m_is_t = THREADED)
    {
        pthread_mutex_lock(&(Logger::m_mutex_lock));
    }
    std::string msg;
    msg += "LOGGER:";
    int trace_level;
    auto current_time = std::chrono::system_clock::now();
    std::time_t now = std::chrono::system_clock::to_time_t(current_time);
    msg += std::ctime(&now);
    msg.replace(msg.find("\n"), msg.size(), "");
    msg +=":";
    for(int i = 0; i < Logger::levels.size(); i++)
    {
        if(Logger::levels[i].Name == trace_level_name)
        {
            trace_level = Logger::levels[i].level;
            msg += "Channel-"+Logger::levels[i].Name;
        }
    }
    
    msg += ":"+message;
    Logger::messages.push_back(msg);
    pthread_mutex_unlock(&(Logger::m_mutex_lock));
    std::cout << msg << "\n";

};

void Logger::add_trace_level(std::string name)
{
    pthread_mutex_lock(&(Logger::m_mutex_lock));
    Trace_level t;
    t.level = Logger::level_depth++;
    t.Name = name;
    Logger::levels.push_back(t);
    pthread_mutex_unlock(&(Logger::m_mutex_lock));
}
