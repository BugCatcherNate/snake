#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <../math/math.h>

class Shader {
public:
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;

    Shader(const std::string& vertexSource, const std::string& fragmentSource);
    ~Shader();

    void use() const;
    void setUniformLi(const std::string& uniformName, GLint value) const;
    void setUniform3f(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z) const;
    void setUniformMat4(const std::string& uniformName, mat4 matrix) const; // New function declaration

private:
    void compileShader(const std::string& vertexSource, const std::string& fragmentSource);
};

#endif // SHADER_H