#ifndef GRAPHICALCONTENTMANAGER_H
#define GRAPHICALCONTENTMANAGER_H

#include <Graphics/Contexts/TextureContext.h>
class GraphicalContentManager
{
    public:
        GraphicalContentManager();
        virtual ~GraphicalContentManager();
        TextureContext* getTexture(unsigned int reference);
    protected:
    private:
        TextureContext* textures;
};

#endif // GRAPHICALCONTENTMANAGER_H
