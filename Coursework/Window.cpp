#include <iostream>
#include "Window.h"


namespace Aerodynamics {
	namespace UI {


		Window::Window() {
			x = y = 0;
			width = funConsole::GetCols();
			height = funConsole::GetRows();
			SetBgColor(Black);
			SetColor(White);
			SetBorderColor(LightBlue);

			buf[0] = 201;
			buf[1] = 205;
			buf[2] = 187;
			buf[3] = 186;
			buf[4] = 200;
			buf[5] = 188;

		}

		Window& Window::HCenter() {
			x = (funConsole::GetCols() - width) / 2;
			return *this;
		}
		Window& Window::VCenter() {
			y = (funConsole::GetRows() - height) / 2;
			return *this;
		}

		Window& Window::SetColor(int c) {
			color = c;
			return *this;
		}

		Window& Window::SetBgColor(int c) {
			bgColor = c;
			return *this;
		}

		Window& Window::SetBorderColor(int c) {
			borderColor = c;
			return *this;
		}

		Window& Window::Move(int _x, int _y) {
			if (_x + width <= funConsole::GetCols()) {
				x = _x;
			}
			else {
				width -= (_x - x);
				x = _x;
			}

			if (_y + height <= funConsole::GetRows()) {
				y = _y;
			}
			else {
				height -= (_y - y);
				y = _y;
			}
			return *this;
		}

		Window& Window::SetWidth(int w) {
			if (w >= 3 && x + w <= funConsole::GetCols()) {
				width = w;
			}
			return *this;
		}

		Window& Window::SetHeight(int h) {
			if (h >= 3 && y + h <= funConsole::GetRows()) {
				height = h;
			}
			return *this;
		}

		Window& Window::Write(int _x, int _y, const char* str) {
			if (_x >= GetClientWidth() || _y >= GetClientHeight()) {
				return *this;
			}
			funConsole::GotoXY(x + _x + 1, y + _y + 1);
			int l = 1;
			int ix = 0;
			for (int i = 0; str[i]; i++) {
				if (_x + i - (l - 1) * i >= GetClientWidth()) {
					funConsole::GotoXY(x + _x + 1, y + _y + l + 1);
					l++;
					ix = 0;
				}
				if (str[i] == '\n') {
					if (ix < GetClientWidth()) {
						for (int j = 0; ix + j < GetClientWidth(); j++) {
							std::cout << " ";
						}
					}
					funConsole::GotoXY(x + _x + 1, y + _y + l + 1);
					l++;
					ix = 0;
					continue;
				}
				setlocale(0, "ukr");
				std::cout << str[i];
				if (!str[i + 1]) {
					setlocale(0, "en");
					if (ix < GetClientWidth()) {
						for (int j = 0; ix + j < GetClientWidth() - 1; j++) {
							std::cout << " ";
						}
					}
					ix = 0;
				}

				ix++;
			}
			return *this;
		}
		FunctionMenu& FunctionMenu::Write(int _x, int _y, const char* str, bool isTitle = 0) {
			if (_x >= GetClientWidth() || _y >= GetClientHeight()) {
				return *this;
			}
			funConsole::GotoXY(x + _x + 1, y + _y + 1);
			int l = 1;
			int ix = 0;
			for (int i = 0; str[i]; i++) {
				if (_x + i - (l - 1) * i >= GetClientWidth()) {
					funConsole::GotoXY(x + _x + 1, y + _y + l + 1);
					l++;
					ix = 0;
				}
				if (str[i] == '\n') {
					if (ix < GetClientWidth()) {
						for (int j = 0; ix + j < GetClientWidth(); j++) {
							std::cout << " ";
						}
					}
					funConsole::GotoXY(x + _x + 1, y + _y + l + 1);
					l++;
					ix = 0;
					continue;
				}
				setlocale(0, "ukr");
				std::cout << str[i];
				if (!str[i + 1] && !isTitle) {
					setlocale(0, "en");
					if (ix < GetClientWidth()) {
						for (int j = 0; ix + j < GetClientWidth() - 1; j++) {
							std::cout << " ";
						}
					}
					ix = 0;
				}

				ix++;
			}
			return *this;
		}

