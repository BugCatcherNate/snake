#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "graphics/model.h"
#include "graphics/shader.h"
#include "graphics/render.h"
#include "utils/utils.h"
#include "utils/logger.h"
#include "utils/text.h"
#include "math/math.h"

mat4 foodMatrix;
vec3 food_position;
vec3 snakePosition;
std::vector<mat4> snakeMatrix;
bool growSnake = false;
model mainModel;

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

Direction currentDirection = Direction::NONE;

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
    if (key == GLFW_KEY_D && action == GLFW_PRESS && currentDirection != Direction::LEFT)
    {
        debug("right pressed");
        currentDirection = Direction::RIGHT;
    }
    else if (key == GLFW_KEY_A && action == GLFW_PRESS && currentDirection != Direction::RIGHT)
    {
        debug("left pressed");
        currentDirection = Direction::LEFT;
    }
    else if (key == GLFW_KEY_W && action == GLFW_PRESS && currentDirection != Direction::DOWN)
    {
        debug("up pressed");
        currentDirection = Direction::UP;
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS && currentDirection != Direction::UP)
    {
        debug("down pressed");
        currentDirection = Direction::DOWN;
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

void momentum(GLFWwindow *window)
{
    if (areFloatsEqual(snakePosition.x, food_position.x, 0.00001) && areFloatsEqual(snakePosition.y, food_position.y, 0.00001))
    {
        growSnake = true;
        food_position.x = clipToNearestIncrement(randomFloat(-1.0, 1.0), 0.025);
        food_position.y = clipToNearestIncrement(randomFloat(-1.0, 1.0), 0.025);

        mat4_translate(&foodMatrix, food_position);
    }

    for (size_t i = snakeMatrix.size() - 1; i > 0; i--)
    {
        if (areFloatsEqual(snakePosition.x, snakeMatrix[i].data[3], 0.00001) && areFloatsEqual(snakePosition.y, snakeMatrix[i].data[7], 0.00001))
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            info("COLLISION");
        }
        snakeMatrix[i] = snakeMatrix[i - 1];
    }

    switch (currentDirection)
    {
    case Direction::LEFT:
        snakePosition.x -= 0.025f;
        break;
    case Direction::RIGHT:
        snakePosition.x += 0.025f;
        break;
    case Direction::UP:
        snakePosition.y += 0.025f;
        break;
    case Direction::DOWN:
        snakePosition.y -= 0.025f;
        break;
    default:
        break;
    }

    mat4_translate(&snakeMatrix[0], snakePosition);
}

int main()
{
    info("Application Started");

    TextLib textLib;
    snakeMatrix.reserve(5);

    if (!glfwInit())
    {
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(800, 600, "Snake", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    model mainModel = {{
                           1.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // top right
                           1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
                           -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
                           -1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
                       },
                       {
                           0, 1, 3, // first triangle
                           1, 2, 3  // second triangle
                       }};

    renderObject mainObject = initRenderObject(mainModel);

    textureObject mainTextureObject = initTextureObject("resources/textures/happy_face.jpg");

    Shader myShader = Shader("shaders/vert_shader.glsl", "shaders/frag_shader.glsl");
    Shader textShader = Shader("shaders/text_vert_shader.glsl", "shaders/text_frag_shader.glsl");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    mat4 snake_head;
    snakeMatrix.push_back(snake_head);
    mat4_identity(&snakeMatrix[0]);
    mat4_scale(&snakeMatrix[0], 0.05f);

    double last_draw = 0;
    food_position.x = clipToNearestIncrement(randomFloat(-1.0, 1.0), 0.025);
    food_position.y = clipToNearestIncrement(randomFloat(-1.0, 1.0), 0.025);
    food_position.z = 0.0;

    mat4_identity(&foodMatrix);
    mat4_scale(&foodMatrix, 0.05f);
    mat4_translate(&foodMatrix, food_position);

    glfwSetKeyCallback(window, key_callback);

    myShader.use();
    myShader.setUniformLi("ourTexture", 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window))
    {
        double seconds = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT);

        // Draw Snake
        for (const auto &matrix : snakeMatrix)
        {
            myShader.setUniformMat4("model", matrix);
            useTexture(mainTextureObject);
            draw(mainObject);
        }

        // Draw Food
        myShader.setUniformMat4("model", foodMatrix);
        useTexture(mainTextureObject);
        draw(mainObject);

        textShader.use();
        textShader.setUniform3f("textColor", 0.5, 0.0, 0.0);
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (seconds - last_draw >= 0.1f)
        {
            if (growSnake)
            {
                debug("food collision");
                mat4 another;
                mat4_identity(&another);
                mat4_scale(&another, 0.05f);
                snakeMatrix.push_back(another);
                growSnake = false;
            }
            momentum(window);
            check_bounds();
            last_draw = seconds;
        }
    }

    cleanRenderObject(mainObject);
    glfwTerminate();

    info("Application Ended");
    return 0;
}
