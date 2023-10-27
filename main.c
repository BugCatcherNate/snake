#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "math/math.h"
#include "utils.h"

GLuint shaderProgram;

mat4 foodMatrix;
vec3 food_position;
vec3 snakePosition;
int pieces = 1;
DynamicArray snakeMatrix;
int add_piece = 0;

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
    if (key == GLFW_KEY_D && action == GLFW_PRESS && currentDirection != LEFT)
    {

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
    else if (key == GLFW_KEY_S && action == GLFW_PRESS && currentDirection != UP)
    {
        currentDirection = DOWN;
    }
    else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        add_piece = 1;

    }
}
void check_bounds()
{
    if (snakePosition.x > 1.0)
    {
        snakePosition.x = -1.0;
    }
    else if (snakePosition.x < -1.0)
    {
        snakePosition.x = 1.0;
    }

    if (snakePosition.y > 1.0)
    {
        snakePosition.y = -1.0;
    }
    else if (snakePosition.y < -1.0)
    {
        snakePosition.y = 1.0;
    }
}

void momentum()
{
    printf("%d\n", snakeMatrix.capacity);
    for (size_t i = snakeMatrix.size; i > 0; i--)
    {

        set_equal(&snakeMatrix.data[i], &snakeMatrix.data[i - (size_t)1]);
    }

    if (currentDirection == LEFT)
    {

        snakePosition.x -= 0.025f;
    }
    else if (currentDirection == RIGHT)
    {
        snakePosition.x += 0.025f;
    }
    else if (currentDirection == UP)
    {
        snakePosition.y += 0.025f;
    }
    else if (currentDirection == DOWN)
    {
        snakePosition.y += -0.025f;
    }

    mat4_translate(&snakeMatrix.data[0], snakePosition);
 if(add_piece == 1) 
    {
    mat4 another;
    pushBack(&snakeMatrix, another);
    add_piece = 0;
    };
}

int main()
{

initDynamicArray(&snakeMatrix, 5);
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
    for (size_t i = 0; i < pieces; i++)
    {
        mat4 element;
        pushBack(&snakeMatrix, element);
        mat4_identity(&snakeMatrix.data[i]);
        mat4_scale(&snakeMatrix.data[i], 0.01f);
    }

    double last_draw = 0;
    food_position.x = randomFloat(-1.0, 1.0);
    food_position.y = randomFloat(-1.0, 1.0);
    food_position.z = 0.0;

    mat4_identity(&foodMatrix);
    mat4_scale(&foodMatrix, 0.01f);
    mat4_translate(&foodMatrix, food_position);

    glfwSetKeyCallback(window, key_callback);
    while (!glfwWindowShouldClose(window))
    {
   
        double seconds = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");

        // Draw Snake
        for (size_t i = 0; i < snakeMatrix.size; i++)
        {
            glUniformMatrix4fv(modelLoc, 1, GL_TRUE, &snakeMatrix.data[i]);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        };
        // Draw Food
        glUniformMatrix4fv(modelLoc, 1, GL_TRUE, foodMatrix.data);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (seconds - last_draw >= 0.1f)
        {
            momentum();
            check_bounds();
            last_draw = seconds;
        }
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();

    return 0;
}
