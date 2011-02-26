#ifndef JOINTEDITORMODE_H
#define JOINTEDITORMODE_H

#include <GameModes/GameMode.h>
class FreeCamera;

class JointEditorMode : public GameMode
{
    public:
        JointEditorMode(FreeCamera* camera);
        virtual ~JointEditorMode();
    protected:
    private:
};

#endif // JOINTEDITORMODE_H
