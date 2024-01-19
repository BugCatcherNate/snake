#include <GL/glew.h>
#include <stdio.h>
#include "utils.h"
#include "logger.h"
#include "shader.h"

void checkShaderCompilation(GLuint shader, const char *shaderType)
{
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        fprintf(stderr, "Error: %s shader compilation failed\n%s\n", shaderType, infoLog);
    }
}

shader compileShader(char *vertexSource, char *fragmentSource)
{
    shader targetShader;
    // Load Shader Files
    const char *fragmentShaderSource = loadFile(fragmentSource);
    const char *vertexShaderSource = loadFile(vertexSource);
    // Create vertex shader
    targetShader.vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(targetShader.vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(targetShader.vertexShader);
    checkShaderCompilation(targetShader.vertexShader, "Vertex");

    // Create fragment shader
    targetShader.fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(targetShader.fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(targetShader.fragmentShader);
    checkShaderCompilation(targetShader.fragmentShader, "Fragment");

    // Create shader program
    targetShader.shaderProgram = glCreateProgram();
    glAttachShader(targetShader.shaderProgram, targetShader.vertexShader);
    glAttachShader(targetShader.shaderProgram, targetShader.fragmentShader);
    glLinkProgram(targetShader.shaderProgram);

    // Cleanup shader sources
    free((void *)fragmentShaderSource);
    free((void *)vertexShaderSource);
    info("Shader compiled");
    return targetShader;
}

void useShader(shader s)
{
    glUseProgram(s.shaderProgram);
}

void setUniformLi(shader s, char *uniformName, GLint value)
{

    glUniform1i(glGetUniformLocation(s.shaderProgram, uniformName), value);
}

void setUniformMat4(shader s, char *uniformName, mat4 value)
{

    glUniformMatrix4fv(glGetUniformLocation(s.shaderProgram, uniformName), 1, GL_TRUE, value.data);

}
