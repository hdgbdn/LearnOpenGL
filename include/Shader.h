#pragma once
#include "CommonHeader.h"
class Shader{
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    void Reload();
private:
    std::string m_vertexPath;
    std::string m_fragmentPath;
    unsigned int m_vertexShaderId;
    unsigned int m_fragmentShaderId;
    void load();
    void compile(const char* vCode, const char* fCode);
};