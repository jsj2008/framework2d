#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

class Camera;
#include <Graphics/Skins/Skin.h>
#include <Graphics/GraphicalContentManager.h>
#include <Types/Vec2i.h>
#include <Box2D/Common/b2Settings.h>
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
        struct ConvexPolygonSkinDef
        {
            unsigned int texture;
            float points[b2_maxPolygonVertices*2];
            unsigned char numPoints;
        };
        StaticSkinDef staticSkinDef;
        ConvexPolygonSkinDef convexPolygonSkinDef;
    };
    /// Members
    GraphicsFactoryDef(SkinType _type);
    SkinType type;
    GraphicsDef graphicsDef;
};
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
        Skin* skinFactory(GraphicsFactoryDef& def);
    protected:
    private:
        Camera* mCamera;
        Vec2i resolution;
        GraphicalContentManager mContentManager;
}g_GraphicsManager;

#endif // GRAPHICSMANAGER_H
