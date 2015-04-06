#pragma once

#include <GL/glew.h>
#include "../maths/maths.h"
//#include "renderable2d.h"

#include <vector>

namespace PistonEngine { namespace graphics {
	
	class Renderable2D; // declare this here to avoid recursive inclusion.
						// (renderer2d.h needs renderable2d.h and vice versa.)
						// unfortunately means we have to include renderable2d.h
						// in all implementations of Renderer2D

	class Renderer2D
	{
	protected:
		const maths::mat4* m_TransformationBack;
		std::vector<const maths::mat4> m_TransformationStack;
	protected:
		Renderer2D()
		{
			m_TransformationStack.push_back(maths::mat4::identity());
			m_TransformationBack = &m_TransformationStack.back(); // update cache
		}
	public:
		void push(const maths::mat4& matrix, bool override = false)
		{
			if (override)
				m_TransformationStack.push_back(matrix);
			else
				m_TransformationStack.push_back(m_TransformationStack.back() * matrix);
			
			m_TransformationBack = &m_TransformationStack.back(); // update cache
		}
		void pop()
		{
			if (m_TransformationStack.size() > 1)
				m_TransformationStack.pop_back();

			m_TransformationBack = &m_TransformationStack.back(); // update cache
		}

		virtual void begin() {};
		virtual void submit(const Renderable2D* renderable) = 0;
		virtual void end() {};
		virtual void flush() = 0;
	};

} }