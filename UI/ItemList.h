#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <Events/EventListener.h>
#include <Events/Events/FactoryCreateEvent.h>
#include <string>
namespace CEGUI
{
    class Window;
    class Combobox;
    class EventArgs;
}
template <typename Product>
class AbstractFactoryBase;
template <typename Product>
class ComponentObjectSelectionVariable;

template <typename Product>
class ItemList : public EventsListener<FactoryCreateEvent<Product>>
{
    public:
        ItemList(CEGUI::Window* _root, CEGUI::Combobox* _listBox);
        virtual ~ItemList();

        bool trigger(FactoryCreateEvent<Product>* _event);
        bool selectFactoryCallback(const CEGUI::EventArgs& _args);
        std::string getSelectedName(); /// Both of these will throw an exception if there is no selection
        AbstractFactoryBase<Product>* getSelectedFactory();
        void setListener(ComponentObjectSelectionVariable<Product>* _variable);
    protected:
    private:
        CEGUI::Window* root;
        CEGUI::Combobox* listBox;
        ComponentObjectSelectionVariable<Product>* variable;
};

#include <Events/Events.h>
#include <CEGUI/CEGUI.h>
#include <GameModes/Editor/DynamicEditor/ComponenObjectSelectionVariable.h>

template <typename Product>
ItemList<Product>::ItemList(CEGUI::Window* _root, CEGUI::Combobox* _listBox)
{
    //ctor
    root = _root;
    listBox = _listBox;
    Events::global().registerListener(this, {eReadQueue});
    listBox->subscribeEvent(CEGUI::Combobox::EventDropListRemoved, {&ItemList::selectFactoryCallback, this});

    variable = nullptr;
}

template <typename Product>
ItemList<Product>::~ItemList()
{
    //dtor
}

template <typename Product>
bool ItemList<Product>::trigger(FactoryCreateEvent<Product>* _event)
{
    CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(_event->getFactoryName());
    item->setUserData(_event->getFactory());
    listBox->addItem(item);
    return true;
}
template <typename Product>
std::string ItemList<Product>::getSelectedName()
{
    return listBox->getText().c_str();
}
template <typename Product>
AbstractFactoryBase<Product>* ItemList<Product>::getSelectedFactory()
{
    throw -1;
}
template <typename Product>
void ItemList<Product>::setListener(ComponentObjectSelectionVariable<Product>* _variable)
{
    variable = _variable;
    root->setVisible(true);
    root->moveToFront();
}
template <typename Product>
bool ItemList<Product>::selectFactoryCallback(const CEGUI::EventArgs& _args)
{
    if (listBox->getSelectedItem() != nullptr)
    {
        variable->setFactory(static_cast<AbstractFactoryBase<Product>*>(listBox->getSelectedItem()->getUserData()));
        root->setVisible(false);
    }
    return true;
}

#endif // ITEMLIST_H
