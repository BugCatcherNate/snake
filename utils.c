#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

const char *loadFile(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return NULL; // Return NULL to indicate an error
    }

    // Find the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file content
    char *file_content = (char *)malloc(file_size + 1);

    if (file_content == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(file);
        return NULL; // Return NULL to indicate an error
    }

    // Read the file content
    size_t bytes_read = fread(file_content, 1, file_size, file);
    file_content[bytes_read] = '\0'; // Null-terminate the string

    fclose(file);
    return file_content; // Return the file content as a string
}

float *mat4_vec4_mult(float matrix[16], float vec[4])
{

    float res[4] = {0.0, 0.0, 0.0, 0.0};

    res[0] = matrix[0] * vec[0] + matrix[1] * vec[0] + matrix[2] * vec[0] + matrix[3] * vec[0];
    res[1] = matrix[4] * vec[1] + matrix[5] * vec[1] + matrix[6] * vec[1] + matrix[7] * vec[1];
    res[2] = matrix[8] * vec[2] + matrix[9] * vec[2] + matrix[10] * vec[2] + matrix[11] * vec[2];
    res[3] = matrix[12] * vec[3] + matrix[13] * vec[3] + matrix[14] * vec[3] + matrix[15] * vec[3];

    return res;
}


float *mat4_mult(float matrix_a[16], float matrix_b[16])
{

    float *result = (float *)malloc(16 * sizeof(float)); // Allocate memory for the result matrix
                                                         //
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result[i * 4 + j] = 0;
            for (int k = 0; k < 4; k++)
            {
                result[i * 4 + j] += matrix_a[i * 4 + k] * matrix_b[k * 4 + j];
            }
        }
    }

    return result;
}

void printMatrix(float matrix[16])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%f\t", matrix[i * 4 + j]);
        }
        printf("\n");
    }

    printf("\n");
}
