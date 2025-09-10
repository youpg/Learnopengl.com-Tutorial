#pragma once

#ifdef DEBUG
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCheckError())
#else
#define GLCall(x) x
#endif