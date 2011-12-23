#ifndef TRAVERSABLE_H
#define TRAVERSABLE_H

class Traversable
{
    public:
        void traverse(Traversable** prevNext); // Tail call recursion
        virtual bool update()=0;
    protected:
        Traversable();
    private:
        virtual ~Traversable();
        Traversable* next;
};

#endif // TRAVERSABLE_H
