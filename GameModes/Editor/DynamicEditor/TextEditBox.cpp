#include "TextEditBox.h"
#include <AbstractFactory/FactoryParameters.h>
#include <GameModes/Editor/DynamicEditor/DynamicEditorMode.h>
#include <Log/GameConsole.h>

extern GameConsole* g_Console;
class GameConsoleStringSetCommand: public GameConsoleCommand
{
    public:
        GameConsoleStringSetCommand(const std::string& _name, const std::string& _default)
        :GameConsoleCommand("set")
        {
            name = _name;
            value = _default;
        }
        void execute(const std::string& _params)
        {
            value = _params;
        }
        const std::string& getValue()
        {
            return value;
        }
    private:
        std::string name, value;
};
TextEditBox::TextEditBox(DynamicEditorMode* _editor, FactoryParameters* _params)
:DynamicEditorVariable(_editor, _params)
{
    //ctor
    command = new GameConsoleStringSetCommand("material","player");
    g_Console->addCommand(command);

    widget = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("EditBox.layout", "material");
    editor->addChildWindow(widget);
}

TextEditBox::~TextEditBox()
{
    //dtor
    delete command;
}

void TextEditBox::finish()
{
    params->add<std::string>("material", widget->getProperty("Text").c_str());
}
