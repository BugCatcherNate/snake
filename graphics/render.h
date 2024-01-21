#ifndef RENDER_H
#define RENDER_H
#include "model.h"

typedef struct {
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    
} renderObject;

typedef struct {

    unsigned int id;
    
} textureObject;


textureObject initTextureObject(const char *path);
void useTexture(textureObject targetTextureObject);
renderObject initRenderObject(model targetModel);

void draw(renderObject targetObject);

void cleanRenderObject(renderObject targetObject);
#endif