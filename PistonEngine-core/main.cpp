#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"
#include "src/maths/maths.h"

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
		0, 3, 0,
		8, 3, 0,
		8, 0, 0
	};
	GLfloat vertices2[] =
	{
		0, 0, 0,
		0, 4, 0,
		4, 4, 0,
		4, 0, 0
	};
	GLushort indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};
	GLfloat colors[] =
	{
		1, 0, 1, 1,
		1, 0, 0, 1,
		0, 1, 0, 1,
		0, 0, 1, 1
	};
	GLfloat black[] =
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	};

	IndexBuffer ibo(indices, 2 * 3);

	VertexArray vao, rect;
	vao.addBuffer(new VertexBuffer(vertices, 4 * 3, 3), 0);
	vao.addBuffer(new VertexBuffer(black, 4 * 4, 4), 1);
	rect.addBuffer(new VertexBuffer(vertices2, 4 * 3, 3), 0);
	rect.addBuffer(new VertexBuffer(colors, 4 * 4, 4), 1);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);

	shader.setUniform4f("u_color", vec4(0.2f, 0.3f, 0.8f, 1.0f));

	while (!window.closed())
	{
		window.clear();
		vec2 mousepos = window.getMousePosition();
		shader.setUniform2f("light_pos", vec2(mousepos.x * 16.0f / window.getSize().x, 9.0f - mousepos.y * 9.0f / window.getSize().y));

		vao.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

		rect.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(0, 0, 0)));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		window.update();
	}

	return 0;
}