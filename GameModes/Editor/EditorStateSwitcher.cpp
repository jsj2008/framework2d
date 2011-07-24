#include "EditorStateSwitcher.h"
#include <Input/Mouse/InputContext.h>
#include <Input/InputManager.h>
#include <Game.h>
#include <CEGUI/CEGUI.h>
#include <iostream>

EditorStateSwitcher::EditorStateSwitcher(const char* tabControlName, std::initializer_list<std::string> _icons, InputContext** _states)
{
    //ctor
    //CEGUI::Window *myRoot = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("TabControlDemo.layout");
    //CEGUI::System::getSingleton().setGUISheet( myRoot );

    CEGUI::Window* guiSheet = CEGUI::System::getSingleton().getGUISheet();
    tab = (CEGUI::TabControl*)guiSheet->getChildRecursive(tabControlName);
    if (tab == nullptr)
    {
        std::cout << "Failed to find CEGUI window " << tabControlName << std::endl;
    }
    states.resize(_icons.size());
    for (unsigned int i = 0; i < _icons.size(); i++)
    {
        states[i] = _states[i];
    }
    auto iter = _icons.begin();
    for (unsigned int i = 0; i < _icons.size(); i++)
    {
        CEGUI::Window *page = CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout(*iter + ".layout");
        tab->addTab(page);
        CEGUI::System::getSingleton().getGUISheet()->getChildRecursive(*iter)->subscribeEvent(CEGUI::TabButton::EventShown,CEGUI::SubscriberSlot(&InputContext::activate,states[i]));
        iter++;
    }
    eventShow();
}

EditorStateSwitcher::~EditorStateSwitcher()
{
    //dtor
}
void EditorStateSwitcher::eventShow()
{
    tab->setSelectedTabAtIndex(states.size());
}
void EditorStateSwitcher::push(const char* name, InputContext* event)
{

}
void EditorStateSwitcher::selectionTrigger()
{
    //g_Game.set(root,states[currentSelection]);
    /*GameMode* top = g_Game.top();
    while (top != root)
    {
        g_Game.pop();
        top = g_Game.top();
    }
    g_Game.push(states[currentSelection]);
    states[currentSelection]->set();*/
}
