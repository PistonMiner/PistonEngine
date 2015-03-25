#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 colorin;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

out vec4 pos;
out vec4 col;

void main()
{
	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
	pos = ml_matrix * position;
	col = colorin;
}