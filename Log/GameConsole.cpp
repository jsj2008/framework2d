#include "GameConsole.h"
#include <Log/Log.h>
#include <Filesystem/Filesystem.h>

GameConsoleCommand::GameConsoleCommand(std::string _name)
{
    console = nullptr;
    name = _name;
}


void GameConsoleCommand::outputText(std::string _msg, unsigned int _colour)
{
    console->outputText(_msg, _colour);
}


class SayCommand: public GameConsoleCommand
{
    public:
        SayCommand()
        :GameConsoleCommand("say")
        {
        }
        void execute(const std::string& _parameters)
        {
            std::string outString = "You:" + _parameters; // Append our 'name' to the message we'll display in the list
            outputText(outString);
        }
};
class PrintCommand: public GameConsoleCommand
{
    public:
        PrintCommand()
        :GameConsoleCommand("print")
        {
        }
        void execute(const std::string& _parameters)
        {
            try
            {
                GameObjectBase* _node = console->getCurrentDirectory()->getNode(_parameters);
                std::string outString = _node->getType()->print(_node);
                outputText(outString);
            }
            catch (int i)
            {
                outputText("Failed");
            }
        }
    private:
};
/// For some reason std::string::{rfind and find} are not working correctly
unsigned int rfind(const std::string& _string, char _char)
{
    for (unsigned int pos = _string.size()-1; pos != 0; pos--)
    {
        if (_string[pos] == _char)
        {
            return pos;
        }
    }
    return -1;
}
class ExecuteActionCommand: public GameConsoleCommand
{
    public:
        ExecuteActionCommand()
        :GameConsoleCommand("run")
        {
        }
        void execute(const std::string& _parameters)
        {
            try
            {
                unsigned int index = rfind(_parameters, '.');
                GameObjectBase* _node = console->getCurrentDirectory()->getNode(_parameters.substr(0, index));
                ActionHandle* handle = _node->getType()->getActionHandle(_parameters.substr(index+1, -1));
                if (handle)
                {
                    handle->execute(_node);
                }
                else
                {
                    g_Log.error("Object has no action called '" + _parameters.substr(index+1, -1) +'\'');
                }
                //outputText(_parameters.substr(index+1, -1));
            }
            catch (int i)
            {
                outputText("Operation failed");
            }
        }
};
class ChangeDirectoryCommand: public GameConsoleCommand
{
    public:
        ChangeDirectoryCommand()
        :GameConsoleCommand("cd")
        {
        }
        void execute(const std::string& _parameters)
        {
            try
            {
                GameObjectBase* _node = console->getCurrentDirectory()->getNode(_parameters);
                console->setCurrentDirectory(_node);
            }
            catch (int i)
            {
                outputText("Failed");
            }
        }
    private:
};
GameConsole::GameConsole()
{
    currentDirectory = Filesystem::global();
    createCEGUIWindow();
    addCommand(new SayCommand());
    addCommand(new PrintCommand());
    addCommand(new ExecuteActionCommand());
    addCommand(new ChangeDirectoryCommand());
}

GameConsole::~GameConsole()
{
    //dtor
}

void GameConsole::addCommand(GameConsoleCommand* _command)
{
    if (commands.find((_command->getName())) != commands.end())
        throw -1;
    _command->console = this;
    commands[_command->getName()] = _command;
}
void GameConsole::createCEGUIWindow()
{
    consoleWindow = CEGUI::System::getSingletonPtr()->getGUISheet()->getChild("Root/Console");
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(consoleWindow);
    (this)->registerHandlers();
}

void GameConsole::registerHandlers()
{
    consoleWindow->getChild("Root/Console/SendButton")->subscribeEvent(
                        CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                            &GameConsole::handleSendButtonPressed,
                        this));
    consoleWindow->getChild("Root/Console/EditBox")->subscribeEvent(CEGUI::Editbox::EventMouseClick,
                        CEGUI::Event::Subscriber(&GameConsole::handleTextSubmitted,this));
}
bool GameConsole::handleTextSubmitted(const CEGUI::EventArgs &e)
{
    CEGUI::String Msg = consoleWindow->getChild("Root/Console/EditBox")->getText();
    parseText(Msg);
    consoleWindow->getChild("Root/Console/EditBox")->setText("");

    return true;
}
bool GameConsole::handleSendButtonPressed(const CEGUI::EventArgs &e)
{
    CEGUI::String Msg = consoleWindow->getChild("Root/Console/EditBox")->getText();
    parseText(Msg);
    consoleWindow->getChild("Root/Console/EditBox")->setText("");

    return true;
}
void GameConsole::parseText(CEGUI::String inMsg)
{
    std::string inString = inMsg.c_str();

	if (inString.length() >= 1)
	{
        std::string::size_type commandEnd = inString.find(" ", 0);
        std::string command = inString.substr(0, commandEnd);
        std::string commandArgs;
        if (commandEnd != -1)
        {
            commandArgs = inString.substr(commandEnd + 1, inString.length() - (commandEnd + 1));
        }
        for(std::string::size_type i=0; i < command.length(); i++)
        {
            command[i] = tolower(command[i]);
        }

        auto commandPtr = commands.find(command);
        if (commandPtr == commands.end())
        {
            std::string outString = command + " is an invalid command.";
            outputText(outString);
        }
        else
        {
            commandPtr->second->execute(commandArgs);
        }
	}
}

Logger* GameConsole::newLogger(Logger* _newLogger)
{
    throw "Error: Invalid command for this class";
}
void GameConsole::outputText(std::string _msg, unsigned int _timeStamp, unsigned int _colour)
{
	CEGUI::Listbox *outputWindow = static_cast<CEGUI::Listbox*>(consoleWindow->getChild("Root/Console/ChatBox"));

	CEGUI::ListboxTextItem *newItem=0;
	newItem = new CEGUI::ListboxTextItem(Log::getTimeString(_timeStamp) + ' ' + _msg,CEGUI::HTF_WORDWRAP_LEFT_ALIGNED);
	newItem->setTextColours(_colour);
	outputWindow->addItem(newItem);
}


