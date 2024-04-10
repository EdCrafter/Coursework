#include "Input.h"
#include <iostream>

using namespace Aerodynamics::UI::funConsole;
	bool InputV2::process(int mode,bool clear) {

		int k = 0;
		int onceDot = 0;
		int onceE = 0;
		int oncePlus = 0;
		int twoMinus = 0;

		bool modeContinue;
		while (k < lengthMax) {
			modeContinue = 0;
			
			int key = _getch();
			if (key == 27) { //Esc
				return false;
			}
			if (key == 8 && k>0) {
				GotoXY(x+k-1, y);
				std::cout << " ";
				GotoXY(x + k - 1, y);
				k--;
				if (str[k] == '.') {
					onceDot = 0;
				}
				if (str[k] == 'e') {
					onceE = 0;
				}
				if (str[k] == '+') {
					oncePlus = 0;
				}
				str[k] = 0;
				continue;
			}
			if (key == 13) {//Enter
				if (k == 0) {
					continue;
				}
				if (clear) {
					GotoXY(x, y);
					for (int i = 0; i < k; i++) std::cout << " ";
				}
				break;
			}
			if (key == 32) continue;//Space
			switch (mode)
			{
			case 1:
				if (!((key >= '0' && key <= '9') || key == '.' || 
					(key == 'e' && k>0) || (key == '+' && k>1 && str[k-1]=='e'))) {
					continue;
				}
				if (key >= '0' && key <= '9' && k>0 && str[k - 1] == 'e') {
					continue;
				}
				if (key == '.') {
					if (onceDot||onceE||oncePlus) {
						continue;
					}
					onceDot = 1;
				}
				if (key == 'e') {
					if (onceE) {
						continue;
					}
					onceE = 1;
				}
				if (key == '+') {
					if (oncePlus) {
						continue;
					}
					oncePlus = 1;
				}
				break;
			case 2:
				if (!((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') ||
					(key >= 'à' && key <= 'ÿ') || (key >= 'À' && key <= 'ß')
					)) { continue; }
				break;
			case 3:
				if (!(key >= '0' && key <= '9')) { continue; }
				break;
			default:
				break;
			};
			str[k] = key;
			k++;
			str[k] = 0; 
			GotoXY(x, y);
			std::cout << str;
			
		}
		lengthOrigin = k;
		

		return true;
	}

