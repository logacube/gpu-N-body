#version 450 core
#extension GL_ARB_gpu_shader_int64 : enable
in vec2 uv;
out uvec2 FragColor;
uniform ivec2 resolution;
uniform int stride;
uniform usampler2D DATA;
void main() 
{
	int idx = (int(gl_FragCoord.x - 0.5)) + (int(gl_FragCoord.y - 0.5)) * resolution.x;//(resolution.x * uv.x + uv.y * resolution.x * resolution.y);
	int partner = idx - (idx % stride) + ((idx % stride) + (stride / 2)) % (stride);//idx + stride - 1 - 2 * (idx % stride);
	
	uvec4 this_texel = texelFetch(DATA, ivec2(int(gl_FragCoord.x - 0.5), int(gl_FragCoord.y - 0.5)), 0);//texture(DATA, partner_coord).r;// * 0.01 + vec4(vec3(float(long_input) * 0.01), 1.0);;
	uvec4 partner_texel = texelFetch(DATA, ivec2(partner % resolution.y, partner / resolution), 0);//texture(DATA, partner_coord).r;// * 0.01 + vec4(vec3(float(long_input) * 0.01), 1.0);;

	if ((partner_texel.r > this_texel.r) || ((partner_texel.r == this_texel.r) && (partner_texel.g > this_texel.g))) {//(partner_val > this_val) {
		if (idx > partner) {
			FragColor = partner_texel.xy;
		}
		else {
			FragColor = this_texel.xy;
		}
	}
	else {
		if (idx > partner) {
			FragColor = this_texel.xy;
		}
		else {
			FragColor = partner_texel.xy;
		}
	}
}