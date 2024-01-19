#ifndef RENDER_H
#define RENDER_H
#include "model.h"

typedef struct {
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    
} renderObject;

renderObject initRenderObject(model targetModel);
#endif