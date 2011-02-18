#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

class Camera;
#include <Graphics/Skins/Skin.h>
#include <Graphics/GraphicalContentManager.h>
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
        void resize(int newXRes, int newYRes);
        int getXRes(){return xRes;}
        int getYRes(){return yRes;}
        int getViewX();
        int getViewY();
        float getPixelsPerMeter();
        void setCamera(Camera* _camera){mCamera = _camera;}
        Skin* skinFactory(GraphicsFactoryDef& def);
    protected:
    private:
        Camera* mCamera;
        int xRes, yRes;
        GraphicalContentManager mContentManager;
}g_GraphicsManager;

#endif // GRAPHICSMANAGER_H
