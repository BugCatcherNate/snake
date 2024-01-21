#include <GL/glew.h>
#include <stdio.h>
#include "render.h"
#include "model.h"
#include "../utils/logger.h"
#include "../utils/utils.h"

renderObject initRenderObject(model targetModel){

    renderObject ro;

    glGenVertexArrays(1, &ro.VAO);
    glGenBuffers(1, &ro.VBO);
    glGenBuffers(1, &ro.EBO);

    // Bind VAO
    glBindVertexArray(ro.VAO);

    // Bind VBO and set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, ro.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(targetModel.vertices), targetModel.vertices, GL_STATIC_DRAW);

    // Bind EBO and set element data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ro.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(targetModel.indices), targetModel.indices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // Set texture attribute pointers;
    //
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return ro;
}

textureObject initTextureObject(const char *path){

    textureObject to;

    // Textures
    unsigned int texture;
    to.id = texture;
    ImageData *texture_image = load_image(path);
    // texture 1
    // ---------
    glGenTextures(1, &to.id);
    glBindTexture(GL_TEXTURE_2D, to.id);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_image->width, texture_image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_image->data);
    glGenerateMipmap(GL_TEXTURE_2D);

    return to;
}

void useTexture(textureObject targetTextureObject){

    glBindTexture(GL_TEXTURE_2D, targetTextureObject.id);
};

void draw(renderObject targetObject){

    glBindVertexArray(targetObject.VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void cleanRenderObject(renderObject targetObject){

    glDeleteVertexArrays(1, &targetObject.VAO);
    glDeleteBuffers(1, &targetObject.VBO);
    glDeleteBuffers(1, &targetObject.EBO);
    info("Cleaned render object");

}