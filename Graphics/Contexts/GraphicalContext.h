#ifndef GRAPHICALCONTEXT_H
#define GRAPHICALCONTEXT_H

#ifndef NULL
#define NULL 0
#endif
#define MAX_NAME 32
class GraphicalContext
{
    public:
        GraphicalContext(const char* _name);
        virtual ~GraphicalContext();
        /// These are the reference counting functions
        void grab(); /// ++
        void release(); /// --
        const char* getName(){return name;}
    protected:
        virtual void vGrab(){}
        virtual void vRelease(){}
        virtual void load()=0;
        virtual void unload()=0;
        virtual void bind()=0;
        unsigned int referenceCount;
        char name[MAX_NAME];
    private:
};

#endif // GRAPHICALCONTEXT_H
