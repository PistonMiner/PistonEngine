#include "vertexbuffer.h"

namespace PistonEngine { namespace graphics {

	VertexBuffer::VertexBuffer(GLfloat* data, GLsizei count, GLuint componentCount)
		: m_ComponentCount(componentCount)
	{
		GLuint& vbo = m_BufferID;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

} }