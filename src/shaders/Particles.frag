#version 430 core
layout (location = 0) out vec4 color;						// This is derived from the age of the particle read
													// by the vertex shader
in float intensity;
void main(void){
	// Blend between red-hot and cool-blue based on the
	// age of the particle.
	color = mix(vec4(0.0f, 0.2f, 1.0f, 1.0f),
			vec4(0.2f, 0.05f, 0.0f, 1.0f),
			intensity);
}