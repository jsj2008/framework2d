#ifndef UNITTEST_H
#define UNITTEST_H


class UnitTest
{
    public:
        UnitTest();
        virtual ~UnitTest();
        virtual void run(bool _intensive)=0;
    protected:
    private:
};

#endif // UNITTEST_H
