#ifndef FOLDER_H
#define FOLDER_H

#include <GameObject.h>


class Folder : public GameObject<Folder>
{
    public:
        Folder(const std::string& _name);
        virtual ~Folder();
        static std::string name()
        {
            return "Folder";
        }
        static void registerActions(GameObjectType* _type);
    protected:
    private:
};

#endif // FOLDER_H
