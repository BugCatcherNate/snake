#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>

typedef struct {
    GLuint shaderProgram;
    GLuint fragmentShader;
    GLuint vertexShader;
} shader;

void checkShaderCompilation(GLuint shader, const char *shaderType);

shader compileShader(char *vertexSource, char *fragmentSource);

void useShader(shader s);
void setUniform3f(shader s, char *uniformName, GLfloat x, GLfloat y, GLfloat z);
void setUniformLi(shader s, char *uniformName, GLint value);
#endif