		Window& Window::Show() {
			setlocale(0, ".850");
			funConsole::SetColor(borderColor, bgColor);
			funConsole::GotoXY(x, y);
			std::cout << buf[0];
			for (int j = 0; j < width - 2; j++) {
				std::cout << buf[1];
			}
			std::cout << buf[2];
			for (int i = 1; i < height - 1; i++) {
				funConsole::GotoXY(x, y + i);
				std::cout << buf[3];
				funConsole::GotoXY(x + width - 1, y + i);
				std::cout << buf[3];
			}
			funConsole::GotoXY(x, y + height - 1);
			std::cout << buf[4];
			for (int j = 0; j < width - 2; j++) {
				std::cout << buf[1];
			}
			std::cout << buf[5];
			funConsole::SetColor(color, bgColor);
			for (int i = 1; i < height - 1; i++) {
				funConsole::GotoXY(x + 1, y + i);
				for (int j = 0; j < width - 2; j++) {
					std::cout << " ";
				}
			}
			funConsole::GotoXY(x + 1, y + 1);
			Draw();
			return *this;
		}

		int Menu::Select() {
			if (GetCount() == 0) {
				active = -1;
				return active;
			}
			funConsole::ShowCaret(false);
			active = 0;
			first = 0;
			Show();
			while (1) {
				if (active > first + GetClientHeight() - 1) {
					first = active - GetClientHeight() + 1;
				}
				else if (active < first) {
					first = active;
				}

				for (int i = 0, j = first; i < GetClientHeight() && j < GetCount(); i++, j++) {
					if (j == active) {
						funConsole::SetColor(selectColor, selectBgColor);
						funConsole::GotoXY(x + 1, y + 1 + i);
					}
					else {
						funConsole::SetColor(color, bgColor);
					}
					DrawItem(i, j);
				}
				int key = _getch();
				if (key == 224) {
					key = _getch();
					if (key == 80 && active + 1 < GetCount()) { //down
						active++;
					}
					if (key == 72 && active > 0) { //down
						active--;
					}
					continue;
				}
				if (key == 27) {
					active = -1;
					break;
				}
				if (key == 13) {
					break;
				}

			}
			funConsole::ShowCaret(true);
			return active;
		}
		int ArrayMenu::Select() {
			if (GetCount() == 0) {
				active = -1;
				return active;
			}
			funConsole::ShowCaret(false);
			active = 0;
			first = 0;

			Show();
			while (1) {
				if (active > first + GetClientHeight() - 1) {
					first = active - GetClientHeight() + heightRow;
				}
				else if (active < first) {
					first = active;
				}

				for (int i = 0, j = first; i <= GetClientHeight() && j / 3 < GetCount(); i += heightRow, j += heightRow) {
					if (j == active) {
						funConsole::SetColor(selectColor, selectBgColor);
						funConsole::GotoXY(x + 1, y + 1 + i);
					}
					else {
						funConsole::SetColor(color, bgColor);

					}
					DrawItem(i, j / heightRow);
				}
				int key = _getch();
				if (key == 224) {
					key = _getch();
					if (key == 80 && active / heightRow + 1 < GetCount()) { //down
						active += heightRow;
					}
					if (key == 72 && active > 0) { //down
						active -= heightRow;
					}
					continue;
				}
				if (key == 27) {
					active = -1;
					break;
				}
				if (key == 13) {
					break;
				}

			}
			return active / heightRow;
		}
		int FunctionMenu::Select() {
			if (GetCount() == 0) {
				active = -1;
				return active;
			}
			funConsole::ShowCaret(false);
			active = 2;
			first = 0;
			height -= 2;
			Show();
			height += 2;
			while (1) {

				if (active > first + GetClientHeight() - 1) {
					first = active - GetClientHeight() + 1;
				}
				else if (active < first + 2) {
					first = active - 2;
				}
				for (int i = 0, j = first; i < GetClientHeight() && j < GetCount() + 2; i++, j++) {
					if (j == active) {
						funConsole::SetColor(selectColor, selectBgColor);
						funConsole::GotoXY(x + 1, y - 1 + i);
					}
					else {
						funConsole::GotoXY(x + 1, y - 1 + i);
						funConsole::SetColor(color, bgColor);
					}
					if (i != 1) {
						for (int k = 0; k < GetClientWidth(); k++) {
							std::cout << " ";
						}
					}
					if (!i) {
						int left = (GetClientWidth() - strlen(title)) / 2;
						Write(left, -2, (const char*)(title), 1);
					}
					if (j > 1 && i > 1) {
						DrawItem(i - 2, j - 2);
					}
				}

				int key = _getch();
				if (key == 224) {
					key = _getch();
					if (key == 80 && active / heightRow + 1 < GetCount() + 2) { //down
						active++;
					}
					if (key == 72 && active > 2) { //up
						active--;
					}
					continue;
				}
				if (key == 13) {
					break;
				}

			}
			active -= 2;
			getCountAction();
			funConsole::ShowCaret(true);
			return active;
		}
	}
}