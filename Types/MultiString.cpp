#include "MultiString.h"
#include <string.h>
#include <stdio.h>
MultiString::MultiString(unsigned int _stringsCapacity)
{
    stringsCapacity = _stringsCapacity;
    data = new char*[stringsCapacity];
    strings = 0;
}
MultiString::~MultiString()
{
    stringsCapacity = 0;
    clear();
}
unsigned int MultiString::getLength()
{
    return strings;
}
const char* MultiString::getLine(unsigned int i)
{
    return data[i];
}
void MultiString::operator << (const char* c)
{
    char* newC = new char[strlen(c)+1];
    strcpy(newC,c);
    *this << newC;
}
void MultiString::operator << (int i)
{
    char* c = new char[8];
    sprintf(c,"%d",i);
    *this << c;
}
void MultiString::operator << (float f)
{
    char* c = new char[9];
    sprintf(c,"%f",f);
    *this << c;
}
void MultiString::operator << (char* c)
{
    if (!(strings < stringsCapacity))
    {
        resize(stringsCapacity*2);
    }
    data[strings++] = c;// Post-increment important
}
void MultiString::resize(unsigned int newCapacity)
{
    char** newData = new char*[newCapacity];
    memcpy(newData,data,sizeof(char*)*stringsCapacity);
    delete[] data;
    data = newData;
    stringsCapacity = newCapacity;
}
//char* MultiString::copyOfData();
void MultiString::clear()
{
    for (unsigned int i = 0; i < strings; i++)
    {
        delete[] data[i];
    }
    strings = 0;
    stringsCapacity = 1;
    delete[] data;
    data = new char*[stringsCapacity];
}



#include <fstream>
void MultiString::fileDump()
{
    std::ofstream file("ShaderDump.txt");
	file.clear();
    for (unsigned int i = 0; i < strings; i++)
    {
        file << data[i] << "\n";
    }
    file.close();
}
#include <GL/GLee.h>
void MultiString::shaderSource(unsigned int shaderObject)
{
    glShaderSourceARB(shaderObject, strings, (const GLchar**)data, NULL);
}
