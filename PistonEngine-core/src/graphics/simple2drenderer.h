#pragma once

#include <deque>
#include "renderer2d.h"
#include "static_sprite.h"

#include "renderable2d.h" // need to include this 
						  // -> renderer2d.h:11

namespace PistonEngine { namespace graphics {

	class Simple2DRenderer : public Renderer2D
	{
	private:
		std::deque<const StaticSprite*> m_RenderQueue;
	public:
		void submit(const Renderable2D* renderable) override;
		void flush() override;
	};

} }