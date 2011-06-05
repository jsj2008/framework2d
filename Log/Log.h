#ifndef LOG_H
#define LOG_H

#include <string>

extern class Log
{
    public:
        Log();
        virtual ~Log();
        void debug(const std::string& message);
        void warning(const std::string& message);
        void error(const std::string& message);
        void message(const std::string& message);
    protected:
    private:
}g_Log;

#endif // LOG_H
