#ifndef GeometrySelectorMode_H
#define GeometrySelectorMode_H

#include "../GameMode.h"
class FreeCamera;

class GeometrySelectorMode : public GameMode
{
    public:
        GeometrySelectorMode(FreeCamera* camera);
        virtual ~GeometrySelectorMode();
    protected:
    private:
};

#endif // GeometrySelectorMode_H
