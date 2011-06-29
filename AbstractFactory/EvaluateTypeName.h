#ifndef EVALUATETYPENAME_H_INCLUDED
#define EVALUATETYPENAME_H_INCLUDED

template <typename Product>
const std::string EvaluateTypeName();



/** Implementation
*
*
*/


#include <cxxabi.h>

template <typename Type>
std::string demangle()
{
    const std::type_info  &ti = typeid(Type);
    char* realname;
    int status;
    realname = abi::__cxa_demangle(ti.name(), 0, 0, &status);
    std::string ret(realname);
    free(realname);
    return ret;
}

template<bool C, typename T = void>
struct IfTest
{
  typedef T type;
};

template<typename T>
struct IfTest<false, T>
{
};

template<typename T, typename Sign>
struct HasName
{
    typedef char yes[1];
    typedef char no [2];
    template <typename U, U> struct type_check;
    template <typename _1> static yes &chk(type_check<Sign, &_1::func> *);
    template <typename   > static no  &chk(...);
    static bool const value = sizeof(chk<T>(0)) == sizeof(yes);
};

template<typename Product>
typename IfTest<HasName<Product, std::string(Product::*)()>::value, std::string>::type getName()
{
   /* getName when T has name() ... */
   return Product::name();
}
#include <Log/Log.h>
template<typename Product>
typename IfTest<!HasName<Product, std::string(Product::*)()>::value, std::string>::type getName()
{
   /* getName when T doesnt have name() ... */
   std::string name = demangle<Product>();
   g_Log.message(name + " doesn't have a name() function defined, consider inserting this code:\n\
static std::string name()\n\
{\n\
    return \"" + name + "\";\n\
}\n\
into the class declaration");
   return name;
}


template <typename Product>
const std::string EvaluateTypeName()
{
    return getName<Product>();
}



#endif // EVALUATETYPENAME_H_INCLUDED
