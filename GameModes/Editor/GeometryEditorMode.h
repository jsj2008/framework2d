#ifndef GEOMETRYEDITORMODE_H
#define GEOMETRYEDITORMODE_H

#include <GameModes/GameMode.h>
class FreeCamera;

class GeometryEditorMode : public GameMode
{
    public:
        GeometryEditorMode(FreeCamera* camera);
        virtual ~GeometryEditorMode();
    protected:
    private:
};

#endif // GEOMETRYEDITORMODE_H
