#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "math/math.h"
#include "utils/utils.h"
#include "utils/logger.h"

GLuint shaderProgram;

mat4 foodMatrix;
vec3 food_position;
vec3 snakePosition;
DynamicArray snakeMatrix;
int growSnake = 0;

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

        debug("escape pressed");
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS && currentDirection != LEFT)
    {
        debug("right pressed");
        currentDirection = RIGHT;
    }
    else if (key == GLFW_KEY_A && action == GLFW_PRESS && currentDirection != RIGHT)
    {

        debug("left pressed");
        currentDirection = LEFT;
    }
    else if (key == GLFW_KEY_W && action == GLFW_PRESS && currentDirection != DOWN)
    {
        debug("up pressed");
        currentDirection = UP;
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS && currentDirection != UP)
    {
        debug("down pressed");
        currentDirection = DOWN;
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

void momentum(GLFWwindow *window)
{

    if (areFloatsEqual(snakePosition.x, food_position.x, 0.00001) && areFloatsEqual(snakePosition.y, food_position.y, 0.00001))
    {

        growSnake = 1;
        food_position.x = clipToNearestIncrement(randomFloat(-1.0, 1.0), 0.025);
        food_position.y = clipToNearestIncrement(randomFloat(-1.0, 1.0), 0.025);

        mat4_translate(&foodMatrix, food_position);
    }

    for (size_t i = snakeMatrix.size - 1; i > 0; i--)
    {

    if (areFloatsEqual(snakePosition.x, snakeMatrix.data[i].data[3], 0.00001) && areFloatsEqual(snakePosition.y, snakeMatrix.data[i].data[7], 0.00001)){

    glfwSetWindowShouldClose(window, GLFW_TRUE);
    info("COLLISION");
    }
        set_equal(&snakeMatrix.data[i], snakeMatrix.data[i - (size_t)1]);
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
}

int main()
{

    info("Application Started");
    ImageData* container_image = load_image("resources/textures/container.jpg");
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
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // top right
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,// bottom left
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // Set texture attribute pointers;
    //
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
 

    // Textures
    unsigned int texture;
    // texture 1
    // ---------
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); 
     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, container_image->width, container_image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, container_image->data);
    glGenerateMipmap(GL_TEXTURE_2D);
    // Load Shader Files
    const char *fragmentShaderSource = loadFile("shaders/frag_shader.glsl");
    const char *vertexShaderSource = loadFile("shaders/vert_shader.glsl");
    // Create vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkShaderCompilation(vertexShader, "Vertex");

    // Create fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompilation(fragmentShader, "Fragment");

    // Create shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Cleanup shader sources
    free((void *)fragmentShaderSource);
    free((void *)vertexShaderSource);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    mat4 snake_head;
    pushBack(&snakeMatrix, snake_head);
    mat4_identity(&snakeMatrix.data[0]);
    mat4_scale(&snakeMatrix.data[0], 0.01f);

    double last_draw = 0;
    food_position.x = clipToNearestIncrement(randomFloat(-1.0, 1.0), 0.025);
    food_position.y = clipToNearestIncrement(randomFloat(-1.0, 1.0), 0.025);
    food_position.z = 0.0;

    mat4_identity(&foodMatrix);
    mat4_scale(&foodMatrix, 0.01f);
    mat4_translate(&foodMatrix, food_position);

    glfwSetKeyCallback(window, key_callback);
    
            glUseProgram(shaderProgram);
        glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"),0); 

    while (!glfwWindowShouldClose(window))
    {

        double seconds = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT);
        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");

        // Draw Snake
        for (size_t i = 0; i < snakeMatrix.size; i++)
        {
            glUniformMatrix4fv(modelLoc, 1, GL_TRUE, &snakeMatrix.data[i]);

        glBindTexture(GL_TEXTURE_2D, texture);

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        };
        // Draw Food
        glUniformMatrix4fv(modelLoc, 1, GL_TRUE, foodMatrix.data);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (seconds - last_draw >= 0.1f)
        {

            if (growSnake == 1)
            {
                debug("food colision");
                mat4 another;
                mat4_identity(&another);
                mat4_scale(&another, 0.01f);
                pushBack(&snakeMatrix, another);
                growSnake = 0;
            }
            momentum(window);
            check_bounds();
            last_draw = seconds;
        }
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();

    freeDynamicArray(&snakeMatrix);
    info("Application Ended");
    return 0;
}
