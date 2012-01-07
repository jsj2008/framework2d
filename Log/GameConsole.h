#ifndef GAMECONSOLE_H
#define GAMECONSOLE_H

#include <CEGUI/CEGUI.h>
#include <unordered_map>
#include <Log/Logger.h>

class GameConsole;
class GameConsoleCommand
{
    public:
        GameConsoleCommand(std::string _name);
        const std::string& getName(){return name;}
        virtual void execute(const std::string& _parameters)=0;
    protected:
        void outputText(std::string _msg, unsigned int _colour = -1);
    private:
        friend class GameConsole;
        GameConsole* console;
        std::string name;
};
class GameConsole : public Logger
{
    public:
       GameConsole();                   // Constructor
       ~GameConsole();
       void addCommand(GameConsoleCommand* _command);
       Logger* newLogger(Logger* _newLogger);
    private:
        friend class GameConsoleCommand;
        void createCEGUIWindow();                                  // The function which will load in the CEGUI Window and register event handlers
        void registerHandlers();                                   // Register our handler functions
        bool handleTextSubmitted(const CEGUI::EventArgs &e);      // Handle when we press Enter after typing
        bool handleSendButtonPressed(const CEGUI::EventArgs &e);  // Handle when we press the Send button
        void parseText(CEGUI::String inMsg);                       // Parse the text the user submitted.
        void outputText(std::string _msg, unsigned int timeStamp = 0, unsigned int _colour = -1);

        CEGUI::Window *consoleWindow;                            // This will be a pointer to the ConsoleRoot window.
        std::unordered_map<std::string, GameConsoleCommand*> commands;
};
#endif // GAMECONSOLE_H
