#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Filesystem/FilesystemNode.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <cassert>
class GameObjectEventListener;
class CollisionObject;

class GameObjectBase : public FilesystemNode
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

        GameObjectBase(const std::string& _name, unsigned int _eventsSize);
        virtual ~GameObjectBase();

        std::string nodeName(){return objectName;}
        const std::string& getObjectName(){return objectName;}

        virtual EventHandle* getEventHandle(const std::string& _name)=0;
        //virtual ActionHandle* getActionHandle(const std::string& _name)=0;
        static ActionHandle* getActionHandle(const std::string& _name){return actionHandles()[_name];}

        void killAction(CollisionObject* _object); /// Will trigger deathEvent
        static void registerBaseActions();

        GameObjectBase* getNext();
        GameObjectBase* getPrev();
        GameObjectBase* getChildren();
        GameObjectBase* getParent();
        void attachChild(GameObjectBase* _child);
        void detach(GameObjectBase* _child);
    protected:
        void setParent(GameObjectBase* _parent);
        void fireEvent(EventHandle* _eventHandle){_eventHandle->fire(this);}
        static std::unordered_map<std::string,ActionHandle*>& actionHandles()
        {
            static std::unordered_map<std::string,ActionHandle*> handles;
            return handles;
        }
        FilesystemIter* firstChild();
        FilesystemIter* nextChild(FilesystemIter* _prevChild);
        void orphaned();
    private:
        friend class OrphanList;
        GameObjectBase* next,* prev,* children,* parent;

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
        template <typename EventObject>
        static void createActionHandle(const std::string& _name, void (DerivedObject::*_action)(EventObject* _object));
    protected:
        static EventHandle* createEventHandle(const char* _name);
    private:
        class TemplateActionHandle : public ActionHandle
        {
            public:
                TemplateActionHandle(void (DerivedObject::*_action)()){action = _action;}
                void execute(GameObjectBase* _object);
                void execute(GameObjectBase* _object, void* _eventObject, unsigned int _typeHandle){execute(_object);}
            private:
                void (DerivedObject::*action)();
        };
        template <typename EventObject>
        class TemplateActionWithObjectHandle : public ActionHandle
        {
            public:
                TemplateActionWithObjectHandle(void (DerivedObject::*_action)(EventObject* _eventObject)){action = _action;}
                void execute(GameObjectBase* _object);
                void execute(GameObjectBase* _object, void* _eventObject, unsigned int _typeHandle);
            private:
                void (DerivedObject::*action)(EventObject* _eventObject);
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
typename GameObject<DerivedObject>::EventHandle* GameObject<DerivedObject>::deathEvent = createEventHandle("onDeath");

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

template <typename T>
const std::string& generateName()
{
    static unsigned int count = 0;
    static std::string ret = T::name();
    ret += count;
    return ret;
}
template <typename DerivedObject>
GameObject<DerivedObject>::GameObject()
:GameObjectBase(generateName<DerivedObject>(), eventHandles().size())
{
    autoInstantiationPlease.check();
    orphaned();
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
template <typename EventObject>
void GameObject<DerivedObject>::createActionHandle(const std::string& _name, void (DerivedObject::*_action)(EventObject* _object))
{
    assert(actionHandles().find(_name) == actionHandles().end());
    ActionHandle* handle = new TemplateActionWithObjectHandle<EventObject>(_action);
    actionHandles()[_name] = handle;
}

template <typename EventObject>
void GameObjectBase::ActionHandle::execute(GameObjectBase* _object, EventObject* _eventObject)
{
    unsigned int handle = getObjectHandle<EventObject>();
    execute(_object, static_cast<void*>(_eventObject), handle);
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
template <typename DerivedObject>
template <typename EventObject>
void GameObject<DerivedObject>::TemplateActionWithObjectHandle<EventObject>::execute(GameObjectBase* _object)
{
    assert(false);
}
template <typename DerivedObject>
template <typename EventObject>
void GameObject<DerivedObject>::TemplateActionWithObjectHandle<EventObject>::execute(GameObjectBase* _object, void* _eventObject, unsigned int _typeHandle)
{
    {
        DerivedObject* dynCast = dynamic_cast<DerivedObject*>(_object);
        assert(dynCast);
        assert(_typeHandle == getObjectHandle<EventObject>());
    }
    DerivedObject* object = static_cast<DerivedObject*>(_object);
    EventObject* eventObject = static_cast<EventObject*>(_eventObject);
    (object->*action)(eventObject);
}

#endif // GAMEOBJECT_H
