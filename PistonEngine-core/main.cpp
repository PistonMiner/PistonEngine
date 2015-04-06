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
#include "src/utils/timer.h"

#include "src/graphics/layers/tilelayer.h"

#include "src/graphics/layers/group.h"

#include <time.h>

#define BATCH_RENDERER 1
#define TEST_50K_SPRITES 0

int main()
{
	using namespace PistonEngine;
	using namespace graphics;
	using namespace maths;
	Window window("PistonEngine", 960, 540);

	// glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	
	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader* s2 = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	Shader& shader2 = *s2;
	shader.enable();
	shader2.enable();

	//shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
	//shader2.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	TileLayer layer(&shader);
	
#if TEST_50K_SPRITES
	for (float y = -9.0f; y < 9.0f; y += 0.1)
	{
		for (float x = -16.0f; x < 16.0f; x += 0.1)
		{
			layer.add(new Sprite(x, y, 0.09f, 0.09f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}
#else

	Group* group = new Group(mat4::translation(maths::vec3(-15.0f, 5.0f, 0.0f)));
	group->add(new Sprite(0, 0, 6, 3, maths::vec4(1, 1, 1, 1)));

	Group* button = new Group(mat4::translation(maths::vec3(0.5f, 0.5f, 0.0f)));
	button->add(new Sprite(0, 0, 5.0f, 2.0f, maths::vec4(1, 0, 1, 1)));
	button->add(new Sprite(0.5f, 0.5f, 3.0f, 1.0f, maths::vec4(0.2f, 0.3, 0.8f, 1)));
	group->add(button);

	layer.add(group);

#endif


	TileLayer layer2(&shader2);
	layer2.add(new Sprite(-2, -2, 4, 4, maths::vec4(1, 0, 1, 1)));

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
		
		//shader2.enable();
		//shader2.setUniform2f("u_light_pos", vec2((float)(m.x * 32.0f / 960.0f - 16.0f), (float)(9.0f - m.y * 18.0f / 540.0f)));
		
		layer.render();
		//layer2.render();
		
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