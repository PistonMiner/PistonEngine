#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"

int main()
{
	using namespace PistonEngine;
	using namespace graphics;
	using namespace maths;

	Window window("PistonEngine", 960, 540);
	// glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


	GLfloat vertices[] =
	{
		0, 0, 0,
		8, 0, 0,
		0, 3, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0,
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));

	shader.setUniform4f("colorin", vec4(0.2f, 0.3f, 0.8f, 1.0f));

	//glProgramParameteri(shade GLenum("color"), (GLint) &vec4(4, 5, 6, 7));

	while (!window.closed())
	{
		vec2 mousepos = window.getMousePosition();
		shader.setUniform2f("light_pos", vec2(mousepos.x * 16.0f / window.getSize().x, 9.0f - mousepos.y * 9.0f / window.getSize().y));
		window.clear();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		window.update();
	}

	return 0;
}