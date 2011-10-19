#ifndef MODEL_H
#define MODEL_H

#include <string>
class VertexArray;

class Model
{
    public:
        Model();
        virtual ~Model();
        void setVertexAttribute(const std::string& _attribute, VertexArray* _array);
    protected:
    private:
};

#endif // MODEL_H
