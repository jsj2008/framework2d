#ifndef SELECTIONBOX_H
#define SELECTIONBOX_H

#include <initializer_list>
#include <vector>
#include "ClickReleaseEvent.h"
class Icon;
class FontPrimitive;

class SelectionBox : public ClickReleaseEvent
{
    public:
        SelectionBox(const Rect& _Rect, std::initializer_list<const char*> _icons);
        virtual ~SelectionBox();
        void click(Vec2i mouse, unsigned char button);
        void render();
        int getCurrentSelection(){return currentSelection;}
        int getNumElements(){return icons.size();}
        void setIcons();
        virtual void selectionTrigger(){} /// Its useful to be able to call this after everything is set up
        void changeResolution(Vec2i newResolution);
    protected:
        unsigned int currentSelection;
    private:
        int div;
        std::vector<Icon*> icons;
        std::vector<FontPrimitive*> fonts;
};

#endif // SELECTIONBOX_H
