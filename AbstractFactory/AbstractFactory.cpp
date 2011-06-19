#include "AbstractFactory.h"
template<typename Product, class DerivedType>
char AbstractFactory<Product, DerivedType>::registration = g_AbstractFactories.registerFactoryType<DerivedType>(DerivedType::getName());

