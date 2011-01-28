#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

class Camera;
#include <Graphics/Skins/Skin.h>
#include <Graphics/GraphicalContentManager.h>
struct GraphicsFactoryDef
{
    /// Types
    union GraphicsDef
    {
        GraphicsDef(SkinType _type);
        struct StaticSkinDef
        {
            unsigned int texture;
            int width,height;
        };
        StaticSkinDef staticSkinDef;
    };
    /// Members
    GraphicsFactoryDef(SkinType _type);
    SkinType type;
    GraphicsDef graphicsDef;
};
class GraphicsManager
{
    public:
        GraphicsManager();
        virtual ~GraphicsManager();
        void beginScene();
        void endScene();
        int getXRes(){return xRes;}
        int getYRes(){return yRes;}
        void setCamera(Camera* _camera){mCamera = _camera;}
        Skin* skinFactory(GraphicsFactoryDef& def);
    protected:
    private:
        Camera* mCamera;
        int xRes, yRes;
        GraphicalContentManager mContentManager;
};

#endif // GRAPHICSMANAGER_H
