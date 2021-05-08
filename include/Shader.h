#pragma once
#include "CommonHeader.h"
class Shader{
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    void Reload();
    void Use();
    void SetMVP(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
    void set(const std::string name, bool value);
    void set(const std::string name, int value);
    void set(const std::string name, float value);

    void set(const std::string name, const glm::vec2& value);
    void set(const std::string name, float x, float y);

    void set(const std::string name, const glm::vec3& value);
    void set(const std::string name, float x, float y, float z);

    void set(const std::string name, const glm::vec4& value);
    void set(const std::string name, float x, float y, float z, float w);

    void set(const std::string name, const glm::mat2& mat);
    void set(const std::string name, const glm::mat3& mat);
    void set(const std::string name, const glm::mat4& mat);

private:
    std::string m_vertexPath;
    std::string m_fragmentPath;
    unsigned int m_vertexShaderId;
    unsigned int m_fragmentShaderId;
    void load();
    void compile(const char* vCode, const char* fCode);
};