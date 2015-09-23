#version 330

in vec2 passUVCoord;

uniform sampler2D colortexture;

out vec4 fragmentColor;

void main() {
    fragmentColor = vec4(texture(colortexture, passUVCoord).rgb,1.0);;//texture(colortexture, passUVCoord);
}