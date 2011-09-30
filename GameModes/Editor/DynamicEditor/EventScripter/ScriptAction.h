#ifndef SCRIPTACTION_H
#define SCRIPTACTION_H


class ScriptAction /// FIXME this is in the wrong folder
{
    public:
        ScriptAction();
        virtual ~ScriptAction();
        virtual void trigger()=0;
    protected:
    private:
};

#endif // SCRIPTACTION_H
