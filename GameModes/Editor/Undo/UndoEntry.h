#ifndef UNDOENTRY_H
#define UNDOENTRY_H

class UndoEntry
{
    public:
        UndoEntry();
        virtual ~UndoEntry();
        virtual void redo()=0; /// This is automatically called by UndoStack
        virtual void undo()=0;
        virtual const char* getListText()=0;
        virtual const char* getTooltipText()=0;
    protected:
};

#endif // UNDOENTRY_H
