#ifndef FRAMEUPDATE_H
#define FRAMEUPDATE_H

#include <Input/InputManager.h>
class DataStream;

class FrameUpdate
{
    public:
        struct Action
        {
            unsigned short entityKey;
            InputActions action;
        };
        FrameUpdate();
        FrameUpdate(DataStream* _stream);
        virtual ~FrameUpdate();
        unsigned short getActionsSize()const{return frameUpdates.size();}
        const Action& getAction(unsigned short _index)const{return frameUpdates[_index];}
        void addAction(const Action& _action){frameUpdates.push_back(_action);}
        void append(FrameUpdate* _update);
        void clear(){frameUpdates.clear();}
        void encode(DataStream* _stream)const;
    protected:
    private:
        std::vector<Action> frameUpdates;
};

#endif // FRAMEUPDATE_H
