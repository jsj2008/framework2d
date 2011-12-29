#include "UnitTesting.h"
#include <UnitTesting/UnitTest.h>
#include <cassert>
#include <iostream>

UnitTesting::UnitTesting()
{
    //ctor
}

UnitTesting::~UnitTesting()
{
    //dtor
}

void UnitTesting::addUnitTest(const std::string& _name, UnitTest* _test)
{
    assert(tests.find(_name) == tests.end());
    tests[_name] = _test;
}
const char* g_HelpString = "No help for you";
void UnitTesting::run(const std::vector<std::string>& _args)
{
    /// C++ needs a string switch block :(
    bool intensive = false;
    auto iter = _args.begin();
    for (; iter != _args.end(); iter++)
    {
        if (*iter == "-h")
        {
            std::cout << g_HelpString;
            return;
        }
        else if (*iter == "-i")
        {
            intensive = true;
        }
        else if (*iter == "-l")
        {
            iter++;
            int num = atoi(iter->c_str());
            for (int i = 0; i < num; i++)
            {
                iter++;
                tests[*iter]->run(intensive);
            }
            break;
        }
        else if (*iter == "-a")
        {
            for (auto iter2 = tests.begin(); iter2 != tests.end(); iter2++)
            {
                iter2->second->run(intensive);
            }
            break;
        }
        else
        {
            std::cout << "Error: Unrecognised argument " + *iter;
            return;
        }
    }
    for (; iter != _args.end(); iter++)
    {
        std::cout << "Syntax error " + *iter + " after tests have run";
    }
}

int main(int _argc, const char** _argv)
{
    std::vector<std::string> args;
    for (int i = 1; i != _argc; i++)
    {
        args.push_back(_argv[i]);
    }
    g_UnitTesting.run(args);
    return 0;
}
