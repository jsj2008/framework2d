#ifndef COMPONENTOBJECTSELECTIONVARIABLE_H
#define COMPONENTOBJECTSELECTIONVARIABLE_H

#include <GameModes/Editor/DynamicEditor/DynamicEditorVariable.h>
#include <GameModes/Editor/DynamicEditor.h>
namespace CEGUI
{
    class Window;
}
template <typename Product>
class ComponentObjectSelectionVariable : public DynamicEditorVariable
{
    public:
        ComponentObjectSelectionVariable(CEGUI::Window* _rootWindow, TypeTable* _params, const std::string& _name, AbstractFactoryBase<Product>* _defaultValue, const std::string& _factoryName);
        virtual ~ComponentObjectSelectionVariable();
        void addPropertyBagVariable(CppFactoryLoader* _loader);
    protected:
        void finish();
    private:
        std::string name;
        AbstractFactoryBase<Product>* defaultValue;
        CEGUI::Window* widget;
};

template <typename Product>
class ComponentObjectSelectionVariableFactory : public DynamicEditor::VariableFactory /// Should move this into another file, to prevent the source of this including DynamicEditor
{
    public:
        ComponentObjectSelectionVariableFactory(const std::string& _name, const std::string& _defaultValue);
        DynamicEditorVariable* createVariable(CEGUI::Window* _rootWindow, TypeTable* _params, const std::string& _factoryName){
            return new ComponentObjectSelectionVariable<Product>(_rootWindow,_params,name,defaultValue,_factoryName);}
    private:
        std::string name;
        AbstractFactoryBase<Product>* defaultValue;
};


template <typename Product>
ComponentObjectSelectionVariable<Product>::ComponentObjectSelectionVariable(CEGUI::Window* _rootWindow, TypeTable* _params, const std::string& _name, AbstractFactoryBase<Product>* _defaultValue, const std::string& _factoryName)
:DynamicEditorVariable(_rootWindow, _params, _factoryName)
{
    //ctor
    name = _name;
    defaultValue = _defaultValue;
    widget = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("EditBox.layout", factoryName + name);
    widget->setProperty("Text","Select component");
    _rootWindow->addChildWindow(widget);
}

template <typename Product>
ComponentObjectSelectionVariable<Product>::~ComponentObjectSelectionVariable()
{
    //dtor
}
template <typename Product>
void ComponentObjectSelectionVariable<Product>::addPropertyBagVariable(CppFactoryLoader* _loader)
{
    std::string factoryName = widget->getText().c_str();
    if (widget->getText() != "Select component")
    {
        auto factory = AbstractFactories::global().getFactory<Product>(factoryName);
        typeTable->addValue<AbstractFactoryBase<Product>*>(name, factory);
    }
}

template <typename Product>
void ComponentObjectSelectionVariable<Product>::finish()
{
    std::string factoryName = widget->getText().c_str();
    if (widget->getText() != "Select component")
    {
        auto factory = AbstractFactories::global().getFactory<Product>(factoryName);
        typeTable->addValue<AbstractFactoryBase<Product>*>(name, factory);
    }
}

template <typename Product>
ComponentObjectSelectionVariableFactory<Product>::ComponentObjectSelectionVariableFactory(const std::string& _name, const std::string& _defaultValue)
{
    name = _name;
    defaultValue = AbstractFactories::global().getFactory<Product>(_defaultValue);
}
#endif // COMPONENTOBJECTSELECTIONVARIABLE_H
