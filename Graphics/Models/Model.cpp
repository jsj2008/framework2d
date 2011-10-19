#include "Model.h"
#include <Log/Log.h>

Model::Model()
{
    //ctor
}

Model::~Model()
{
    //dtor
}

void Model::setVertexAttribute(const std::string& _attribute, VertexArray* _array)
{
    if (_attribute == "Position")
    {

    }
    else
    {
        g_Log.error("Unrecognised vertex attribute " + _attribute);
    }
}
