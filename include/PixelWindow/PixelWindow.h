#pragma once

#include "Window.h"

namespace sr {

	class PixelWindow : public Window {
	private:
		int width = 0;
		int height = 0;
		int* pixelBuffer = nullptr;

		// Geometry
		GLuint vertVbo = 0;
		GLuint texVbo = 0;
		GLuint vao = 0;

		// Shaders
		GLuint vs = 0;
		GLuint fs = 0;
		GLuint shader = 0;

		// Texture
		GLuint textureId = 0;

		// Pbos
		GLuint pbos[2]{ 0 };
		int pboIndex = 0;

	public:
		PixelWindow(int width, int height, const char* title);

		void setBackgroundColor(int color);
		void setPixel(int x, int y, int color);
		void beginFrame();
		void endFrame();

		int getWidth() const noexcept;
		int getHeight() const noexcept;
	};

}
