#ifndef UTILS_H
#define UTILS_H
#include "../math/math.h"

typedef struct {
    mat4 *data;
    size_t size;
    size_t capacity;
} DynamicArray;

typedef struct {
    unsigned char *data;
    int height;
    int width;
    int nrChannels;
} ImageData;

const char *loadFile(const char *filename);
float randomFloat(float min, float max);
void initDynamicArray(DynamicArray *arr, size_t initialCapacity);
float clipToNearestIncrement(float value, float increment);
int areFloatsEqual(float a, float b, float tolerance); 
void pushBack(DynamicArray *arr, mat4 element);
void freeDynamicArray(DynamicArray *arr);
ImageData* load_image(const char *path);
#endif
