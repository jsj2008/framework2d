#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include <unordered_map>
#include <cassert>
class GameObjectEventListener;

class GameObjectBase
{
    public:
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
        };

        GameObjectBase(unsigned int _eventsSize);
        virtual ~GameObjectBase();

        const std::string& getObjectName(){return objectName;}

        virtual EventHandle* getEventHandle(const std::string& _name)=0;
        //virtual ActionHandle* getActionHandle(const std::string& _name)=0;
        static ActionHandle* getActionHandle(const std::string& _name){return actionHandles()[_name];}

        void killAction(); /// Will trigger deathEvent
        static void registerBaseActions();
    protected:
        void fireEvent(EventHandle* _eventHandle){_eventHandle->fire(this);}
        void attachChild(GameObjectBase* _child);
        static std::unordered_map<std::string,ActionHandle*>& actionHandles()
        {
            static std::unordered_map<std::string,ActionHandle*> handles;
            return handles;
        }
    private:
        GameObjectBase* next,* prev,* children;

        friend class EventHandle;
        std::vector<std::vector<GameObjectEventListener*>> eventListenerLists;
        std::string objectName;
};
class GameObjectEventListener
{
    public:
        virtual void fire()=0;
        virtual void eventObjectDeleted()=0;
};

template <typename DerivedObject>
class AutoInstantiate
{
    public:
        AutoInstantiate();
        void check()const{}
};
template <typename DerivedObject>
class GameObject : public GameObjectBase
{
    public:
        GameObject();
        virtual ~GameObject();

        EventHandle* getEventHandle(const std::string& _name){return eventHandles()[_name];}

        static std::vector<EventHandle*> getAllEventHandles();
        static std::vector<ActionHandle*> getAllActionHandles();
        static void createActionHandle(const std::string& _name, void (DerivedObject::*_action)());
    protected:
        static EventHandle* createEventHandle(const char* _name);
    private:
        class TemplateActionHandle : public ActionHandle
        {
            public:
                TemplateActionHandle(void (DerivedObject::*_action)()){action = _action;}
                void execute(GameObjectBase* _object);
            private:
                void (DerivedObject::*action)();
        };

        friend class AutoInstantiate<DerivedObject>;
        static void baseRegisterActions();

        static EventHandle* deathEvent;

        static std::unordered_map<std::string,EventHandle*>& eventHandles()
        {
            static std::unordered_map<std::string,EventHandle*> handles;
            return handles;
        }

        const static AutoInstantiate<DerivedObject> autoInstantiationPlease;
};


template <typename DerivedObject>
typename GameObject<DerivedObject>::EventHandle* GameObject<DerivedObject>::deathEvent = createEventHandle("Death");

template <typename DerivedObject>
const AutoInstantiate<DerivedObject> GameObject<DerivedObject>::autoInstantiationPlease;

class GameEntity: public GameObject<GameEntity>
{
    public:
        void coonAction(){}
        static void registerActions()
        {
            createActionHandle("Coon", &GameEntity::coonAction);
        }
        static EventHandle* coonEvent;
};














template <typename DerivedObject>
AutoInstantiate<DerivedObject>::AutoInstantiate()
{
    GameObjectBase::registerBaseActions();
    GameObject<DerivedObject>::baseRegisterActions();
}

template <typename DerivedObject>
GameObject<DerivedObject>::GameObject()
:GameObjectBase(eventHandles().size())
{
    autoInstantiationPlease.check();
}
template <typename DerivedObject>
GameObject<DerivedObject>::~GameObject()
{
    fireEvent(deathEvent);
}

template <typename DerivedObject>
void GameObject<DerivedObject>::baseRegisterActions()
{
    /**
        A class derived from GameObject needs to have a static registerActions() function.
        This function should call createActionHandle for every executable action you want that class to have available for scripting.
    */
    DerivedObject::registerActions();
}

template <typename DerivedObject>
typename GameObject<DerivedObject>::EventHandle* GameObject<DerivedObject>::createEventHandle(const char* _name)
{
    assert(eventHandles().find(_name) == eventHandles().end());
    EventHandle* handle = new EventHandle(eventHandles().size());
    eventHandles()[_name] = handle;
    return handle;
}
template <typename DerivedObject>
void GameObject<DerivedObject>::createActionHandle(const std::string& _name, void (DerivedObject::*_action)())
{
    assert(actionHandles().find(_name) == actionHandles().end());
    ActionHandle* handle = new TemplateActionHandle(_action);
    actionHandles()[_name] = handle;
}

template <typename DerivedObject>
void GameObject<DerivedObject>::TemplateActionHandle::execute(GameObjectBase* _object)
{
    {
        DerivedObject* dynCast = dynamic_cast<DerivedObject*>(_object);
        assert(dynCast);
    }
    DerivedObject* cast = static_cast<DerivedObject*>(_object);
    (cast->*action)();
}

#endif // GAMEOBJECT_H
