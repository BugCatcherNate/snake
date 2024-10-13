#include "shader.h"
#include "../math/math.h"
#include "../utils/utils.h"
#include "../utils/logger.h"

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource) {
    compileShader(vertexSource, fragmentSource);
}

Shader::~Shader() {
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);
}

void Shader::use() const {
    glUseProgram(this->shaderProgram);
}

void Shader::setUniformLi(const std::string& uniformName, GLint value) const {
    glUniform1i(glGetUniformLocation(this->shaderProgram, uniformName.c_str()), value);
}

void Shader::setUniform3f(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z) const {
    glUniform3f(glGetUniformLocation(this->shaderProgram, uniformName.c_str()), x, y, z);
}

    void Shader::setUniformMat4(const std::string& uniformName, mat4 matrix) const{
glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram, uniformName.c_str()), 1, GL_FALSE, matrix.data);
    }


void Shader::compileShader(const std::string& vertexSource, const std::string& fragmentSource) {
    // Compilation logic for vertex and fragment shaders
}