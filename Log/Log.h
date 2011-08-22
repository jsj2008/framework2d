#ifndef LOG_H
#define LOG_H

#include <string>
class Logger;

extern class Log
{
    public:
        Log();
        virtual ~Log();
        void init();
        void debug(const std::string& _message);
        void warning(const std::string& _message);
        void error(const std::string& _message);
        void message(const std::string& _message);
        static std::string getTimeString(unsigned int _timeStamp);
    protected:
    private:
        Logger* logger;
}g_Log;

#endif // LOG_H
