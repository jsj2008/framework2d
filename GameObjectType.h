#ifndef GAMEOBJECTTYPE_H
#define GAMEOBJECTTYPE_H

#include <string>
#include <unordered_map>
#include <cassert>

class GameObjectBase;
class GameObjectEventListener;

class EventHandle /// Template event object
{
    public:
        EventHandle(unsigned int _eventIndex){eventIndex = _eventIndex;}
        void registerListener(GameObjectBase* _object, GameObjectEventListener* _listener);
    private:
        friend class GameObjectBase;
        void fire(GameObjectBase* _object);
        unsigned int eventIndex;
};
class ActionHandle
{
    public:
        virtual void execute(GameObjectBase* _object)=0;
        template <typename EventObject>
        void execute(GameObjectBase* _object, EventObject* _eventObject);
        virtual void execute(GameObjectBase* _object, void* _eventObject, unsigned int _typeHandle)=0;
    protected:
        template <typename EventObject>
        static unsigned int getObjectHandle()
        {
            static unsigned int handle = newObjectHandle();
            return handle;
        }
    private:
        static unsigned int newObjectHandle()
        {
            static unsigned int handle = 0;
            return handle++;
        }
};
template <typename DerivedObject>
class TemplateActionHandle : public ActionHandle
{
    public:
        TemplateActionHandle(void (DerivedObject::*_action)()){action = _action;}
        void execute(GameObjectBase* _object);
        void execute(GameObjectBase* _object, void* _eventObject, unsigned int _typeHandle){execute(_object);}
    private:
        void (DerivedObject::*action)();
};
template <typename DerivedObject, typename EventObject>
class TemplateActionWithObjectHandle : public ActionHandle
{
    public:
        TemplateActionWithObjectHandle(void (DerivedObject::*_action)(EventObject* _eventObject)){action = _action;}
        void execute(GameObjectBase* _object);
        void execute(GameObjectBase* _object, void* _eventObject, unsigned int _typeHandle);
    private:
        void (DerivedObject::*action)(EventObject* _eventObject);
};

class GameObjectType
{
    public:
        GameObjectType(const std::string& _name);
        virtual ~GameObjectType();
        const std::string& getName(){return name;}
        EventHandle* createEventHandle(const std::string& _name);
        ActionHandle* createActionHandle(const std::string& _name);
        unsigned int eventsSize();
        std::string print(GameObjectBase* _object);
        EventHandle* getEventHandle(const std::string& _name);
        ActionHandle* getActionHandle(const std::string& _name);
        static EventHandle* staticGetEventHandle(const std::string& _name);
        static ActionHandle* staticGetActionHandle(const std::string& _name);

        template <typename DerivedObject>
        void createActionHandle(const std::string& _name, void (DerivedObject::*_action)());
        template <typename DerivedObject, typename EventObject>
        void createActionHandle(const std::string& _name, void (DerivedObject::*_action)(EventObject* _object));
    protected:
    private:
        std::string name;
        std::unordered_map<std::string,EventHandle*> eventHandles;
        std::unordered_map<std::string,ActionHandle*> actionHandles;
        static std::unordered_map<std::string,EventHandle*>& g_EventHandles();
        static std::unordered_map<std::string,ActionHandle*>& g_ActionHandles();
};


template <typename DerivedObject>
void GameObjectType::createActionHandle(const std::string& _name, void (DerivedObject::*_action)())
{
    assert(actionHandles.find(_name) == actionHandles.end());
    ActionHandle* handle = new TemplateActionHandle<DerivedObject>(_action);
    actionHandles[_name] = handle;
    if (g_ActionHandles().find(_name) == g_ActionHandles().end())
    {
        g_ActionHandles()[_name] = handle;
    }
}
template <typename DerivedObject, typename EventObject>
void GameObjectType::createActionHandle(const std::string& _name, void (DerivedObject::*_action)(EventObject* _object))
{
    assert(actionHandles.find(_name) == actionHandles.end());
    ActionHandle* handle = new TemplateActionWithObjectHandle<DerivedObject, EventObject>(_action);
    actionHandles[_name] = handle;
    if (g_ActionHandles().find(_name) == g_ActionHandles().end())
    {
        g_ActionHandles()[_name] = handle;
    }
}

#endif // GAMEOBJECTTYPE_H
