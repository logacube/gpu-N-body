#version 330 core
out vec4 FragColor;
in float scale;

void main() 
{
	float brightness_control = 2.0;
	FragColor = mix(vec4(0.6, 0.2, 0.0125, 0.2 * brightness_control), vec4(0.1, 0.3, 0.6, 0.2 * brightness_control), clamp(40.0 * scale, 0.0, 1.0));
}