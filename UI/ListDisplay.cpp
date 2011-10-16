#include "ListDisplay.h"
#include <CEGUI/CEGUI.h>

ListDisplay::ListDisplay(CEGUI::Window* _parent, const std::string& _name)
{
    //ctor
    CEGUI::FrameWindow* root = new CEGUI::FrameWindow("TaharezLook/FrameWindow", _name);
    root->setPosition({{0.5,200},{0.5,200}});
    root->setWidth({0.5,200});
    root->setHeight({0.5,200});

    _parent->addChildWindow(root);
    CEGUI::Listbox* listBox = new CEGUI::Listbox("TaharezLook/Listbox", "Main");
    root->addChildWindow(listBox);

    allGroup = new Group(listBox);
}

ListDisplay::~ListDisplay()
{
    //dtor
}

ListDisplay::Item* ListDisplay::addItem(const std::string& _name, void* _userData, Category* _category)
{
    Item* ret = new Item(_name, _category);
    _category->addItem(ret);
    return ret;
}
void ListDisplay::removeItem(Item* _item)
{
    delete _item;
}
ListDisplay::Category* ListDisplay::createCategory(const std::string& _name)
{
    Category* category = new Category;
    allGroup->addCategory(category);
    return category;
}
void ListDisplay::removeCategory(Category* _category)
{
    allGroup->removeCategory(_category);
    delete _category;
}

void ListDisplay::Category::addItem(Item* _item)
{
    items.push_back(_item);
}
void ListDisplay::Group::removeCategory(Category* _category)
{
    for (unsigned int i = 0; i < categories.size(); i++)
    {
        if (categories[i] == _category)
        {
            categories[i] = categories.back();
            categories.pop_back();
            return;
        }
    }
}

void ListDisplay::Category::removeItem(Item* _item)
{
    for (unsigned int i = 0; i < items.size(); i++)
    {
        if (items[i] == _item)
        {
            items[i] = items.back();
            items.pop_back();
            return;
        }
    }
}

ListDisplay::Category::~Category()
{
    for (unsigned int i = 0; i < groups.size(); i++)
    {
        groups[i]->removeCategory(this);
    }
    for (unsigned int i = 0; i < items.size(); i++)
    {
        items[i]->deleteFromCategory();
    }
}

ListDisplay::Item::~Item()
{
    if (category != nullptr)
    {
        category->removeItem(this);
    }
}
