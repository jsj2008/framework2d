#include "TextEditBox.h"
#include <AbstractFactory/FactoryParameters.h>
#include <GameModes/Editor/DynamicEditor/DynamicEditorMode.h>
#include <Log/GameConsole.h>
#include <AbstractFactory/FactoryLoaders/CppFactoryLoader.h>

TextEditBox::TextEditBox(CEGUI::Window* _rootWindow, TypeTable* _params, const std::string& _name,
    const std::string& _defaultValue, const std::string& _factoryName, float* _uiElementHeight)
:DynamicEditorVariable(_params, _name)
{
    //ctor
    defaultValue = _defaultValue;
    widget = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("EditBox.layout", _factoryName + _name);

    widget->setPosition(CEGUI::UVector2({{0.5f, 0.0f}, {0.0f,*_uiElementHeight}})); /// FIXME this function should be in the base class
    *_uiElementHeight += widget->getHeight().asAbsolute(0);

    widget->setProperty("Text",_defaultValue);
    _rootWindow->addChildWindow(widget);
}

TextEditBox::~TextEditBox()
{
    //dtor
}

DynamicEditorVariable* TextEditBoxFactory::createVariable(CEGUI::Window* _rootWindow, TypeTable* _params, const std::string& _factoryName, float* _uiElementHeight)
{
    float top = *_uiElementHeight;
    TextEditBox* ret = new TextEditBox(_rootWindow,_params, name, defaultValue,_factoryName, _uiElementHeight);
    float height = *_uiElementHeight - top;
    createNameDisplay(top, height, _rootWindow);
    return ret;
}
void TextEditBox::finish()
{
    std::string value = widget->getProperty("Text").c_str();
    if (value == "")
    {
        value = defaultValue;
    }
    typeTable->addDynamicValue("float", name, value);
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
        _loader->addDynamicValue("float", name, value);
    }
}
