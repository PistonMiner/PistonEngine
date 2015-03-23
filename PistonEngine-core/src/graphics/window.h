#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../maths/maths.h"

#define MAX_KEYS 1024
#define MAX_MOUSE_BUTTONS 32

namespace PistonEngine { namespace graphics {

	class Window
	{
		friend struct GLFWwindow;

	private:
		const char* m_Title;
		int m_Width, m_Height;
		GLFWwindow* m_Window;
		bool m_Closed;

		bool m_Keys[MAX_KEYS];
		bool m_MouseButtons[MAX_MOUSE_BUTTONS];
		double mx, my;
	public:
		Window(const char *title, int width, int height);
		~Window();
		void clear() const;
		void update();
		bool closed() const;

		//inline int getWidth() const { return m_Width; };
		//inline int getHeight() const { return m_Height; };
		inline maths::vec2 getSize() const { return maths::vec2(m_Width, m_Height); }

		bool isKeyPressed(unsigned int key) const;
		bool isMouseButtonPressed(unsigned int button) const;
		maths::vec2 getMousePosition() const;
		
	private:
		bool init();
		
		//Callbacks
		friend static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	};

} }