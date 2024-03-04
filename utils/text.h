#ifndef TEXT_H
#define TEXT_H

typedef struct {
    unsigned int TextureID;
    int width;
    int rows;
    int left;
    int top;
    unsigned int Advance; 
} Character;

void init_text_lib();
void clean_text_lib();
#endif
