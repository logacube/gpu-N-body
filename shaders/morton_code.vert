#version 400 core
in vec2 position;
out vec2 uv;

void main()
{
    uv = (position + 1.0) / 2.0;
    //uv.x *= ratio;
    //uv.x -= (ratio -1.0) *0.5 ;
    //uv.y = 1.0-uv.y;
    gl_Position = vec4(position, 0.0, 1.0);
}