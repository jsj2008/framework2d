#include "GameConsole.h"

GameConsoleCommand::GameConsoleCommand(std::string _name)
{
    console = nullptr;
    name = _name;
}


void GameConsoleCommand::outputText(CEGUI::String message, unsigned int colour)
{
    console->outputText(message, colour);
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
GameConsole::GameConsole()
{
    createCEGUIWindow();
    addCommand(new SayCommand());
}

GameConsole::~GameConsole()
{
    //dtor
}

void GameConsole::addCommand(GameConsoleCommand* _command)
{
    _command->console = this;
    commands[_command->getName()] = _command;
}
void GameConsole::createCEGUIWindow()
{
    consoleWindow = CEGUI::System::getSingletonPtr()->getGUISheet()->getChild("ConsoleRoot");
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(consoleWindow);
    (this)->registerHandlers();
}

void GameConsole::registerHandlers()
{
    consoleWindow->getChild("ConsoleRoot/SendButton")->subscribeEvent(
                        CEGUI::PushButton::EventClicked,
                        CEGUI::Event::Subscriber(
                            &GameConsole::handleSendButtonPressed,
                        this));
    consoleWindow->getChild("ConsoleRoot/EditBox")->subscribeEvent(CEGUI::Editbox::EventMouseClick,
                        CEGUI::Event::Subscriber(&GameConsole::handleTextSubmitted,this));
}
bool GameConsole::handleTextSubmitted(const CEGUI::EventArgs &e)
{
    CEGUI::String Msg = consoleWindow->getChild("ConsoleRoot/EditBox")->getText();
    (this)->parseText(Msg);
    consoleWindow->getChild("ConsoleRoot/EditBox")->setText("");

    return true;
}
bool GameConsole::handleSendButtonPressed(const CEGUI::EventArgs &e)
{
    CEGUI::String Msg = consoleWindow->getChild("ConsoleRoot/EditBox")->getText();
    (this)->parseText(Msg);
    consoleWindow->getChild("ConsoleRoot/EditBox")->setText("");

    return true;
}
void GameConsole::parseText(CEGUI::String inMsg)
{
    std::string inString = inMsg.c_str();

	if (inString.length() >= 1)
	{
        std::string::size_type commandEnd = inString.find(" ", 0);
        std::string command = inString.substr(0, commandEnd);
        std::string commandArgs = inString.substr(commandEnd + 1, inString.length() - (commandEnd + 1));
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


void GameConsole::outputText(CEGUI::String message, unsigned int colour)
{
	CEGUI::Listbox *outputWindow = static_cast<CEGUI::Listbox*>(consoleWindow->getChild("ConsoleRoot/ChatBox"));

	CEGUI::ListboxTextItem *newItem=0;
	newItem = new CEGUI::ListboxTextItem(message,CEGUI::HTF_WORDWRAP_LEFT_ALIGNED);
	newItem->setTextColours(colour);
	outputWindow->addItem(newItem);
}


