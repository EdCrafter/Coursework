#pragma once
#include <iostream>
#include <conio.h>
#include "fun_console.h"

	class InputV2 {
		int x, y;
		size_t lengthMax;
		size_t lengthOrigin;
		char* str;
	public:
		InputV2(size_t len, int x, int y ) {
			lengthMax = len; 
			str = new char[lengthMax+1]; 
			str[0] = 0;
			this->x = x;
			this->y = y;
			lengthOrigin = 0;
		}

		~InputV2() {
			delete str;
		}

		void Move(int _x, int _y) { x = _x; y = _y; }
		bool process(int, bool clear = true);
		InputV2& setLength(int len) {
			if (len > 0) {
				lengthMax = len;
				delete str;
				str = new char[lengthMax + 1];
			}
			return *this;
		}
		char* get() { return str; }
		size_t getLength() { return lengthOrigin+1; }

	};

