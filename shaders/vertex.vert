#version 450 core
layout (location = 0) in vec3 aPos;
uniform mat4 transformationMatrix;
uniform vec3 camera;
uniform float test;
void main()
{
	//idea: use the vertex id to lookup data directly from a texture
	gl_Position = transformationMatrix * vec4(aPos - camera, 1.0);
}