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
		FunctionMenu myInterface("������� ����", 1);
		myInterface.SetHeight(9).SetWidth(30).HCenter().VCenter();
		myInterface.addItem("������ ���i����� �����", [this, &myInterface]() {
			_getch();
			funConsole::clearScr();
			myInterface.Select();
			});		
		myInterface.addItem("������� ���i������ �����", [this, &myInterface]() {
			_getch();
			funConsole::clearScr();
			myInterface.Select();
			});
		myInterface.addItem("��������� �������", [this, &myInterface]() {
			_getch();
			funConsole::clearScr();
			myInterface.Select();
			});
		myInterface.addItem("���� ����", [this, &myInterface]() {
			_getch();
			funConsole::clearScr();
			myInterface.Select();
			});
		myInterface.addItem("�������� ���i����� �����", [this, &myInterface]() {
			_getch();
			funConsole::clearScr();
			myInterface.Select();
			});
		myInterface.addItem("�������� ��i ����", [this, &myInterface]() {
			_getch();
			funConsole::clearScr();
			myInterface.Select();
			});

		myInterface.Select();
		return *this;
	}
};

