#ifndef FBO_H_
#define FBO_H_

#include "glad/glad.h"
#include <memory>

namespace hdgbdn
{
    class FBO
    {
    public:
        FBO(const int w, const int h);
        FBO(const FBO&);
        FBO(FBO&&);
        FBO& operator=(const FBO&);
        FBO& operator=(FBO&&);
        static void BindFBO(const FBO&);
        static void UnBindFBO(const FBO&);
    private:
        std::shared_ptr<unsigned int> pFrameBufferID;
        std::shared_ptr<unsigned int> pRenderBufferID;
    };
}


#endif