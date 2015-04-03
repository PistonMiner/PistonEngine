#pragma once

#include <GL/glew.h>

namespace PistonEngine { namespace graphics {
		
	class Buffer
	{
	private:
		GLuint m_BufferID;
		GLuint m_ComponentCount;
	public:
		Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
		~Buffer();

		inline GLuint getComponentCount() const { return m_ComponentCount; }
		void bind() const;
		void unbind() const;
			
	};
} }