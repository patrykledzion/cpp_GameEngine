#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>   
#include "Image.h"

namespace nWindow {

	class Window;

	typedef struct {
		float r;
		float g;
		float b;
		float a;
	} Color;

	typedef struct {
		float x;
		float y;
	} Vector2;

	typedef struct {
		float x;
		float y;
		float z;
	} Vector3;

	typedef struct{
		Vector3 v1;
		Vector3 v2;
		Vector3 v3;
		Vector3 v4;
	} Rectangle;

	typedef struct {
		GLuint tex;
		int width;
		int height;
	} Texture;

	class Drawing
	{
	public:
		static void Begin();
		static void DrawRectangle(Vector3* pos, Vector3 *size, Color* color);
		static void DrawRectangle(Vector3* pos, Vector3 *size, Color* color, Texture* texture);
		static void DrawRectangle(Vector3* pos, Vector3 *size, Color* color, Texture* texture, Rectangle chunk);
		static void DrawRectangle(Rectangle* rectangle, Color* color);
		static void DrawRectangle(Rectangle* rectangle, Color* color, Texture* texture);
		static void DrawRectangle(Rectangle* rectangle, Color* color, Texture* texture, Rectangle chunk);
		static Texture* LoadTexture(nWindow::Image* image);
		static void End(nWindow::Window* window);
	};
}
