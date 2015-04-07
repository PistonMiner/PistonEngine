#version 330 core

layout (location = 0) in vec4 i_position;
layout (location = 1) in vec2 i_uv;
layout (location = 2) in float i_tid;
layout (location = 3) in vec4 i_color;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

out DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} vs_out;

void main()
{
	gl_Position = pr_matrix * vw_matrix * ml_matrix * i_position;
	vs_out.position = ml_matrix * i_position;
	vs_out.uv = i_uv;
	vs_out.tid = i_tid;
	vs_out.color = i_color;
}