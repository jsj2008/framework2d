#ifndef GAMECONSOLE_H
#define GAMECONSOLE_H

#include <CEGUI/CEGUI.h>
#include <unordered_map>

class GameConsole;
class GameConsoleCommand
{
    public:
        GameConsoleCommand(std::string _name);
        const std::string& getName(){return name;}
        virtual void execute(const std::string& parameters)=0;
    protected:
        void outputText(CEGUI::String _msg, unsigned int colour = -1);
    private:
        friend class GameConsole;
        GameConsole* console;
        std::string name;
};
class GameConsole
{
    public:
       GameConsole();                   // Constructor
       ~GameConsole();
       void addCommand(GameConsoleCommand* _command);
    private:
        friend class GameConsoleCommand;
        void createCEGUIWindow();                                  // The function which will load in the CEGUI Window and register event handlers
        void registerHandlers();                                   // Register our handler functions
        bool handleTextSubmitted(const CEGUI::EventArgs &e);      // Handle when we press Enter after typing
        bool handleSendButtonPressed(const CEGUI::EventArgs &e);  // Handle when we press the Send button
        void parseText(CEGUI::String inMsg);                       // Parse the text the user submitted.
        void outputText(CEGUI::String inMsg,                       // Post the message to the ChatHistory listbox.
              unsigned int colour = -1); //   with a white color default

        CEGUI::Window *consoleWindow;                            // This will be a pointer to the ConsoleRoot window.
        std::unordered_map<std::string, GameConsoleCommand*> commands;
};
#endif // GAMECONSOLE_H
