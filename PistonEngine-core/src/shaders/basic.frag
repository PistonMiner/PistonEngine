#version 330 core

layout (location = 0) out vec4 o_color;

uniform vec2 u_light_pos;
uniform vec4 u_color;

in DATA
{
	vec4 position;
	vec4 color;
} fs_in;

void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - u_light_pos);
	o_color = fs_in.color * intensity;
}