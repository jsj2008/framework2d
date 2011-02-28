#include "SelectionBox.h"
#include <GL/gl.h>
#include <Graphics/Primitives/Icon.h>
#include <Graphics/Primitives/FontPrimitive.h>
#include <Graphics/GraphicsManager.h>

SelectionBox::SelectionBox(const Rect& _Rect,std::initializer_list<const char*> _icons)
:ClickReleaseEvent(_Rect)
{
    //ctor
    for (auto i = _icons.begin(); i != _icons.end(); i++)
    {
        icons.push_back(new Icon(*i));
        fonts.push_back(g_GraphicsManager.renderFont(*i,-1));
    }
    div = (mRect.x2 - mRect.x)/icons.size();
    currentSelection = icons.size();
    Vec2i dimensions(div,mRect.y2-mRect.y);
    for (unsigned int i = 0; i < icons.size(); i++)
    {
        icons[i]->setDimensions(dimensions);
    }
}

SelectionBox::~SelectionBox()
{
    //dtor
    for (unsigned int i = 0; i < icons.size(); i++)
    {
        if (icons[i] != NULL)
        {
            delete icons[i];
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

void SelectionBox::render()
{
    glPushMatrix(); /// Want to maintain the original transform
    glLoadIdentity();
    Vec2i topLeft(mRect.x,mRect.y);
    for (unsigned int i = 0; i < fonts.size(); i++)
    {
        glColor3f(0,0,0);
        glBegin(GL_LINES);
        glVertex2i(mRect.x+(i*div),mRect.y);
        glVertex2i(mRect.x+(i*div),mRect.y2);
        glEnd();
        if (icons[i] != NULL)
            icons[i]->draw(topLeft);
        if (fonts[i] != NULL)
        {
            fonts[i]->draw(topLeft);
            glColor3f(0,0,0);
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
    glBindTexture(GL_TEXTURE_2D,0);
}
























