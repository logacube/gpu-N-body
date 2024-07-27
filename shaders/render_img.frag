#version 450 core
#extension  GL_ARB_shader_atomic_counter_ops: enable
in vec2 uv;
out vec4 FragColor;
uniform sampler2D tex;
layout(std430, binding = 0) buffer layoutName
{
    int data_SSBO[];
};
void main() 
{
	//uint g = atomicExchange(data_SSBO[0], 121);
	FragColor = texture(tex, uv);// + vec4(float(data_SSBO[1]) * 0.1, 0.0, 0.0, 1.0);

}