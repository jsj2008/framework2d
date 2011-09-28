#ifndef COMPONENTOBJECTSELECTIONVARIABLE_H
#define COMPONENTOBJECTSELECTIONVARIABLE_H

#include <GameModes/Editor/DynamicEditor/DynamicEditorVariable.h>
#include <GameModes/Editor/DynamicEditor.h>
template <typename Product>
class ItemList;

template <typename Product>
class ComponentObjectSelectionVariable : public DynamicEditorVariable
{
    public:
        ComponentObjectSelectionVariable(CEGUI::Window* _rootWindow, ItemList<Product>* _itemList, TypeTable* _params, const std::string& _name, AbstractFactoryBase<Product>* _defaultValue, const std::string& _factoryName);
        virtual ~ComponentObjectSelectionVariable();
        void addPropertyBagVariable(CppFactoryLoader* _loader);
        bool listDisplay(const CEGUI::EventArgs& _args);
        void setFactory(AbstractFactoryBase<Product>* _value);
    protected:
        void finish();
    private:
        std::string name;
        AbstractFactoryBase<Product>* value;
        ItemList<Product>* itemList;
        CEGUI::Window* displayButton;
};

template <typename Product>
class ComponentObjectSelectionVariableFactory : public DynamicEditor::VariableFactory /// Should move this into another file, to prevent the source of this including DynamicEditor
{
    public:
        ComponentObjectSelectionVariableFactory(const std::string& _name, const std::string& _defaultValue);
        DynamicEditorVariable* createVariable(CEGUI::Window* _rootWindow, TypeTable* _params, const std::string& _factoryName){
            return new ComponentObjectSelectionVariable<Product>(_rootWindow, itemList,_params,name,defaultValue,_factoryName);}
    private:
        std::string name;
        AbstractFactoryBase<Product>* defaultValue;
        ItemList<Product>* itemList;
};

#include <UI/ItemList.h>
#include <AbstractFactory/FactoryLoaders/CppFactoryLoader.h>
#include <iostream>
template <typename Product>
ComponentObjectSelectionVariable<Product>::ComponentObjectSelectionVariable(CEGUI::Window* _rootWindow, ItemList<Product>* _itemList, TypeTable* _params, const std::string& _name, AbstractFactoryBase<Product>* _defaultValue, const std::string& _factoryName)
:DynamicEditorVariable(nullptr, _params, _factoryName) /// FIXME base class doesn't need these variables
{
    //ctor
    name = _name;
    value = _defaultValue;
    itemList = _itemList;
    displayButton = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("ComponentSelectionDisplay.layout", factoryName + name);
    displayButton->setProperty("Text","Select component");
    displayButton->subscribeEvent(CEGUI::Window::EventMouseClick, {&ComponentObjectSelectionVariable::listDisplay, this});
    _rootWindow->addChildWindow(displayButton);
}

template <typename Product>
ComponentObjectSelectionVariable<Product>::~ComponentObjectSelectionVariable()
{
    //dtor
}
template <typename Product>
void ComponentObjectSelectionVariable<Product>::addPropertyBagVariable(CppFactoryLoader* _loader)
{
    _loader->addValue<AbstractFactoryBase<Product>*>(name, value);
}

template <typename Product>
void ComponentObjectSelectionVariable<Product>::finish()
{
    typeTable->addValue<AbstractFactoryBase<Product>*>(name, value);
}

template <typename Product>
bool ComponentObjectSelectionVariable<Product>::listDisplay(const CEGUI::EventArgs& _args)
{
    itemList->setListener(this);
    return true;
}

template <typename Product>
void ComponentObjectSelectionVariable<Product>::setFactory(AbstractFactoryBase<Product>* _value)
{
    value = _value;
    displayButton->setText(_value->getInstanceName());
}
template <typename Product>
ComponentObjectSelectionVariableFactory<Product>::ComponentObjectSelectionVariableFactory(const std::string& _name, const std::string& _defaultValue)
{
    name = _name;
    defaultValue = AbstractFactories::global().getFactory<Product>(_defaultValue);
    CEGUI::Window* widget = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("ComponentSelection.layout", name);
    widget->setText(name);
    itemList = new ItemList<Product>(widget, static_cast<CEGUI::Combobox*>(widget->getChildAtIdx(2)));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(widget);
}
#endif // COMPONENTOBJECTSELECTIONVARIABLE_H
