#ifndef WEAPONCONTENT_H
#define WEAPONCONTENT_H

#include <SharedContent/SharedContent.h>
#include <Factory/ProjectileDef.h>
class Vec2f;

class WeaponContent: public SharedContent
{
    public:
        WeaponContent(const char* _name);
        virtual ~WeaponContent();
        unsigned short getReloadFrames(){return reloadFrames;}
        void fire(const Vec2f& source, const Vec2f& direction);
    private:
        void load();
        void unload();
        void vGrab();
        void vRelease();

        ProjectileDef def;
        unsigned short numberOfProjectiles;
        float maximumSpread; /// Angle
        unsigned short reloadFrames;
};

#endif // WEAPONCONTENT_H
