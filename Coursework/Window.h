#pragma once
#include <conio.h>
#include "String.h"
#include "Array.h"
#include "fun_console.h"
#include <functional>
#include <vector>
#include <string>

namespace Aerodynamics {
	namespace UI {
		class Window
		{
		protected:
			int x, y, width, height;
			int color, bgColor, borderColor;
			char buf[6];
		public:
			Window();
			Window& Move(int _x, int _y);
			int GetColor() { return color; }
			int GetBgColor() { return bgColor; }
			int GetBorderColor() { return borderColor; }
			int GetX() { return x; }
			int GetY() { return y; }
			int GetWidth() { return width; }
			int GetClientWidth() { return width - 2; }
			int GetHeight() { return height; }
			int GetClientHeight() { return height - 2; }
			Window& HCenter();
			Window& VCenter();
			Window& SetColor(int c);
			Window& SetBorderColor(int c);
			Window& SetBgColor(int c);
			Window& SetWidth(int w);
			virtual Window& SetHeight(int h);
			virtual Window& Show();
			Window& Write(int, int, const char*);
			virtual void Draw() {}
		};


		class Message : public Window {
		protected:
			Aerodynamics::Data::String text;
		public:
			Message(Aerodynamics::Data::String t) :text(t) {}
			void Draw() { std::cout << text; _getch(); }
		};



		class Menu : public Window {
		protected:
			int active;
			int selectColor, selectBgColor;
			int first;
		public:
			Menu() : Window() {
				active = -1;
				selectColor = Blue;
				selectBgColor = White;
			}
			int GetSelect() { return active; }
			virtual int Select();
			virtual int GetCount() = 0;
			virtual void DrawItem(int row, int index) = 0;
			Menu& setSelectColor(int c) {
				selectColor = c;
				return *this;
			}
			Menu& setSelectBgColor(int c) {
				selectBgColor = c;
				return *this;
			}
		};

		class ArrayMenu : public Menu {
		protected:
			Aerodynamics::Data::Array<Aerodynamics::Data::String> items;
			unsigned int heightRow;
		public:
			ArrayMenu() : Menu(), heightRow(1) {

			}
			void Add(const char* m) { items.Add(m); }
			int GetCount() {
				return items.GetCount();
			}
			void DrawItem(int row, int index) {
				Write(0, row, items[index]);
			}
			ArrayMenu& setHeightRow(unsigned int h) {
				if (h && h <= GetClientHeight()) {
					heightRow = h;
				}
				return *this;
			}
			int Select();

		};

		class MenuItem {
		public:
			std::string label;
			std::function<void()> action;
			MenuItem(const std::string& label, const std::function<void()>& action)
				: label(label), action(action) {}
		};

		class FunctionMenu : public ArrayMenu {
			std::vector<MenuItem> items;
			char buf[2];
			const char* title;
		public:
			FunctionMenu(const char* title = "title", bool addExit = 0) {
				buf[0] = 204;
				buf[1] = 185;
				this->title = title;
				if (addExit) {
					addItem("Вихiд", []() { funConsole::SetColor(White, Black); funConsole::cls();  });
				}
			};
			FunctionMenu& SetHeight(int h) {
				h += 2;
				Window::SetHeight(h);
				return *this;
			}
			void addItem(const std::string& label, const std::function<void()>& action) {
				items.emplace_back(label, action);
				Add(label.c_str());
			}
			void addItem(const char* label, const std::function<void()>& action) {
				items.emplace_back(label, action);
				Add(label);
			}
			void getCountAction() {
				items[active].action();
			}
			int Select();
			FunctionMenu& Show() {
				Window::Show();
				funConsole::SetColor(borderColor, bgColor);
				funConsole::GotoXY(x, y - 2);
				std::cout << Window::buf[0];
				for (int j = 0; j < width - 2; j++) {
					std::cout << Window::buf[1];
				}
				std::cout << Window::buf[2];
				funConsole::GotoXY(x, y - 1);
				std::cout << Window::buf[3];

				funConsole::GotoXY(x + width - 1, y - 1);
				std::cout << Window::buf[3];
				funConsole::GotoXY(x, y);
				std::cout << buf[0];
				funConsole::GotoXY(x + width - 1, y);
				std::cout << buf[1];
				return *this;
			};
			FunctionMenu& Write(int, int, const char*, bool);
		};


		class ColorsMenu : public Menu {
		public:
			ColorsMenu() : Menu() {
			}

			int GetCount() { return 16; }

			void DrawItem(int row, int index) {
				if (index == active) Write(0, row, ">");
				funConsole::SetColor(index, index);
				for (int i = 1; i < GetClientWidth(); i++) {
					Write(i, row, " ");
				}
			}

		};
	}
}

