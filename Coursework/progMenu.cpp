#include "ProgMenu.h"

using namespace Aerodynamics::UI;
using namespace Aerodynamics::Data;

progMenu& progMenu::start()
{
	setlocale(0, "en");
	FunctionMenu myInterface("������� ����", 1);
	myInterface.SetHeight(9).SetWidth(30).HCenter().VCenter();
	myInterface.addItem("���� ����", [this, &myInterface]() {
		this->wingsMenu();
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("���� ���i������ �����", [this, &myInterface]() {
		this->aircraftsMenu();
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

progMenu& progMenu::wingsMenu()
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

progMenu& Aerodynamics::UI::progMenu::aircraftsMenu()
{
	FunctionMenu myInterface("���� ���I������ �����", 1);
	myInterface.SetHeight(9).SetWidth(30).HCenter().VCenter();
	myInterface.addItem("������ ���i����� �����", [this, &myInterface]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(9).VCenter().HCenter();
		win.Show();
		win.Write(0,0,"��������� ���i������� �����");
		win.Write(0,1,"������     :");
		win.Write(0,2,"�������(�)      :");
		win.Write(0,3,"�i������ ����(H):");
		win.Write(0,4,"���� ����    (H):");
		win.Write(0,5,"���� �����   (H):");
		win.Write(0,6,"���� ���i��� (H):");
		InputV2 in(12, win.GetX() + 18, win.GetY() + 2);
		in.process(2,0);
		string name = in.get();
		in.Move(win.GetX() + 18, win.GetY() + 3);
		in.process(1,0);
		double l = ((String)in.get()).atoi();
		in.Move(win.GetX() + 18, win.GetY() + 4);
		in.process(3, 0);
		double Y = ((String)in.get()).atoi();
		in.Move(win.GetX() + 18, win.GetY() + 5);
		in.process(3, 0);
		double D = ((String)in.get()).atoi();
		in.Move(win.GetX() + 18, win.GetY() + 6);
		in.process(3, 0);
		double X = ((String)in.get()).atoi();
		in.Move(win.GetX() + 18, win.GetY() + 7);
		in.process(3, 0);
		double G = ((String)in.get()).atoi();
		Aircraft air(name,l,D,X,Y,G);
		aircB.add(air);
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("������� ���i������ �����", [this, &myInterface]() {
		funConsole::clearScr();
		FunctionMenu table("������� ���i������ �����", 1);
		table.SetHeight(9).SetWidth(30).HCenter().VCenter();
		for (auto i = aircB.getObjects().begin(); i != aircB.getObjects().end(); i++)
			table.addItem(i->dataF.getName(), [this, &myInterface,i]() {
			funConsole::clearScr();
			aircraftMenu(i->dataF);
			funConsole::clearScr();
			myInterface.Select();
				});
		table.Select();
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("��������� �������", [this, &myInterface]() {
		_getch();
		funConsole::clearScr();
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("�������� ��i ����", [this, &myInterface]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(9).VCenter().HCenter();
		win.Show();
		win.Write(0, 0, "�� �������i?(1/0)");
		InputV2 in(1, win.GetX() + 18, win.GetY() + 1);
		in.process(1, 0);
		if (((String)in.get()).atoi()) {
			aircB.del();
		}
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.Select();
	return *this;
}

progMenu& Aerodynamics::UI::progMenu::aircraftMenu(Aircraft& airc)
{
	FunctionMenu aircraftMenu("���� ���I������� �����", 1);
	aircraftMenu.SetHeight(9).SetWidth(30).HCenter().VCenter();
	aircraftMenu.addItem("������� ���i", [this, &aircraftMenu,&airc]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(9).VCenter().HCenter();
		win.Show();
		String name = (String)"������     :"+airc.getName().c_str();
		win.Write(0, 0, name);
		String l = (String)"�������(�)      :"+String(airc.getL());
		win.Write(0, 1, l);
		String Y = (String)"�i������ ����(H):"+ (String)airc.getY();
		win.Write(0, 2, Y);
		String D = (String)"���� ����    (H):"+ (String)airc.getD();
		win.Write(0, 3, D);
		String X = (String)"���� �����   (H):"+ (String)airc.getX();
		win.Write(0, 4, X);
		String G = (String)"���� ���i��� (H):"+ (String)airc.getG();
		win.Write(0, 5, G);
		//model wing
		_getch();
		aircraftMenu.Select();
		funConsole::clearScr();
		});
	aircraftMenu.addItem("�������� ���������i��i ����������i", [this, &aircraftMenu]() {
		funConsole::clearScr();
		FunctionMenu aeroMenu("���������i��i ����������i", 1);
		aeroMenu.SetHeight(9).SetWidth(30).HCenter().VCenter();
		
		aircraftMenu.Select();
		funConsole::clearScr();
		});	
	aircraftMenu.addItem("���������� �����", [this, &aircraftMenu]() {
		funConsole::clearScr();
		aircraftMenu.Select();
		funConsole::clearScr();
		});

	aircraftMenu.addItem("�������� �����", [this, &aircraftMenu]() {
		funConsole::clearScr();

		aircraftMenu.Select();
		funConsole::clearScr();
		});
	aircraftMenu.Select();
	return *this;
}

