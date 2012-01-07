#include "LogScriptAction.h"
#include <Log/Log.h>

LogScriptAction::LogScriptAction(const std::string& _message)
{
    //ctor
    message = _message;
    g_Log.message(message + " created");
}

LogScriptAction::~LogScriptAction()
{
    //dtor
}

void LogScriptAction::trigger()
{
    g_Log.message(message);
}
