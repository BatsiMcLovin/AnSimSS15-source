#version 330 core

in vec4 passPosition;
in vec3 passNormal;
in vec2 passUV;

uniform mat4 viewMatrix;
uniform vec3 color;
uniform int useColorTexture;
uniform sampler2D colorTexture;

out vec4 fragmentColor;

void main(){

    // diffuse color 
    vec3 diffuseColor;
    if (useColorTexture != 0)
    {
        diffuseColor = texture(colorTexture, passUV).rgb;
    }
    else
    {
        diffuseColor = color;
    }
    
    //compute the eye vector as the normalized negative vertex position in camera coordinates:
    vec3 eye = normalize(-passPosition.xyz);
    
    //compute the normalized reflection vector using GLSL's built-in reflect() function:
    vec3 reflection = normalize(reflect(eye, normalize(passNormal)));
    
    //varables used in the phong lighting model:
    float phi = max(dot(passNormal, eye), 0);
    float psi = max(dot(reflection, eye),0);

    diffuseColor = psi * vec3(1.0,1.0,1.0) + phi * diffuseColor;
    fragmentColor = vec4(diffuseColor, 1.0f);

}