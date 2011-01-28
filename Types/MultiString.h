#ifndef _MULTI_STRING_
#define _MULTI_STRING_

class MultiString
{
    public:
        MultiString(unsigned int _stringsCapacity = 1);
        ~MultiString();
        unsigned int getLength();
        const char* getLine(unsigned int i);
        void operator << (const char* c);// This does a strcpy, safe for passing static strings (this could be replaced with having an array of bools alongside the chars determining if they should be deleted or not
        void operator << (int i);// Max string length - 8
        void operator << (float f);// Max string length - 9
        char* copyOfData();
        void clear();
        void fileDump();
        void shaderSource(unsigned int shaderObject);
    private:
        void operator << (char* c);
        char** data;
        unsigned int strings;
        unsigned int stringsCapacity;
        void resize(unsigned int newCapacity);
};
#endif
