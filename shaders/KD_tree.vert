#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 offset;

struct node {
    vec3 minimum;
    int child1;
    vec3 maximum;
    int child2;
    vec4 COM;//4th component is mass
};
layout(std430, binding = 0) buffer nodeBuffer
{
    node KD_tree[];
};
uniform mat4 transformationMatrix;
uniform vec3 camera;
uniform float test;
out float scale;
void main()
{
    node this_node = KD_tree[gl_InstanceID];
	vec3 center = 0.5 * (this_node.minimum + this_node.maximum);
    vec3 scale3 = (this_node.maximum - this_node.minimum);
    scale = 1.0 * (scale3.x + scale3.y + scale3.z) / 3.0;
	//idea: use the vertex id to lookup data directly from a texture
	gl_Position = transformationMatrix * vec4(aPos * scale3 + center - camera, 1.0);
}