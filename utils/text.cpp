#include "text.h"
#include "logger.h"
#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <stdexcept>  // Include the stdexcept header for std::runtime_error

static TextLib* textLibInstance = nullptr;

void init_text_lib() {
    if (textLibInstance == nullptr) {
        textLibInstance = new TextLib();
    }
}

void clean_text_lib() {
    delete textLibInstance;
    textLibInstance = nullptr;
}

TextLib::TextLib() : symbols(128) {
    if (FT_Init_FreeType(&ft)) {
        error("Could not load Freetype");
        throw std::runtime_error("Could not load Freetype");
    }
    if (FT_New_Face(ft, "resources/fonts/DroidSansFallbackFull.ttf", 0, &face)) {
        error("Failed to load font");
        throw std::runtime_error("Failed to load font");
    }

    FT_Set_Pixel_Sizes(face, 0, 40);
    init_symbols();
}

TextLib::~TextLib() {
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextLib::init_symbols() {
    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            error("Failed to load Glyph");
            continue;
        }
        GLuint texture;
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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Character character = {
            texture,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            face->glyph->bitmap_left,
            face->glyph->bitmap_top,
            face->glyph->advance.x
        };
        symbols[c] = character;
    }
}