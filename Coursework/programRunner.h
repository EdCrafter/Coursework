#pragma once
#include "AircraftBase.h"
#include "Window.h"
using namespace Aerodynamics::UI;
class ProgramRunner
{
	
	Aerodynamics::Data::AircraftBase aircB;
	Aerodynamics::Data::WingBase wingB;
	Aerodynamics::Data::AeroPropertiesBase apB;
public:
	ProgramRunner() = default;
	ProgramRunner& start() {
		setlocale(0, "en");
		FunctionMenu myInterface("ГОЛОВНЕ МЕНЮ", 1);
		myInterface.SetHeight(9).SetWidth(30).HCenter().VCenter();
		myInterface.addItem("Додати повiтряне судно", [this, &myInterface]() {
			_getch();
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
		myInterface.addItem("Меню Крил", [this, &myInterface]() {
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
};

