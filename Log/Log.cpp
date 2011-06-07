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
void Log::warning(const std::string& message)
{
    cout << "Warning " << message << endl;
}
void Log::error(const std::string& message)
{
    cout << "Error " << message << endl;
    throw -1;
}
