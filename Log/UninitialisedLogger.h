#ifndef UNINITIALISEDLOGGER_H
#define UNINITIALISEDLOGGER_H

#include <Log/Logger.h>
#include <vector>

class UninitialisedLogger : public Logger
{
    public:
        UninitialisedLogger();
        virtual ~UninitialisedLogger();
        void outputText(std::string _msg, unsigned int _timeStamp,  unsigned int _colour);
        Logger* newLogger(Logger* _newLogger);
    protected:
    private:
        struct StoredMessage
        {
            std::string message;
            unsigned int timeStamp;
            unsigned int colour;
        };
        std::vector<StoredMessage> storedMessages;
};

#endif // UNINITIALISEDLOGGER_H
