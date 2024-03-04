#include "logger.h"
#include <GL/glew.h>
#include "text.h"
#include "ft2build.h"
#include FT_FREETYPE_H

FT_Library ft;
FT_Face face;

Character *symbols;


void init_text_lib(){
    if (FT_Init_FreeType(&ft))
    {
        error("Could not load Freetype");
        return -1;
    }
    if (FT_New_Face(ft, "resources/fonts/DroidSansFallbackFull.ttf", 0, &face)){
        error("Failed to load font");
        return -1;
    }

    FT_Set_Pixel_Sizes(face, 0, 40);


    init_symbols();
}

void init_symbols(){

 symbols = (Character *)malloc(128 * sizeof(Character));
glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c =0; c<128; c++){

    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
        error("Failed to load glyph");
        return -1;
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer
    );
    // set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      
    Character character = {
        1,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        face->glyph->bitmap_left,
        face->glyph->bitmap_top,
        face->glyph->advance.x
       };
       symbols[c] = character; 
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void clean_text_lib(){

    free(symbols);

}
