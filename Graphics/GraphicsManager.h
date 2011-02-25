#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

class Camera;
#include <Graphics/Skins/Skin.h>
#include <Graphics/GraphicalContentManager.h>
#include <Types/Vec2i.h>
#include <Box2D/Common/b2Settings.h>
extern class GraphicsManager
{
    public:
        GraphicsManager();
        virtual ~GraphicsManager();
        void beginScene();
        void endScene();
        void resize(Vec2i newResolution);
        Vec2i getResolution(){return resolution;}
        const Vec2i& getView();
        float getPixelsPerMeter();
        void setCamera(Camera* _camera){mCamera = _camera;}
        MaterialContext* getMaterial(const char* material){return mContentManager.getMaterial(material);}
    protected:
    private:
        Camera* mCamera;
        Vec2i resolution;
        GraphicalContentManager mContentManager;
}g_GraphicsManager;

#endif // GRAPHICSMANAGER_H
