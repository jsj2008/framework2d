#ifndef BRAIN_H
#define BRAIN_H

#include <string>
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
        static const std::string name()
        {
            return "Brain";
        }
    protected:
        friend class ShooterGame; /// FIXME
        friend class CarneGame; /// FIXME
        AIEntity* mEntity;
    private:
};

#endif // BRAIN_H
