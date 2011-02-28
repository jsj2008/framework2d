#ifndef SELECTIONBOX_H
#define SELECTIONBOX_H

#include <initializer_list>
#include <vector>
#include "ClickReleaseEvent.h"
class Icon;

class SelectionBox : public ClickReleaseEvent
{
    public:
        SelectionBox(const Rect& _Rect, std::initializer_list<Icon*> _icons);
        virtual ~SelectionBox();
        void click(Vec2i mouse, unsigned char button);
        void render();
        int getCurrentSelection(){return currentSelection;}
        void setNumElements(unsigned int numElements);
        int getNumElements(){return icons.size();}
        //Icon** getIcons(){return icons;}
        void setIcons();
        virtual void selectionTrigger(){} /// Its useful to be able to call this after everything is set up
    protected:
        int currentSelection;
    private:
        int div;
        std::vector<Icon*> icons;
};

#endif // SELECTIONBOX_H
