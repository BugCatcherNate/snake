#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 texCoord;
uniform mat4 model;

out vec2 TexCoord; 
void main()
{
    gl_Position = model * vec4(inPosition, 1.0);
    TexCoord = texCoord;
}
