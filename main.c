#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

GLuint shaderProgram;

int pieces = 4;
float snakeMatrix[4][16];

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

enum Direction currentDirection = NONE;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS && currentDirection != LEFT) {

        currentDirection = RIGHT;

    }
    else if (key == GLFW_KEY_A && action == GLFW_PRESS && currentDirection != RIGHT)
    {
        currentDirection = LEFT;
    }
    else if (key == GLFW_KEY_W && action == GLFW_PRESS && currentDirection != DOWN)
    {

        currentDirection = UP;
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS && currentDirection != UP) {
        currentDirection = DOWN;
    }
}

void momentum()
{
    for (int i = pieces; i > 0; i--){
        set_equal(snakeMatrix[i], snakeMatrix[i-1]);
    }

    if (currentDirection == LEFT)
    {

        mat4_translate(snakeMatrix[0], -0.025f, 0.0f, 0.0f);
    }
    else if (currentDirection == RIGHT)
    {

        mat4_translate(snakeMatrix[0], 0.025f, 0.0f, 0.0f);
    }
    else if (currentDirection == UP)
    {

        mat4_translate(snakeMatrix[0], 0.0f, 0.025f, 0.0f);
    }
    else if (currentDirection == DOWN)
    {
        mat4_translate(snakeMatrix[0], 0.0f, -0.025f, 0.0f);
    }
}

int main()
{

    if (!glfwInit())
    {
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(800, 600, "Snake", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    float vertices[] = {
        1.0f, 1.0f, 0.0f,   // top right
        1.0f, -1.0f, 0.0f,  // bottom right
        -1.0f, -1.0f, 0.0f, // bottom left
        -1.0f, 1.0f, 0.0f   // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind VBO and set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind EBO and set element data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Load Shader Files
    const char *fragmentShaderSource = loadFile("frag_shader.glsl");
    const char *vertexShaderSource = loadFile("vert_shader.glsl");
    // Create vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Cleanup shader sources
    free((void *)fragmentShaderSource);
    free((void *)vertexShaderSource);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    for (int i = 0; i<pieces; i++){
    mat4_identity(snakeMatrix[i]);
    mat4_scale(snakeMatrix[i], 0.01f);

    }
    // Get the location of the model matrix uniform from the shader

    // Pass the model matrix to the shader

    double last_draw = 0;

    glfwSetKeyCallback(window, key_callback);
    while (!glfwWindowShouldClose(window))
    {


        double seconds = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT);
        // Draw the square

        glUseProgram(shaderProgram);
        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");


        // Pass the model matrix to the shader
        for (int i=0; i<pieces; i++){
        glUniformMatrix4fv(modelLoc, 1, GL_TRUE, snakeMatrix[i]);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        };
        // Pass the model matrix to the shader
 

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (seconds - last_draw >= 0.1f)
        {
            momentum();
            last_draw = seconds;
        }
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();

    return 0;
}
