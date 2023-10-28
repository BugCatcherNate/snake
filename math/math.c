#include "math.h"
#include <stdio.h>

void mat4_translate(mat4 *matrix, vec3 in_vec)
{
    matrix->data[3] = in_vec.x;
    matrix->data[7] = in_vec.y;
    matrix->data[11] = in_vec.z;
}

void mat4_scale(mat4 *matrix, float scale)
{

    matrix->data[0] *= scale;
    matrix->data[5] *= scale;
    matrix->data[10] *= scale;
}

void set_equal(mat4 *matrixA, mat4 matrixB)
{
    for (int i = 0; i < 16; i++)
    {
        matrixA->data[i] = matrixB.data[i];
    }
}

void mat4_identity(mat4 *matrix)
{
    for (int i = 0; i < 16; i++)
    {
        matrix->data[i] = (i % 5 == 0) ? 1.0f : 0.0f;
    }
}

void print_matrix(mat4 *matrix)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%f\t", matrix->data[i * 4 + j]);
        }
        printf("\n");
    }

    printf("\n");
}
