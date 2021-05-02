#include "Shader.h"
Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    m_vertexPath = vertexPath;
    m_fragmentPath = fragmentPath;
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream shaderFile;
    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        shaderFile.open(vertexPath);
        std::stringstream stream;
        stream << shaderFile.rdbuf();
        shaderFile.close();
        vertexCode = stream.str();
        stream.str(std::string());

        shaderFile.open(fragmentPath);
        stream << shaderFile.rdbuf();
        shaderFile.close();
        fragmentCode = stream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    this->m_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    this->m_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    this->m_shaderProgramId = glCreateProgram();
    compile(vertexCode.c_str(), fragmentCode.c_str());
}

void Shader::compile(const char *vCode, const char *fCode) {
    glShaderSource(this->m_vertexShaderId, 1, &vCode, nullptr);
    glCompileShader(this->m_vertexShaderId);

    glShaderSource(this->m_fragmentShaderId, 1, &fCode, nullptr);
    glCompileShader(this->m_fragmentShaderId);

    glAttachShader(this->m_shaderProgramId, this->m_vertexShaderId);
    glAttachShader(this->m_shaderProgramId, this->m_fragmentShaderId);
    glLinkProgram(this->m_shaderProgramId);
    int success;
    char infoLog[1024];
    glGetShaderiv(this->m_shaderProgramId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(this->m_shaderProgramId, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR " << infoLog << std::endl;
    }
    glGetProgramiv(this->m_shaderProgramId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->m_shaderProgramId, 1024, NULL, infoLog);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR" << infoLog << std::endl;
    }
    glDeleteShader(this->m_vertexShaderId);
    glDeleteShader(this->m_fragmentShaderId);
}