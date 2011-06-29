#ifndef LOG_H
#define LOG_H

#include <string>

extern class Log
{
    public:
        Log();
        virtual ~Log();
        void debug(const std::string& _message);
        void warning(const std::string& _message);
        void error(const std::string& _message);
        void message(const std::string& _message);
    protected:
    private:
}g_Log;

#endif // LOG_H
