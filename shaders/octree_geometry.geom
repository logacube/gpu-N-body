#version 450 core

layout (points) in;
layout (line_strip, max_vertices = 8) out;

uniform mat4 transformationMatrix;
uniform vec3 camera;
void main() 
{
    float size = 0.04;
    vec4 pos = transformationMatrix * (gl_in[0].gl_Position - vec4(camera, 0.0)  + vec4(-size, 0.0, 0.0, 1.0));
    gl_Position = vec4(0.5 * pos.x / pos.w, 0.5 * pos.y / pos.w, pos.z, pos.w);
    EmitVertex();

    pos = transformationMatrix * (gl_in[0].gl_Position - vec4(camera, 0.0)  + vec4(size, 0.0, 0.0, 1.0));
    gl_Position = vec4( 0.5 * pos.x / pos.w, 0.5 * pos.y / pos.w, pos.z, pos.w);
    EmitVertex();

    EndPrimitive();

}