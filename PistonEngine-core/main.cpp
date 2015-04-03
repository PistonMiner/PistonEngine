#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/renderer2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2d.h"

#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"

#include <time.h>

#define BATCH_RENDERER 1

int main()
{
	using namespace PistonEngine;
	using namespace graphics;
	using namespace maths;

	Window window("PistonEngine", 960, 540);
	// glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
//	shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
	
	
	std::vector<Renderable2D*> sprites;
	
	for (float y = 0; y < 9.0f; y += 0.05f)
	{
		for (float x = 0; x < 16.0f; x += 0.05f)
		{
#if BATCH_RENDERER
			sprites.push_back(new Sprite(x, y, 0.04f, 0.04f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
#else
			sprites.push_back(new StaticSprite(x, y, 0.04f, 0.04f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1), shader));
#endif
		}
	}

#if BATCH_RENDERER
	Sprite sprite(5, 5, 4, 4, maths::vec4(1, 0, 1, 1));
	Sprite sprite2(7, 1, 2, 3, maths::vec4(0.2f, 0, 1, 1));
	BatchRenderer2D renderer;

#else
	StaticSprite sprite(5, 5, 4, 4, maths::vec4(1, 0, 1, 1), shader);
	StaticSprite sprite2(7, 1, 2, 3, maths::vec4(0.2f, 0, 1, 1), shader);
	Simple2DRenderer renderer;
#endif
	//BatchRenderer2D batch;

	shader.setUniform4f("u_color", vec4(0.2f, 0.3f, 0.8f, 1.0f));

	while (!window.closed())
	{
		window.clear();
		vec2 mousepos = window.getMousePosition();
		shader.setUniform2f("u_light_pos", vec2(mousepos.x * 16.0f / window.getSize().x, 9.0f - mousepos.y * 9.0f / window.getSize().y));
#if BATCH_RENDERER
		renderer.begin();
#endif
		for (int i = 0; i < sprites.size(); i ++)
			renderer.submit(sprites[i]);
		//renderer.submit(&sprite);
		//renderer.submit(&sprite2);
#if BATCH_RENDERER
		renderer.end();
#endif
		renderer.flush();

		window.update();
	}

	return 0;
}