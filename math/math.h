#ifndef MATH_H
#define MATH_H

typedef struct Vec3 {
    float x;
    float y;
    float z;
} vec3;

typedef struct Mat4 {
    float data[16];
} mat4;

void mat4_translate(mat4 matrix, vec3 in_vec);

#endif
