#pragma once

#include <GL/glew.h>

namespace PistonEngine { namespace graphics {

	class VertexBuffer
	{
	private:
		GLuint m_BufferID;
		GLuint m_ComponentCount;
	public:
		VertexBuffer(GLfloat* data, GLsizei count, GLuint componentCount);

		inline GLuint getComponentCount() const { return m_ComponentCount; }

		void bind() const;
		void unbind() const;

	};

} }