#include "Shader.h"
namespace Hi {


    Shader::Shader()
    {
        this->m_shaderProgram = 0;
    }

    Shader::~Shader()
    {
    }
    void Shader::Init(const std::string& vertFilename, const std::string& fragFilename)
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertFilename);
            vertexCode = std::string((std::istreambuf_iterator<char>(vShaderFile)), std::istreambuf_iterator<char>());
            vShaderFile.close();

            fShaderFile.open(fragFilename);
            fragmentCode = std::string((std::istreambuf_iterator<char>(fShaderFile)), std::istreambuf_iterator<char>());
            fShaderFile.close();
        }
        catch (std::ifstream::failure e)
        {
            HI_ERROR("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        // print compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            HI_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED : {0}", infoLog);
        };

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            HI_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED : {0}", infoLog);
        };



        this->m_shaderProgram = glCreateProgram();
        glAttachShader(this->m_shaderProgram, vertex);
        glAttachShader(this->m_shaderProgram, fragment);
        glLinkProgram(this->m_shaderProgram);
        
        glGetProgramiv(this->m_shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(this->m_shaderProgram, 512, NULL, infoLog);
            HI_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED : {0}", infoLog);
        }
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Shader::UseShader()
    {
        glUseProgram(this->m_shaderProgram);
    }

    void Shader::setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(this->m_shaderProgram, name.c_str()), (int)value);
    }
    void Shader::setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(this->m_shaderProgram, name.c_str()), value);
    }
    void Shader::setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(this->m_shaderProgram, name.c_str()), value);
    }

    void Shader::setVec2(const std::string& name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(this->m_shaderProgram, name.c_str()), 1, &value[0]);
    }
    void Shader::setVec2(const std::string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(this->m_shaderProgram, name.c_str()), x, y);
    }
    
    void Shader::setVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(this->m_shaderProgram, name.c_str()), 1, &value[0]);
    }

    void Shader::setVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(this->m_shaderProgram, name.c_str()), x, y, z);
    }
    
    void Shader::setVec4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(this->m_shaderProgram, name.c_str()), 1, &value[0]);
    }
    void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(this->m_shaderProgram, name.c_str()), x, y, z, w);
    }
    
    void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(this->m_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    
    void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(this->m_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
   
    void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(this->m_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }


}