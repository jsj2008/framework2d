#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

class Camera;
#include <Graphics/Skins/Skin.h>
#include <Graphics/GraphicalContentManager.h>
#include <Types/Vec2i.h>
#include <Box2D/Common/b2Settings.h>
#include <Graphics/Camera/Camera.h>
class Icon;
class Sprite;
class SpriteList;

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
        const Vec2f& getCameraTranslation(){return mCamera->getTranslation();}
        float getPixelsPerMeter();
        void setCamera(Camera* _camera){mCamera = _camera;}
        MaterialContext* getMaterial(const char* material){return mContentManager.getMaterial(material);}
        TextureContext* getTexture(const char* texture){return mContentManager.getTexture(texture);}
        void addSprite(Sprite* _sprite);
        void deleteSprite(Sprite* _sprite);
    protected:
    private:
        SpriteList* spriteList;
        Camera* mCamera;
        Vec2i resolution;
        GraphicalContentManager mContentManager;
}g_GraphicsManager;

#endif // GRAPHICSMANAGER_H
