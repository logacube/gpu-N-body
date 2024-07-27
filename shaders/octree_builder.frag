#version 450 core
#extension  GL_ARB_shader_atomic_counter_ops: enable

struct voxel {
	uint child;
	uint start_point;
	uint end_point;
};

in vec2 uv;
out vec4 FragColor;
uniform ivec2 resolution;
uniform sampler2D tex;
layout(binding = 0, offset = 0) uniform atomic_uint two;
layout(std430, binding = 3) buffer layoutName
{
    voxel data_SSBO[];
};
void main() 
{
	int idx = (int(gl_FragCoord.x - 0.5)) + (int(gl_FragCoord.y - 0.5)) * resolution.x;//(resolution.x * uv.x + uv.y * resolution.x * resolution.y);

	voxel node = data_SSBO[idx];

	//the end indices of the start and end points for each of the eight children.
	//all values are initialized as 0 that way empty nodes dont need to be touched.
	int bounds[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	//check if this node will have children:
	if (node.start_point == node.end_point) {
		//this is a leaf node with one child
		//note, that this could also be an empty node
		//empty nodes are designated by having 0 as both the start and end points
	}
	else {
		//find the location of the most significant bit:
		int MSB = findMSB(node.start_point ^ node.end_point);

		//half way point: (if the start and end point are right next to each other this will take on the value of the first index)
		uint midway_index = (node.start_point + node.end_point) / 2;

		//check if the mid way point satisfies the condition for being in the 

	}

	//placeholder value
	FragColor = vec4(1.0, 0.0, 0.0, 1.0);

}