#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/utils/timer.h"

#include "src/graphics/renderer2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2d.h"

#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"

#include "src/graphics/layers/tilelayer.h"

#include "src/graphics/layers/group.h"

#include "src/graphics/texture.h"

#define BATCH_RENDERER 1
#define TEST_50K_SPRITES 0

int main()
{
	using namespace PistonEngine;
	using namespace graphics;
	using namespace maths;
	Window window("PistonEngine", 960, 540);

	// glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	shader.enable();

	//shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
	//shader2.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	TileLayer layer(&shader);

	Texture* textures[] = 
	{
		new Texture("test.png"),
		new Texture("test2.png"),
		new Texture("test3.png")
	};

	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{
			layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			if (rand() % 4 == 0)
				layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			else
				layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
		}
	}

	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);
	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	//system("PAUSE");
	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	while (!window.closed())
	{
		window.clear();
		maths::vec2 m = window.getMousePosition();

		shader.enable();
		shader.setUniform2f("u_light_pos", vec2((float)(m.x * 32.0f / 960.0f - 16.0f), (float)(9.0f - m.y * 18.0f / 540.0f)));
		//shader.setUniform2f("u_light_pos", vec2(-8, -3));
		shader.enable();
		layer.render();

		window.update();
		
		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d FPS\n", frames);
			frames = 0;
		}
	}
	return 0;
}