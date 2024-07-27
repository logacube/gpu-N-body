#version 450 core
#extension GL_ARB_gpu_shader_int64 : enable

in vec2 uv;
out uvec2 FragColor;
uniform sampler2D tex;
uint64_t morton_code(float x) {
	uint64_t x_ = uint64_t(x) & 0x00000000001fffff;
	x_ = (x_ | x_ << 32) & 0x1f00000000fffful;
    x_ = (x_ | x_ << 16) & 0x1f0000ff0000fful;
    x_ = (x_ | x_ << 8) & 0x100f00f00f00f00ful;
    x_ = (x_ | x_ << 4) & 0x10c30c30c30c30c3ul;
    x_ = (x_ | x_ << 2) & 0x1249249249249249ul;
	return x_;
}
void main() 
{
	//get point position
	vec3 point_position = texture(tex, uv).xyz;
	
	//ensure point position is in the range of an unsigned integer
	//assumes that points are in the range of -0.5 to 0.5
	point_position = 2097151.0 * (point_position + (vec3(0.5)));

	//find morton code of each component;
	uint64_t morton_x = morton_code(point_position.x);
	uint64_t morton_y = morton_code(point_position.y);
	uint64_t morton_z = morton_code(point_position.z);
	
	//combine to find nearest z-index of the point
	uint64_t z_index = morton_x * 4 + morton_y * 2 + morton_z;

	//split the index into two 32 bit unsigned integers so that they can be stored in a texture
	uvec2 z_split = unpackUint2x32(z_index);


	FragColor = z_split;
}