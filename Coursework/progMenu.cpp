#include "ProgMenu.h"

using namespace Aerodynamics::UI;
using namespace Aerodynamics::Data;

progMenu& progMenu::start()
{
	setlocale(0, "en");
	FunctionMenu myInterface("ГОЛОВНЕ МЕНЮ", 1);
	myInterface.SetHeight(9).SetWidth(30).HCenter().VCenter();
	myInterface.addItem("Меню крил", [this, &myInterface]() {
		this->wingsMenu();
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("Меню повiтряних суден", [this, &myInterface]() {
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

progMenu& Aerodynamics::UI::progMenu::aircraftsMenu()
{
	FunctionMenu myInterface("МЕНЮ ПОВIТРЯНИХ СУДЕН", 1);
	myInterface.SetHeight(9).SetWidth(30).HCenter().VCenter();
	myInterface.addItem("Додати повiтряне судно", [this, &myInterface]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(9).VCenter().HCenter();
		win.Show();
		win.Write(0,0,"Створення повiтряного судна");
		win.Write(0,1,"Модель     :");
		win.Write(0,2,"Довжина(м)      :");
		win.Write(0,3,"Пiдйомна сила(H):");
		win.Write(0,4,"Сила тяги    (H):");
		win.Write(0,5,"Сила опору   (H):");
		win.Write(0,6,"Сила тяжiння (H):");
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
	myInterface.addItem("Таблиця повiтряних суден", [this, &myInterface]() {
		funConsole::clearScr();
		FunctionMenu table("Таблиця повiтряних суден", 1);
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
	myInterface.addItem("Сортувати таблицю", [this, &myInterface]() {
		_getch();
		funConsole::clearScr();
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("Видалити всi суда", [this, &myInterface]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(9).VCenter().HCenter();
		win.Show();
		win.Write(0, 0, "Ви впевненi?(1/0)");
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
	FunctionMenu aircraftMenu("МЕНЮ ПОВIТРЯНОГО СУДНА", 1);
	aircraftMenu.SetHeight(9).SetWidth(30).HCenter().VCenter();
	aircraftMenu.addItem("Вивести данi", [this, &aircraftMenu,&airc]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(9).VCenter().HCenter();
		win.Show();
		String name = (String)"Модель     :"+airc.getName().c_str();
		win.Write(0, 0, name);
		String l = (String)"Довжина(м)      :"+String(airc.getL());
		win.Write(0, 1, l);
		String Y = (String)"Пiдйомна сила(H):"+ (String)airc.getY();
		win.Write(0, 2, Y);
		String D = (String)"Сила тяги    (H):"+ (String)airc.getD();
		win.Write(0, 3, D);
		String X = (String)"Сила опору   (H):"+ (String)airc.getX();
		win.Write(0, 4, X);
		String G = (String)"Сила тяжiння (H):"+ (String)airc.getG();
		win.Write(0, 5, G);
		//model wing
		_getch();
		aircraftMenu.Select();
		funConsole::clearScr();
		});
	aircraftMenu.addItem("Показати аеродинамiчнi властивостi", [this, &aircraftMenu]() {
		funConsole::clearScr();
		FunctionMenu aeroMenu("Аеродинамiчнi властивостi", 1);
		aeroMenu.SetHeight(9).SetWidth(30).HCenter().VCenter();
		
		aircraftMenu.Select();
		funConsole::clearScr();
		});	
	aircraftMenu.addItem("Редагувати судно", [this, &aircraftMenu]() {
		funConsole::clearScr();
		aircraftMenu.Select();
		funConsole::clearScr();
		});

	aircraftMenu.addItem("Видалити судно", [this, &aircraftMenu]() {
		funConsole::clearScr();

		aircraftMenu.Select();
		funConsole::clearScr();
		});
	aircraftMenu.Select();
	return *this;
}

