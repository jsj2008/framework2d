#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <vector>

class VertexArray
{
    public:
        VertexArray();
        virtual ~VertexArray();
    protected:
    private:
        std::vector<float> vertices;
};

#endif // VERTEXARRAY_H
