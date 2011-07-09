#include "TextEditBox.h"
#include <AbstractFactory/FactoryParameters.h>

TextEditBox::TextEditBox()
{
    //ctor
}

TextEditBox::~TextEditBox()
{
    //dtor
}

void TextEditBox::finish()
{
    params->add<std::string>("material", "player");
}
