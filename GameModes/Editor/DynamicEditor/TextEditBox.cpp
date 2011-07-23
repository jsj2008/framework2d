#include "TextEditBox.h"
#include <AbstractFactory/FactoryParameters.h>
#include <GameModes/Editor/DynamicEditor/DynamicEditorMode.h>
#include <Log/GameConsole.h>
#include <AbstractFactory/FactoryLoaders/CppFactoryLoader.h>

TextEditBox::TextEditBox(CEGUI::Window* _rootWindow, TypeTable* _params)
:DynamicEditorVariable(_rootWindow, _params)
{
    //ctor
    widget = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("EditBox.layout", "material");
    widget->setProperty("Text","StaticSkinFactory");
    _rootWindow->addChildWindow(widget);
}

TextEditBox::~TextEditBox()
{
    //dtor
}

void TextEditBox::finish()
{
    std::string material = widget->getProperty("Text").c_str();
    if (material == "")
    {
        material = "StaticSkinFactory";
    }
    typeTable->addValue<std::string>("material", material);
}

void TextEditBox::addPropertyBagVariable(CppFactoryLoader* _loader)
{
    std::string material = widget->getProperty("Text").c_str();
    if (material == "")
    {
        material = "StaticSkinFactory";
    }
    _loader->addValue<std::string>("material", material);
}
