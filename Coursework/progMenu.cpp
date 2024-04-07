#include "ProgMenu.h"

using namespace Aerodynamics::UI;

progMenu& progMenu::start()
{
	setlocale(0, "en");
	FunctionMenu myInterface("ГОЛОВНЕ МЕНЮ", 1);
	myInterface.SetHeight(9).SetWidth(30).HCenter().VCenter();
	myInterface.addItem("Меню крил", [this, &myInterface]() {
		this->wingMenu();
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("Меню повiтряних суден", [this, &myInterface]() {
		this->aircraftMenu();
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("", [&myInterface]() {myInterface.Select(); });
	myInterface.addItem("          __ | __", [&myInterface]() {myInterface.Select(); });
	myInterface.addItem("    --@--@--(_)--@--@-- ", [&myInterface]() {myInterface.Select(); });
	myInterface.addItem("      `` ``      `` `` ", [&myInterface]() {myInterface.Select(); });
		


	myInterface.Select();
	return *this;
}

progMenu& progMenu::wingMenu()
{
	FunctionMenu myInterface("МЕНЮ КРИЛ", 1);
	myInterface.SetHeight(9).SetWidth(30).HCenter().VCenter();
	myInterface.addItem("Додати крило", [this, &myInterface]() {
	
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("Видалити крило", [this, &myInterface]() {
	
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("Редагувати крило", [this, &myInterface]() {
		
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.Select();
	return *this;
}

progMenu& Aerodynamics::UI::progMenu::aircraftMenu()
{
	FunctionMenu myInterface("МЕНЮ ПОВIТРЯНИХ СУДЕН", 1);
	myInterface.SetHeight(9).SetWidth(30).HCenter().VCenter();
	myInterface.addItem("Додати повiтряне судно", [this, &myInterface]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(9).VCenter().HCenter();
		win.Show();
		win.Write(0,0,"Створення повiтряного судна");

		InputV2 in(2, win.GetX() + 18, win.GetY() + 2);
		in.process(0);
		Aerodynamics::Data::Aircraft air;
		aircB.add(air);
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("Таблиця повiтряних суден", [this, &myInterface]() {
		_getch();
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("Сортувати таблицю", [this, &myInterface]() {
		_getch();
		funConsole::clearScr();
		myInterface.Select();
		});

	myInterface.addItem("Видалити повiтряне судно", [this, &myInterface]() {
		_getch();
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("Видалити всi суда", [this, &myInterface]() {
		_getch();
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.Select();
	return *this;
}

