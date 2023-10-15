#ifndef UTILS_H
#define UTILS_H

const char *loadFile(const char *filename);
void mat4_identity(float matrix[16]);
void mat4_scale(float matrix[16], float scale);
float *mat4_vec4_mult(float matrix[16], float vec[4]);
void printMatrix(float matrix[16]);
float *mat4_mult(float matrix_a[16], float matrix_b[16]);
void set_equal(float matrixA[16], float matrixB[16]);

#endif
