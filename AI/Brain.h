#ifndef BRAIN_H
#define BRAIN_H

enum BrainType
{
    ePlayerInputBrainType,
    eZombieBrainType,
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
        virtual void update(){}
    protected:
        friend class ShooterGame; /// FIXME
        AIEntity* mEntity;
    private:
};

#endif // BRAIN_H
