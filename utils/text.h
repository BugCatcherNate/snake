#ifndef TEXT_H
#define TEXT_H

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <vector>
#include <string>

struct Character {
    GLuint TextureID;  // ID handle of the glyph texture
    int Width;         // Width of glyph
    int Height;        // Height of glyph
    int BearingX;      // Offset from baseline to left/top of glyph
    int BearingY;      // Offset from baseline to left/top of glyph
    int Advance;       // Offset to advance to next glyph
};

class TextLib {
public:
    TextLib();
    ~TextLib();

private:
    void init_symbols();  // Declare the init_symbols function

    FT_Library ft;
    FT_Face face;
    std::vector<Character> symbols;
};

#endif // TEXT_H