#pragma once

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"

#include "renderer2d.h"
#include "texture.h"

#include "../maths/maths.h"
#include "shader.h"

namespace PistonEngine { namespace graphics {

	struct VertexData
	{
		maths::vec3 vertex;
		maths::vec2 uv;
		float tid;
		unsigned int color;
	};

	class Renderable2D
	{
	protected:
		maths::vec3 m_Position;
		maths::vec2 m_Size;
		maths::vec4 m_Color;
		std::vector<maths::vec2> m_UV;
		Texture* m_Texture;
	protected:
		Renderable2D() { setUVDefaults(); }
	public:
		Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color)
			: m_Position(position), m_Size(size), m_Color(color) { setUVDefaults(); }

		virtual ~Renderable2D() {}

		virtual void submit(Renderer2D * renderer) const
		{
			renderer->submit(this);
		}

		inline const maths::vec3& getPosition() const { return m_Position; }
		inline const maths::vec2& getSize() const { return m_Size; }
		inline const maths::vec4& getColor() const { return m_Color; }
		inline const std::vector<maths::vec2>& getUV() const { return m_UV; }

		inline const GLuint getTID() const { return m_Texture == nullptr ? 0 : m_Texture->getID(); }
	private:
		void setUVDefaults()
		{
			m_UV.push_back(maths::vec2(0, 0));
			m_UV.push_back(maths::vec2(0, 1));
			m_UV.push_back(maths::vec2(1, 1));
			m_UV.push_back(maths::vec2(1, 0));
		}
	};

} }