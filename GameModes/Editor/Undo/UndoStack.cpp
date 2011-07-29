#include "UndoStack.h"
#include <GameModes/Editor/Undo/UndoEntry.h>

UndoStack::UndoStack()
{
    //ctor
    stackOffset = 0;
}

UndoStack::~UndoStack()
{
    //dtor
}

void UndoStack::init()
{
    window = CEGUI::System::getSingleton().getGUISheet()->getChild("UndoHistory");
    window->getChild("UndoHistory/Undo")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&UndoStack::undoButton, this));
    window->getChild("UndoHistory/Redo")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&UndoStack::redoButton, this));
    listBox = static_cast<CEGUI::Listbox*>(window->getChild("UndoHistory/ListBox"));
}
UndoStack& UndoStack::global()
{
    static UndoStack undoStack;
    return undoStack;
}
bool UndoStack::undoButton(const CEGUI::EventArgs& _args)
{
    if (undoStack.size() - stackOffset != 0)
    {
        undoStack[undoStack.size()-(stackOffset+1)]->undo();
        stackOffset++;
        setInfoboxText();
    }
    return true;
}
bool UndoStack::redoButton(const CEGUI::EventArgs& _args)
{
    if (stackOffset != 0)
    {
        undoStack[undoStack.size()-stackOffset]->redo();
        stackOffset--;
        setInfoboxText();
    }
    return true;
}

void UndoStack::addEntry(UndoEntry* _entry)
{
    while (stackOffset != 0)
    {
        delete undoStack.back();
        undoStack.pop_back();
        stackOffset--;
    }
    undoStack.push_back(_entry);
    _entry->redo();
    CEGUI::ListboxItem* item = new CEGUI::ListboxTextItem(_entry->getListText());
    listBox->addItem(item);
    setInfoboxText();
}

void UndoStack::setInfoboxText()
{
    std::stringstream entries;
    entries << "Undos: " << undoStack.size()-stackOffset << std::endl;
    entries << "Redos: " << stackOffset;
    window->getChild("UndoHistory/InfoBox")->setText(entries.str());
}
