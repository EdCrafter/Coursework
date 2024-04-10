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
		win.Write(0,1,"Модель          :");
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
		unsigned int j = 0;
		for ( auto i = aircB.getObjects().begin(); i != aircB.getObjects().end(); i++)
			table.addItem(i->dataF.getName(), [this, &myInterface,i,&j]() {
			funConsole::clearScr();
			aircraftMenu(i->dataF,j);
			j++;
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

progMenu& Aerodynamics::UI::progMenu::aircraftMenu(Aircraft& airc,unsigned int j)
{
	FunctionMenu aircraftMenu("МЕНЮ ПОВIТРЯНОГО СУДНА", 1);
	aircraftMenu.SetHeight(8).SetWidth(40).HCenter().VCenter();
	aircraftMenu.addItem("Вивести данi", [this, &aircraftMenu,&airc]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(9).VCenter().HCenter();
		win.Show();
		String name = (String)"Модель          :"+airc.getName().c_str();
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
		_getch();
		funConsole::clearScr();
		aircraftMenu.Select();
		});
	aircraftMenu.addItem("Показати аеродинамiчнi властивостi", [this, &aircraftMenu,&airc]() {
		funConsole::clearScr();
		FunctionMenu aeroMenu(" angle |  Cx   |  Cy   |   K   ");
		aeroMenu.SetHeight(9).SetWidth(33).HCenter().VCenter();
		Aerodynamics::Analytics::AeroProperties aero = airc.getAeroProperties();
		int l = aero.size();
		if (!l) {
			aeroMenu.addItem("Немає даних", [this, &aeroMenu]() {
				funConsole::clearScr();
				});
		}
		else {
			Window win;
			win.SetWidth(25).SetHeight(6).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, "1) 1.");
			win.Write(0, 1, "2) 0.1");
			win.Write(0, 2, "3) 0.01");
			win.Write(0, 3, "Точнiсть (1/2/3):");
			InputV2 in(2, win.GetX() + 19, win.GetY() + 4);
			in.process(3, 0);
			int prec = ((String)in.get()).atoi();
			double step;
			if (prec == 1) {
				step = 1;
			}
			else if (prec == 2) {
				step = 0.1;
			}
			else {
				step = 0.01;
			}
			double min = aero[0].a;
			double max = aero[l - 1].a;
			max += step;
			funConsole::clearScr();
			for (double angle = min; angle < max; angle +=step) {
				String i = String(angle,2).setSize(7) +"|" + String(aero.getCx(angle), 2).setSize(7)
					+ "|" + String(aero.getCy(angle), 2).setSize(7) + "|" + String(aero.getK(angle), 2).setSize(7);
				aeroMenu.addItem(i, [this, &aeroMenu]() {
					funConsole::clearScr();
					});
			}
		}
		aeroMenu.Select();
		
		funConsole::clearScr();
		aircraftMenu.Select();
		});	
	aircraftMenu.addItem("Додати аеродинамiчнi властивостi", [this, &aircraftMenu, &airc]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(3).VCenter().HCenter();
		win.Show();
		win.Write(0, 0, "Введiть к-ть контрольних точок:");
		InputV2 in(3, win.GetX() + 32, win.GetY() + 1);
		in.process(3);
		int l = ((String)in.get()).atoi();
		funConsole::clearScr();
		win.SetHeight(9).SetWidth(40).VCenter().HCenter();
		
		for (int i = 0; i < l; i++) {
			win.Show();
			String name = (String)"   Точка " + (String)(i+1);
			win.Write(0, 0, name);
			win.Write(0, 1, "Кут атаки(град) :");
			win.Write(0, 2, "Cx              :");
			win.Write(0, 3, "Cy              :");
			InputV2 in(12, win.GetX() + 18, win.GetY() + 2);
			in.process(1, 0);
			double angle = ((String)in.get()).atof();
			in.Move(win.GetX() + 18, win.GetY() + 3);
			in.process(1, 0);
			double Cx = ((String)in.get()).atof();
			in.Move(win.GetX() + 18, win.GetY() + 4);
			in.process(1, 0);
			double Cy = ((String)in.get()).atof();
			airc.getAeroProperties().add(Cx, Cy,angle);
			funConsole::clearScr();
		}
		aircraftMenu.Select();
		});
	aircraftMenu.addItem("Редагувати судно", [this, &aircraftMenu, &airc]() {
		funConsole::clearScr();
		FunctionMenu editMenu("РЕДАГУВАННЯ ПОВIТРЯНОГО СУДНА", 1);
		editMenu.SetHeight(9).SetWidth(35).HCenter().VCenter();
		editMenu.addItem("Змiнити модель", [this, &editMenu, &airc]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, airc.getName().c_str());
			win.Write(0, 1, "Нова модель:");
			InputV2 in(20, win.GetX() + 14, win.GetY() + 2);
			in.process(0, 0);
			airc.setName(in.get());
			funConsole::clearScr();
			editMenu.Select();
			});
		editMenu.addItem("Змiнити довжину", [this, &editMenu, &airc]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, String(airc.getL()).get());
			win.Write(0, 1, "Нова довжина(м):");
			InputV2 in(20, win.GetX() + 17, win.GetY() + 2);
			in.process(3, 0);
			double l = ((String)in.get()).atoi();
			airc.setL(l);
			funConsole::clearScr();
			editMenu.Select();
			});
		editMenu.addItem("Змiнити пiдйомну силу", [this, &editMenu, &airc]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, String(airc.getY()).get());
			win.Write(0, 1, "Нова пiдйомна сила(H):");
			InputV2 in(20, win.GetX() + 23, win.GetY() + 2);
			in.process(3, 0);
			double Y = ((String)in.get()).atoi();
			airc.setY(Y);
			funConsole::clearScr();
			editMenu.Select();
			});
		editMenu.addItem("Змiнити силу тяги", [this, &editMenu, &airc]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, String(airc.getD()).get());
			win.Write(0, 1, "Нова сила тяги(H):");
			InputV2 in(20, win.GetX() + 19, win.GetY() + 2);
			in.process(3, 0);
			double D = ((String)in.get()).atoi();
			airc.setD(D);
			funConsole::clearScr();
			editMenu.Select();
			});
		editMenu.addItem("Змiнити силу опору", [this, &editMenu, &airc]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, String(airc.getX()).get());
			win.Write(0, 1, "Нова сила опору(H):");
			InputV2 in(20, win.GetX() + 20, win.GetY() + 2);
			in.process(3, 0);
			double X = ((String)in.get()).atoi();
			airc.setX(X);
			funConsole::clearScr();
			editMenu.Select();
			});
		editMenu.addItem("Змiнити силу тяжiння", [this, &editMenu, &airc]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, String(airc.getG()).get());
			win.Write(0, 1, "Нова сила тяжiння(H):");
			InputV2 in(20, win.GetX() + 22, win.GetY() + 2);
			in.process(3, 0);
			double G = ((String)in.get()).atoi();
			airc.setG(G);
			funConsole::clearScr();
			editMenu.Select();
			});
		editMenu.Select();
		funConsole::clearScr();
		aircraftMenu.Select();
		});
	aircraftMenu.addItem("Меню центрування", [this, &aircraftMenu, &airc]() {
		funConsole::clearScr();
		FunctionMenu centerMenu("МЕНЮ ЦЕНТРУВАННЯ", 1);
		centerMenu.SetHeight(9).SetWidth(30).HCenter().VCenter();
		centerMenu.addItem("Показати центрування", [this, &centerMenu, &airc]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, (String)"x = "+String(airc.getAlignment()*100,2).get()+(String)"%");
			_getch();
			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.addItem("Змiнити центрування", [this, &centerMenu, &airc]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, (String)"x = " + String(airc.getAlignment() * 100, 2).get() + (String)"%");
			win.Write(0, 1, "Нове центрування(%):");
			InputV2 in(6, win.GetX() + 21, win.GetY() + 2);
			in.process(1);
			airc.setAlignment(((String)in.get()).atof() / 100);
			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.addItem("Обчислити центрування", [this, &centerMenu, &airc]() {
			funConsole::clearScr();
			double distance=0;
			double weight = airc.getG()/Aerodynamics::Analytics::AtmosphereConstants::g;
			double _x = airc.getAlignment()*100;
			double cargoG = 0;
			funConsole::clearScr();
			cout <<"w="<< & cargoG << "\n";
			_getch();
			FunctionMenu calcMenu("ОбЧИСЛЕННЯ ЦЕНТРУВАННЯ", 1);
			calcMenu.SetHeight(9).SetWidth(50).HCenter().VCenter();
			calcMenu.addItem((String)"Вага вантажу:"+String(cargoG), [&calcMenu, &airc, &cargoG]() {
				funConsole::clearScr();
				Window win;
				win.SetWidth(40).SetHeight(4).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, "Введiть вагу вантажу(кг):");
				InputV2 in(6, win.GetX() + 26, win.GetY() + 1);
				in.process(1);
				funConsole::clearScr();
				cout << &cargoG << "\n";
				_getch();
				cargoG = ((String)in.get()).atoi();
				funConsole::clearScr();
				calcMenu.Select();
				});
			calcMenu.addItem((String)"Перемiстити на вiдстань : " + String(distance), [&calcMenu, &airc, &distance]() {
				funConsole::clearScr();
				Window win;
				win.SetWidth(40).SetHeight(4).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, "Введiть вiдстань(м):");
				InputV2 in(6, win.GetX() + 21, win.GetY() + 1);
				in.process(3, 0);
				distance = ((String)in.get()).atoi();
				funConsole::clearScr();
				calcMenu.Select();
				});	
			calcMenu.addItem((String)"Центрування : " + String(_x,2)+(String)"%", [&calcMenu, &airc, &_x]() {
				funConsole::clearScr();
				Window win;
				win.SetWidth(40).SetHeight(4).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, "Введiть центрування(%):");
				InputV2 in(6, win.GetX() + 24, win.GetY() + 1);
				in.process(1);
				_x = ((String)in.get()).atof();
				funConsole::clearScr();
				calcMenu.Select();
				});
			calcMenu.addItem("Обчислити", [& calcMenu, &airc, &distance]() {});
			calcMenu.Select();
			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.Select();
		funConsole::clearScr();
		aircraftMenu.Select();
		});
	aircraftMenu.addItem("Видалити судно", [this, &aircraftMenu,&j]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(9).VCenter().HCenter();
		win.Show();
		win.Write(0, 0, "Ви впевненi?(1/0):");
		InputV2 in(2, win.GetX() + 19, win.GetY() + 1);
		in.process(3, 0);
		if (((String)in.get()).atoi()) {
			aircB.remove(j);
		}
		else {
			funConsole::clearScr();
			aircraftMenu.Select();
		}
		funConsole::clearScr();
		});
	aircraftMenu.Select();
	return *this;
}

