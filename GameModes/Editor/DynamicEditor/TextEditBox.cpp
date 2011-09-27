#include "TextEditBox.h"
#include <AbstractFactory/FactoryParameters.h>
#include <GameModes/Editor/DynamicEditor/DynamicEditorMode.h>
#include <Log/GameConsole.h>
#include <AbstractFactory/FactoryLoaders/CppFactoryLoader.h>

TextEditBox::TextEditBox(CEGUI::Window* _rootWindow, TypeTable* _params, const std::string& _name, const std::string& _defaultValue, const std::string& _factoryName)
:DynamicEditorVariable(_rootWindow, _params, _factoryName)
{
    //ctor
    name = _name;
    defaultValue = _defaultValue;
    widget = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("EditBox.layout", factoryName + name);
    widget->setProperty("Text",defaultValue);
    _rootWindow->addChildWindow(widget);
}

TextEditBox::~TextEditBox()
{
    //dtor
}

void TextEditBox::finish()
{
    std::string value = widget->getProperty("Text").c_str();
    if (value == "")
    {
        value = defaultValue;
    }
    typeTable->addValue<std::string>(name, value);
}

void TextEditBox::addPropertyBagVariable(CppFactoryLoader* _loader)
{
    std::string value = widget->getProperty("Text").c_str();
    if (value == "")
    {
        value = defaultValue;
    }
    else
    {
        _loader->addValue<std::string>(name, value);
    }
}
