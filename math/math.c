#include "math.h"

void mat4_translate(mat4 matrix, vec3 in_vec)
{
    matrix.data[3] = in_vec.x;
    matrix.data[7] = in_vec.y;
    matrix.data[11] = in_vec.z;
}