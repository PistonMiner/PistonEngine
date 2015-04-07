#version 330 core

layout (location = 0) out vec4 o_color;

uniform vec2 u_light_pos;
uniform vec4 u_color;

in DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} fs_in;

uniform sampler2D textures[32];

void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - u_light_pos);
	
	vec4 texColor = fs_in.color * intensity;
	if (fs_in.tid > 0.0)
	{
		int tid = int(fs_in.tid - 0.5);
		texColor = texture(textures[tid], fs_in.uv);
	}
	o_color = texColor * intensity;
}