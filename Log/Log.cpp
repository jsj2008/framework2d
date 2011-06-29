#include "Log.h"
#include <iostream>
using namespace std;
Log g_Log;

Log::Log()
{
    //ctor
}

Log::~Log()
{
    //dtor
}
void Log::warning(const std::string& _message)
{
    cout << "Warning " << _message << endl;
}
void Log::error(const std::string& _message)
{
    cout << "Error " << _message << endl;
    throw -1;
}
void Log::message(const std::string& _message)
{
    cout << "Message " << _message << endl;
}
