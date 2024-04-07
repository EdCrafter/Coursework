#include "ProgMenu.h"

using namespace Aerodynamics::UI;

progMenu& progMenu::start()
{
	setlocale(0, "en");
	FunctionMenu myInterface("������� ����", 1);
	myInterface.SetHeight(9).SetWidth(30).HCenter().VCenter();
	myInterface.addItem("���� ����", [this, &myInterface]() {
		this->wingMenu();
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("���� ���i������ �����", [this, &myInterface]() {
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
	FunctionMenu myInterface("���� ����", 1);
	myInterface.SetHeight(9).SetWidth(30).HCenter().VCenter();
	myInterface.addItem("������ �����", [this, &myInterface]() {
	
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("�������� �����", [this, &myInterface]() {
	
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("���������� �����", [this, &myInterface]() {
		
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.Select();
	return *this;
}

progMenu& Aerodynamics::UI::progMenu::aircraftMenu()
{
	FunctionMenu myInterface("���� ���I������ �����", 1);
	myInterface.SetHeight(9).SetWidth(30).HCenter().VCenter();
	myInterface.addItem("������ ���i����� �����", [this, &myInterface]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(9).VCenter().HCenter();
		win.Show();
		win.Write(0,0,"��������� ���i������� �����");

		InputV2 in(2, win.GetX() + 18, win.GetY() + 2);
		in.process(0);
		Aerodynamics::Data::Aircraft air;
		aircB.add(air);
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

