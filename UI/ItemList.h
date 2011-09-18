#ifndef ITEMLIST_H
#define ITEMLIST_H

namespace CEGUI
{
    class Listbox;
}
#include <string>

class ItemList
{
    public:
        ItemList(const std::string& _listboxWindowName);
        virtual ~ItemList();
    protected:
    private:
        CEGUI::Listbox* listBox;
};

#endif // ITEMLIST_H
