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
		win.Write(0,1,"������          :");
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

progMenu& Aerodynamics::UI::progMenu::aircraftMenu(Aircraft& airc,unsigned int j)
{
	FunctionMenu aircraftMenu("���� ���I������� �����", 1);
	aircraftMenu.SetHeight(8).SetWidth(40).HCenter().VCenter();
	aircraftMenu.addItem("������� ���i", [this, &aircraftMenu,&airc]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(9).VCenter().HCenter();
		win.Show();
		String name = (String)"������          :"+airc.getName().c_str();
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
		_getch();
		funConsole::clearScr();
		aircraftMenu.Select();
		});
	aircraftMenu.addItem("�������� ���������i��i ����������i", [this, &aircraftMenu,&airc]() {
		funConsole::clearScr();
		FunctionMenu aeroMenu(" angle |  Cx   |  Cy   |   K   ");
		aeroMenu.SetHeight(9).SetWidth(33).HCenter().VCenter();
		Aerodynamics::Analytics::AeroProperties aero = airc.getAeroProperties();
		int l = aero.size();
		if (!l) {
			aeroMenu.addItem("���� �����", [this, &aeroMenu]() {
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
			win.Write(0, 3, "����i��� (1/2/3):");
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
	aircraftMenu.addItem("������ ���������i��i ����������i", [this, &aircraftMenu, &airc]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(3).VCenter().HCenter();
		win.Show();
		win.Write(0, 0, "����i�� �-�� ����������� �����:");
		InputV2 in(3, win.GetX() + 32, win.GetY() + 1);
		in.process(3);
		int l = ((String)in.get()).atoi();
		funConsole::clearScr();
		win.SetHeight(9).SetWidth(40).VCenter().HCenter();
		
		for (int i = 0; i < l; i++) {
			win.Show();
			String name = (String)"   ����� " + (String)(i+1);
			win.Write(0, 0, name);
			win.Write(0, 1, "��� �����(����) :");
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
	aircraftMenu.addItem("���������� �����", [this, &aircraftMenu, &airc]() {
		funConsole::clearScr();
		FunctionMenu editMenu("����������� ���I������� �����", 1);
		editMenu.SetHeight(9).SetWidth(35).HCenter().VCenter();
		editMenu.addItem("��i���� ������", [this, &editMenu, &airc]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, airc.getName().c_str());
			win.Write(0, 1, "���� ������:");
			InputV2 in(20, win.GetX() + 14, win.GetY() + 2);
			in.process(0, 0);
			airc.setName(in.get());
			funConsole::clearScr();
			editMenu.Select();
			});
		editMenu.addItem("��i���� �������", [this, &editMenu, &airc]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, String(airc.getL()).get());
			win.Write(0, 1, "���� �������(�):");
			InputV2 in(20, win.GetX() + 17, win.GetY() + 2);
			in.process(3, 0);
			double l = ((String)in.get()).atoi();
			airc.setL(l);
			funConsole::clearScr();
			editMenu.Select();
			});
		editMenu.addItem("��i���� �i������ ����", [this, &editMenu, &airc]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, String(airc.getY()).get());
			win.Write(0, 1, "���� �i������ ����(H):");
			InputV2 in(20, win.GetX() + 23, win.GetY() + 2);
			in.process(3, 0);
			double Y = ((String)in.get()).atoi();
			airc.setY(Y);
			funConsole::clearScr();
			editMenu.Select();
			});
		editMenu.addItem("��i���� ���� ����", [this, &editMenu, &airc]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, String(airc.getD()).get());
			win.Write(0, 1, "���� ���� ����(H):");
			InputV2 in(20, win.GetX() + 19, win.GetY() + 2);
			in.process(3, 0);
			double D = ((String)in.get()).atoi();
			airc.setD(D);
			funConsole::clearScr();
			editMenu.Select();
			});
		editMenu.addItem("��i���� ���� �����", [this, &editMenu, &airc]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, String(airc.getX()).get());
			win.Write(0, 1, "���� ���� �����(H):");
			InputV2 in(20, win.GetX() + 20, win.GetY() + 2);
			in.process(3, 0);
			double X = ((String)in.get()).atoi();
			airc.setX(X);
			funConsole::clearScr();
			editMenu.Select();
			});
		editMenu.addItem("��i���� ���� ���i���", [this, &editMenu, &airc]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, String(airc.getG()).get());
			win.Write(0, 1, "���� ���� ���i���(H):");
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
	aircraftMenu.addItem("���� �����������", [this, &aircraftMenu, &airc]() {
		funConsole::clearScr();
		FunctionMenu centerMenu("���� �����������", 1);
		centerMenu.SetHeight(9).SetWidth(30).HCenter().VCenter();
		centerMenu.addItem("�������� �����������", [this, &centerMenu, &airc]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, (String)"x = "+String(airc.getAlignment()*100,2).get()+(String)"%");
			_getch();
			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.addItem("��i���� �����������", [this, &centerMenu, &airc]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, (String)"x = " + String(airc.getAlignment() * 100, 2).get() + (String)"%");
			win.Write(0, 1, "���� �����������(%):");
			InputV2 in(6, win.GetX() + 21, win.GetY() + 2);
			in.process(1);
			airc.setAlignment(((String)in.get()).atof() / 100);
			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.addItem("��������� �����������", [this, &centerMenu, &airc]() {
			funConsole::clearScr();
			double distance = 0;
			double weight = airc.getG() / Aerodynamics::Analytics::AtmosphereConstants::g;
			double _x = airc.getAlignment() ;
			double cargoG = 1;
			double MAC = 1;
			bool tail = true;
			if (this->wingB.size() != 0) {
				MAC = airc.getWing().getMAC();
			}
			
			FunctionMenu calcMenu("���������� �����������", 1);
			calcMenu.SetHeight(11).SetWidth(50).HCenter().VCenter();
			calcMenu.addItem("�������� ��i��i ���i", [&calcMenu, &airc, &distance, &cargoG, &_x,&weight,&MAC,&tail]() {
				funConsole::clearScr();
				Window win;
				win.SetWidth(40).SetHeight(8).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, (String)"���� �������(��)     :" + String(cargoG));
				win.Write(0, 1, (String)"�i������(�)          :" + String(distance));
				win.Write(0, 2, (String)"����������� ���������:" + String(_x * 100, 2) + "%");
				win.Write(0, 3, (String)"���� �����(��)       :" + String(weight));
				win.Write(0, 4, (String)"���(����� �)         :" + String(MAC));
				win.Write(0, 5, (String)"����    :" + ((tail)?String("�� ������ �������"):String("�� �������� �������")));
				_getch();
				funConsole::clearScr();
				calcMenu.Select();
				});
			calcMenu.addItem("��i���� ���� �������", [&calcMenu, &airc, &cargoG]() {
				funConsole::clearScr();
				Window win;
				win.SetWidth(40).SetHeight(4).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, "����i�� ���� �������(��):");
				InputV2 in(6, win.GetX() + 26, win.GetY() + 1);
				in.process(1);
				cargoG = ((String)in.get()).atoi();
				funConsole::clearScr();
				calcMenu.Select();
				});
			calcMenu.addItem("��i���� ���� �����", [&calcMenu, &airc, &weight]() {
				funConsole::clearScr();
				Window win;
				win.SetWidth(40).SetHeight(4).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, "����i�� ���� �������(��):");
				InputV2 in(6, win.GetX() + 26, win.GetY() + 1);
				in.process(1);
				weight = ((String)in.get()).atoi();
				airc.setG(weight * Aerodynamics::Analytics::AtmosphereConstants::g);
				funConsole::clearScr();
				calcMenu.Select();
				});
			calcMenu.addItem("�����i����� �� �i������", [&calcMenu, &airc, &distance]() {
				funConsole::clearScr();
				Window win;
				win.SetWidth(40).SetHeight(4).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, "����i�� �i������(�):");
				InputV2 in(6, win.GetX() + 21, win.GetY() + 1);
				in.process(1, 0);
				distance = ((String)in.get()).atoi();
				funConsole::clearScr();
				calcMenu.Select();
				});
			calcMenu.addItem("��i���� ��������� �����������", [&calcMenu, &airc, &_x]() {
				funConsole::clearScr();
				Window win;
				win.SetWidth(40).SetHeight(4).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, "����i�� �����������(%):");
				InputV2 in(6, win.GetX() + 24, win.GetY() + 1);
				in.process(1);
				_x = ((String)in.get()).atof();
				funConsole::clearScr();
				calcMenu.Select();
				});
			calcMenu.addItem("��i���� ���", [&calcMenu, &airc, &MAC]() {
				funConsole::clearScr();
				Window win;
				win.SetWidth(40).SetHeight(4).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, "����i�� ���(�):");
				InputV2 in(6, win.GetX() + 16, win.GetY() + 1);
				in.process(1, 0);
				MAC = ((String)in.get()).atoi();
				funConsole::clearScr();
				calcMenu.Select();
			});
			calcMenu.addItem("���� �����i�����", [&calcMenu, &airc, &tail]() {
				funConsole::clearScr();
				Window win;
				win.SetWidth(40).SetHeight(4).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, "���� �����i�����(1/0):");
				InputV2 in(1, win.GetX() + 23, win.GetY() + 1);
				in.process(1, 0);
				tail = ((String)in.get()).atoi();
				funConsole::clearScr();
				calcMenu.Select();
				});
			calcMenu.addItem("���������", [&calcMenu, &airc, &distance,&tail,&cargoG,&weight,&MAC,&_x]() {
				funConsole::clearScr();
				airc.evalAlignment(distance, cargoG, weight, tail, MAC, _x);
				Window win;
				win.SetWidth(40).SetHeight(4).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, (String)"���� �����������(%):" + String(airc.getAlignment() * 100, 2));
				_getch();
				});
			calcMenu.Select();

			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.Select();
		funConsole::clearScr();
		aircraftMenu.Select();
		});
	aircraftMenu.addItem("�������� �����", [this, &aircraftMenu,&j]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(9).VCenter().HCenter();
		win.Show();
		win.Write(0, 0, "�� �������i?(1/0):");
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

