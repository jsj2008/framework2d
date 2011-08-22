#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger
{
    public:
        Logger();
        virtual ~Logger();
        virtual void outputText(std::string _msg, unsigned int timeStamp, unsigned int _colour = -1)=0; /// FIXME Make this an engine string class, and alias CEGUI string to it
        virtual Logger* newLogger(Logger* _newLogger)=0;
    protected:
    private:
};

#endif // LOGGER_H
