#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 offset;

layout(std430, binding = 0) buffer instanceBuffer
{
    vec4 centers[];
};
uniform mat4 transformationMatrix;
uniform vec3 camera;
uniform float test;
out float scale;
void main()
{
	scale = centers[gl_InstanceID].w;
	//idea: use the vertex id to lookup data directly from a texture
	gl_Position = transformationMatrix * vec4(aPos * centers[gl_InstanceID].w + centers[gl_InstanceID].xyz - camera, 1.0);
}