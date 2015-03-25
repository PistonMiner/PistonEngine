#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 light_pos;
uniform vec4 u_color;

in vec4 pos;
in vec4 col;

void main()
{
	float intensity = 1.0 / length(pos.xy - light_pos);
	if (col.a != 0)
		color = col * intensity;
	else
		color = u_color * intensity;
}