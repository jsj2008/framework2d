#include "TextBox.h"
#include <Input/InputManager.h>
#include <Graphics/GraphicsManager.h>
#include <Graphics/Primitives/FontPrimitive.h>

TextBox::TextBox(const Vec2i position, const char* name)
:ClickReleaseEvent(Rect(position.x,position.y,position.x+20,position.y+20))
{
    //ctor
    title = g_GraphicsManager.renderFont(name,-1);
    textGraphic = NULL;
}

TextBox::~TextBox()
{
    //dtor
    delete title;
    delete textGraphic;
}

void TextBox::click(Vec2i mouse, unsigned char button)
{
    g_InputManager.activeTextBox(this);
}

void TextBox::inputCharacter(char c)
{
    if (c == 8) /// Backspace
    {
        if (text.size () > 0) text.erase(text.size() - 1);
    }
    else text.push_back(c);
    delete textGraphic;
    textGraphic = g_GraphicsManager.renderFont(text.c_str(),-1);
}
#include <GL/gl.h>
void TextBox::render()
{
    glPushMatrix();
    glLoadIdentity();
    title->draw(Vec2i(mRect.x,mRect.y));
    if (textGraphic != NULL)
    {
        textGraphic->draw(Vec2i (mRect.x,mRect.y+20));
    }
    glPopMatrix();
}
