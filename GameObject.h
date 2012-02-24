#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GameObjectType.h>
#include <Types/Tree.h>
#include <string>
#include <vector>
#include <cassert>
class CollisionObject;

class GameObjectBase: public TreeNode<GameObjectBase>
{
    public:

        GameObjectBase(GameObjectType* _type, const std::string& _name);
        GameObjectBase(GameObjectType* _type, const std::string& _name, GameObjectBase* _parent, bool _orphan);
        virtual ~GameObjectBase();

        const std::string& getObjectName(){return objectName;}

        void killAction(); /// Will trigger deathEvent
        void killActionBy(CollisionObject* _object); /// Will trigger deathEvent
        static void registerBaseActions(GameObjectType* _type);

        GameObjectBase* getNode(const std::string& _address);
        GameObjectType* getType();
        GameObjectBase* getIndividualNode(const std::string& _address);
    protected:
        void setParent(TreeNode<GameObjectBase*>* _parent);
        void fireEvent(EventHandle* _eventHandle){_eventHandle->fire(this);}
        static std::unordered_map<std::string,ActionHandle*>& actionHandles()
        {
            static std::unordered_map<std::string,ActionHandle*> handles;
            return handles;
        }
        void orphaned();
        std::string objectName;
    private:
        friend class OrphanList;
	ListNode<GameObjectBase> filesystemNode;
        friend class EventHandle;
        std::vector<std::vector<GameObjectEventListener*>> eventListenerLists;
        GameObjectType* type;
        static EventHandle* deathEvent;
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
        AutoInstantiate(GameObjectType* _type);
        void check()const{}
};
template <typename T>
const std::string& generateName()
{
    static unsigned int count = 0;
    static std::string ret = T::name();
    ret += count;
    return ret;
}
template <typename DerivedObject>
class GameObject : public GameObjectBase
{
    public:
        GameObject(const std::string& _name = generateName<DerivedObject>());
        GameObject(GameObjectBase* _parent, bool _orphan = true); /// , const std::string& _name = generateName<DerivedObject>()
        GameObject(const std::string& _name, GameObjectBase* _parent, bool _orphan = true);
        virtual ~GameObject();

        void print(std::string* _output);
    protected:
        static GameObjectType type;
    private:

        friend class AutoInstantiate<DerivedObject>;
        static void baseRegisterActions(GameObjectType* _type);

        const static AutoInstantiate<DerivedObject> autoInstantiationPlease;
};

template <typename DerivedObject>
const AutoInstantiate<DerivedObject> GameObject<DerivedObject>::autoInstantiationPlease(&type);

#include <AbstractFactory/EvaluateTypeName.h>
template <typename DerivedObject>
GameObjectType GameObject<DerivedObject>::type(EvaluateTypeName<DerivedObject>());













template <typename DerivedObject>
AutoInstantiate<DerivedObject>::AutoInstantiate(GameObjectType* _type)
{
    GameObjectBase::registerBaseActions(_type);
    GameObject<DerivedObject>::baseRegisterActions(_type);
}

template <typename DerivedObject>
GameObject<DerivedObject>::GameObject(const std::string& _name)
:GameObjectBase(&type, _name)
{
    autoInstantiationPlease.check();
}
template <typename DerivedObject>
GameObject<DerivedObject>::GameObject(GameObjectBase* _parent, bool _orphan)
:GameObjectBase(&type, generateName<DerivedObject>(), _parent, _orphan)
{
    autoInstantiationPlease.check();
}
template <typename DerivedObject>
GameObject<DerivedObject>::GameObject(const std::string& _name, GameObjectBase* _parent, bool _orphan)
:GameObjectBase(&type, _name, _parent, _orphan)
{
    autoInstantiationPlease.check();
}
template <typename DerivedObject>
GameObject<DerivedObject>::~GameObject()
{
    fireEvent(deathEvent);
}

template <typename DerivedObject>
void GameObject<DerivedObject>::baseRegisterActions(GameObjectType* _type)
{
    /**
        A class derived from GameObject needs to have a static registerActions(GameObjectType* _type) function.
        This function should call createActionHandle for every executable action you want that class to have available for scripting.
    */
    DerivedObject::registerActions(_type);
}


template <typename EventObject>
void ActionHandle::execute(GameObjectBase* _object, EventObject* _eventObject)
{
    unsigned int handle = getObjectHandle<EventObject>();
    execute(_object, static_cast<void*>(_eventObject), handle);
}

template <typename DerivedObject>
void TemplateActionHandle<DerivedObject>::execute(GameObjectBase* _object)
{
    {
        DerivedObject* dynCast = dynamic_cast<DerivedObject*>(_object);
        assert(dynCast);
    }
    DerivedObject* cast = static_cast<DerivedObject*>(_object);
    (cast->*action)();
}
template <typename DerivedObject, typename EventObject>
void TemplateActionWithObjectHandle<DerivedObject, EventObject>::execute(GameObjectBase* _object)
{
    assert(false);
}
template <typename DerivedObject, typename EventObject>
void TemplateActionWithObjectHandle<DerivedObject, EventObject>::execute(GameObjectBase* _object, void* _eventObject, unsigned int _typeHandle)
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

/*template <typename DerivedObject>
void GameObject<DerivedObject>::print(std::string* _output)
{
    _output->append(getObjectName() + "\nChildren:\n");

    for (GameObjectBase* iter = getChildren(); iter; iter = iter->getNext())
    {
        _output->append(iter->getObjectName() + ",\n");
    }
    _output->append("Events:\n");
    for (auto iter = eventHandles().begin(); iter != eventHandles().end(); iter++)
    {
        _output->append(iter->first);
    }
}*/

#endif // GAMEOBJECT_H

































