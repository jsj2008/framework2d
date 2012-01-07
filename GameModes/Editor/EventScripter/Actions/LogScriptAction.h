#ifndef LOGSCRIPTACTION_H
#define LOGSCRIPTACTION_H

#include <GameModes/Editor/DynamicEditor/EventScripter/ScriptAction.h>
#include <string>

class LogScriptAction : public ScriptAction
{
    public:
        LogScriptAction(const std::string& _message);
        virtual ~LogScriptAction();
        void trigger();
    protected:
    private:
        std::string message;
};

#endif // LOGSCRIPTACTION_H
