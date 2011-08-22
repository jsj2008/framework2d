#include "UninitialisedLogger.h"

UninitialisedLogger::UninitialisedLogger()
{
    //ctor
}

UninitialisedLogger::~UninitialisedLogger()
{
    //dtor
}

void UninitialisedLogger::outputText(std::string _msg, unsigned int _timeStamp,  unsigned int _colour)
{
    storedMessages.push_back({_msg,_timeStamp,_colour});
}

Logger* UninitialisedLogger::newLogger(Logger* _newLogger)
{
    for (unsigned int i = 0; i < storedMessages.size(); i++)
    {
        _newLogger->outputText(storedMessages[i].message, storedMessages[i].timeStamp, storedMessages[i].colour);
    }
    delete this;
    return _newLogger;
}
