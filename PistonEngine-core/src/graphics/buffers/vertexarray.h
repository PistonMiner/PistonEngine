#pragma once

#include <GL/glew.h>
#include <vector>

#include "vertexbuffer.h"

namespace PistonEngine { namespace graphics {

	class VertexArray
	{
	private:
		GLuint m_ArrayID;
		std::vector<VertexBuffer*> m_Buffers;
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(VertexBuffer* buffer, GLuint index);
		void bind() const;
		void unbind() const;
	};

} }