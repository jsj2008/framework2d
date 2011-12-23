#ifndef SHADERCONTEXT_H
#define SHADERCONTEXT_H

#include <Graphics/Contexts/GraphicalContext.h>

class ShaderContext: public GraphicalContext
{
    public:
        ShaderContext(const char* _name = nullptr);
        virtual ~ShaderContext();
    protected:
    private:
        void load(){}
        void unload(){}
        void bind(){}
};

#endif // SHADERCONTEXT_H
