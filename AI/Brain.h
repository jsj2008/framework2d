#ifndef BRAIN_H
#define BRAIN_H

enum BrainType
{
    ePlayerInputBrainType,
    eBrainTypesMax
};
class AIEntity;
class Brain
{
    public:
        Brain();
        virtual ~Brain();
        void setEntity(AIEntity* _Entity);
        /// Ai callbacks
        void jump();
    protected:
        AIEntity* mEntity;
    private:
};

#endif // BRAIN_H
