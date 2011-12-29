#ifndef UNITTESTING_H
#define UNITTESTING_H

#include <unordered_map>
#include <string>
#include <vector>
class UnitTest;

class UnitTesting
{
    public:
        UnitTesting();
        virtual ~UnitTesting();
        void run(const std::vector<std::string>& _args);
        void addUnitTest(const std::string& _name, UnitTest* _test);
    protected:
    private:
        std::unordered_map<std::string, UnitTest*> tests;
}g_UnitTesting;

#endif // UNITTESTING_H
