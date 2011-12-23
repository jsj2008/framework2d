#ifndef RENDERCALLBACK_H
#define RENDERCALLBACK_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>


class RenderCallback : public b2QueryCallback
{
    public:
        RenderCallback();
        virtual ~RenderCallback();
        bool ReportFixture(b2Fixture* fixture);
    protected:
    private:
};

#endif // RENDERCALLBACK_H
