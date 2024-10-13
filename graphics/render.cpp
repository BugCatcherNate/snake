#include <GL/glew.h>
#include <iostream>
#include <string>
#include "render.h"
#include "model.h"
#include "../utils/logger.h"
#include "../utils/utils.h"

class RenderObject {
public:
    GLuint VAO, VBO, EBO;

    RenderObject(const Model& targetModel) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // Bind VAO
        glBindVertexArray(VAO);

        // Bind VBO and set vertex data
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(targetModel.vertices), targetModel.vertices, GL_STATIC_DRAW);

        // Bind EBO and set element data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(targetModel.indices), targetModel.indices, GL_STATIC_DRAW);

        // Set vertex attribute pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // Set texture attribute pointers
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
};

void loadTexture(const std::shared_ptr<ImageData>& texture_image) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_image->width, texture_image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_image->data.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}