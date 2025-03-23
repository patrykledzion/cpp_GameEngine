#pragma once
#include <iostream>
#include <Windows.h>
#include <functional>
#include <vector>
#include <gl/GL.h>
#include <gl/GLU.h>     
#include "Image.h"

namespace nWindow {

	struct ContextMenuOption {
		LPCWSTR value;
		bool isLast;
		int id;
	};

	class Window
	{
	private:
		int width;
		int height;
		char* title;
		static ATOM WINDOW_CLASS;
		HWND windowPtr;
		void InitWindowClass();
		void InitWindow();
		void InitGL();
		void HandleEvents();
	public:
		HDC hdc;
		static HMENU contextMenu;
		Window(const char* title, int width, int height);
		void Update();
		void Draw();
		HWND GetWindow() { return this->windowPtr; }
		using EventHandler = std::function<void(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)>;
		std::vector<EventHandler> lbClickHandle;
		std::vector<EventHandler> rbClickHandle;
		std::vector<EventHandler> contextMenuHandle;
		std::vector<EventHandler> mouseMoveHandle;
		std::vector<EventHandler> keyboardUpHandle;
		std::vector<EventHandler> keyboardDownHandle;
		std::vector<EventHandler> focusHandle;
		std::vector<EventHandler> unfocusHandle;
		std::vector<EventHandler> resizeHandle;
		static void CreateContextMenu(std::vector<struct ContextMenuOption> options, HWND hWnd);
		static void ShowMessageBox(LPCWSTR title, LPCWSTR message, UINT type);
		void OnResize(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		std::pair<int, int> GetSize() { return std::make_pair(this->width, this->height); }
		Image* OpenBMP(std::string filename);
	};
}
