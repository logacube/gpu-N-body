#version 450 core
#extension GL_ARB_gpu_shader_int64 : enable

in vec2 uv;
out vec4 FragColor;
uniform usampler2D tex;
void main() 
{
	//dont know where to put this.
	//look into gl_fragDepth to manually write depths values
	uvec2 packed_value = texture(tex, uv).rg;
	uint64_t value = packUint2x32(packed_value.gr);//int64_t(packed_value.r) << 32 | int64_t(packed_value.y);
	double test = 1.0;//works!!!

	FragColor = vec4(vec3(float(value) * 5.42e-20), 1.0);//vec4(uv, 0.0, 1.0);
}