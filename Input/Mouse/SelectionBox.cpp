#include "SelectionBox.h"
#include <GL/gl.h>
#include <Graphics/Primitives/Icon.h>

SelectionBox::SelectionBox(const Rect& _Rect,std::initializer_list<Icon*> _icons)
:ClickReleaseEvent(_Rect)
{
    //ctor
    icons = _icons;
    div = (mRect.x2 - mRect.x)/icons.size();
    currentSelection = icons.size();
    Vec2i dimensions(div,mRect.y2-mRect.y);
    for (unsigned int i = 0; i < icons.size(); i++)
    {
        if (icons[i] != NULL) // FIXME
            icons[i]->setDimensions(dimensions);
    }
}

SelectionBox::~SelectionBox()
{
    //dtor
    for (auto i = icons.begin(); i != icons.end(); i++)
    {
        if (*i != NULL)
        {
            delete (*i);
        }
    }
}
void SelectionBox::changeResolution(Vec2i newResolution)
{
    mRect.changeResolution(newResolution);
    div = (mRect.x2 - mRect.x)/icons.size();
}
/// This only works horizontally atm
void SelectionBox::click(Vec2i mouse, unsigned char button)
{
    mouse.x -= mRect.x;
    int newSelection = mouse.x / div;
    currentSelection = newSelection;
    selectionTrigger();
}
void SelectionBox::setNumElements(unsigned int numElements)
{
    while (icons.size() < numElements)
    {
        icons.push_back(NULL);
    }
    while (icons.size() > numElements)
    {
        delete icons.back();
        icons.pop_back();
    }
}

void SelectionBox::render()
{
    glPushMatrix(); /// Want to maintain the original transform
    glLoadIdentity();
    Vec2i topLeft(mRect.x,mRect.y);
    for (unsigned int i = 0; i < icons.size(); i++)
    {
        glColor3f(0,0,0);
        glBegin(GL_LINES);
        glVertex2i(mRect.x+(i*div),mRect.y);
        glVertex2i(mRect.x+(i*div),mRect.y2);
        glEnd();
        if (icons[i] != NULL)
        {
            Icon* icon = icons[i];
            icon->draw(topLeft);
        }
        else
        { // Remove this, icons shouldn't be NULL once I'm done FIXME
            glColor3f(1,1,1);
            glBegin(GL_QUADS);
            glTexCoord2f(0,0);
            glVertex2i(mRect.x+(i*div),mRect.y);
            glTexCoord2f(0,1);
            glVertex2i(mRect.x+(i*div),mRect.y2);
            glTexCoord2f(1,1);
            glVertex2i(mRect.x+((i+1)*div),mRect.y2);
            glTexCoord2f(1,0);
            glVertex2i(mRect.x+((i+1)*div),mRect.y);
            glEnd();
        }
        topLeft.x += div;
    }
    if (currentSelection < icons.size())
    {
        glColor3f(1,0,0);
        glBegin(GL_LINE_LOOP);
        glVertex2i(mRect.x+(currentSelection*div),mRect.y);
        glVertex2i(mRect.x+(currentSelection*div),mRect.y2);
        glVertex2i(mRect.x+((currentSelection+1)*div),mRect.y2);
        glVertex2i(mRect.x+((currentSelection+1)*div),mRect.y);
        glEnd();
        glColor3f(1,1,1);
    }
    glPopMatrix();
}
























