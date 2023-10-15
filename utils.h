#ifndef UTILS_H
#define UTILS_H

const char *loadFile(const char *filename);
float *mat4_vec4_mult(float matrix[16], float vec[4]);
void printMatrix(float matrix[16]);
float *mat4_mult(float matrix_a[16], float matrix_b[16]);

#endif
