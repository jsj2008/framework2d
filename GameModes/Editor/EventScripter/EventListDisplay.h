#ifndef EVENTLISTDISPLAY_H
#define EVENTLISTDISPLAY_H

#include <UI/ListDisplay.h>

class EventListDisplay : public ListDisplay
{
    public:
        class EventListItem : public Item
        {
            public:
                const std::string& getName(){return name;}
            protected:
                Item(const std::string _name){name = _name;}
            private:
                std::string name;
        };
        class EventListCategory : Category
        {
            public:
                int getId(){return id;}
                void addItem(Item* _item);
                void removeItem(Item* _item);
            protected:
                Category(int _id){id = _id;}
            private:
                int id;
        };
        EventListDisplay();
        virtual ~EventListDisplay();
    protected:
    private:
        Item* addItem(const std::string& _name, void* _userData);
        void removeItem(Item* _item);
        Category* createCategory(const std::string& _name);
        void removeCategory(Category* _category);
};

#endif // EVENTLISTDISPLAY_H
