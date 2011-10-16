#ifndef LISTDISPLAY_H
#define LISTDISPLAY_H

#include <string>
#include <vector>
namespace CEGUI
{
    class Window;
    class Listbox;
}

class ListDisplay
{
    public:
        class Category;
        class Item
        {
            public:
                Item(const std::string _name, Category* _category){name = _name; category = _category;}
                void deleteFromCategory(){category = nullptr;delete this;}
                ~Item();
                const std::string& getName(){return name;}
            protected:
            private:
                std::string name;
                Category* category;
        };
        class Group;
        class Category
        {
            public:
                Category(){}
                ~Category();
                void addItem(Item* _item);
                void removeItem(Item* _item);
            protected:
            private:
                std::vector<Item*> items;
                std::vector<Group*> groups;
        };
        class Group
        {
            public:
                Group(CEGUI::Listbox* _listBox){listBox = _listBox;}
                ~Group();
                void addCategory(Category* _category){categories.push_back(_category);}
                void removeCategory(Category* _category);
            protected:
            private:
                std::vector<Category*> categories;
                CEGUI::Listbox* listBox;
        };
        ListDisplay(CEGUI::Window* _parent, const std::string& _name);
        ListDisplay(CEGUI::Window* _root);
        virtual ~ListDisplay();
        Item* addItem(const std::string& _name, void* _userData, Category* _category);
        void removeItem(Item* _item);
        Category* createCategory(const std::string& _name);
        void removeCategory(Category* _category);
    protected:
    private:
        Group* allGroup;
};

#endif // LISTDISPLAY_H
