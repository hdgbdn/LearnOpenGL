#pragma once
#include "CommonHeader.h"
class Shader{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    void Reload();
private:
    std::string m_vertexPath;
    std::string m_fragmentPath;
    unsigned int m_vertexShaderId;
    unsigned int m_fragmentShaderId;
    unsigned int m_shaderProgramId;
    void load();
    void compile(const char* vCode, const char* fCode);
};