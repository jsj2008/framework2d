#ifndef DYNAMICTYPETABLE_H
#define DYNAMICTYPETABLE_H

#include <Types/TypeTable.h>

/* The practical difference between this and its base is that types can be accessed by string, which makes this useful for scripts */

class DynamicTypeTable : public TypeTable
{
    public:
        DynamicTypeTable();
        //DynamicTypeTable(const DynamicTypeTable& rhs);
        typedef std::string TypeIndex;

        // Don't use these unless neccessary, use the functions in the base class unless you're reading from file or something
        Value* addDynamicValue(const TypeIndex& type, const ValueIndex& name);
        void addDynamicValue(const TypeIndex& type, const ValueIndex& name, std::istream* parseSource);
        //void setValue(const ValueIndex& name);
        friend std::ostream& operator<< (std::ostream &out, const DynamicTypeTable &table);
        friend std::istream& operator>> (std::istream &in, DynamicTypeTable &table);

    private:
    template <typename T>
        void registerType(const TypeIndex& name);
        class Type;
        std::unordered_map<TypeIndex,Type*> types;
        class Type
        {
            public:
                Type(){}
                virtual ~Type(){}
                virtual Value* instance()=0;
                virtual Type* clone()=0;
        };
        template <typename T>
        class TemplateType : public Type
        {
            public:
                TemplateType(){}
                Value* instance(){return new TemplateValue<T>;}
                Type* clone(){return new TemplateType<T>;}
        };
        std::unordered_map<std::string,std::string> typeInfoMap;
};

#endif // DYNAMICTYPETABLE_H
