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
	funConsole::clearScr();
	myInterface.SetHeight(8).SetWidth(30).HCenter().VCenter();
	myInterface.addItem("������ �����", [this, &myInterface]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(7).VCenter().HCenter();
		win.Show();
		win.Write(0, 0, "��������� �����");
		win.Write(0, 1, "������          :");
		win.Write(0, 3, "���(�)          :");
		win.Write(0, 2, "�������(�)      :");
		win.Write(0, 4, "�����(�^2)      :");
		InputV2 in(12, win.GetX() + 18, win.GetY() + 2);
		in.process(0,0);
		string name = in.get();
		in.Move(win.GetX() + 18, win.GetY() + 3);
		in.process(1, 0);
		double _MAC = ((String)in.get()).atoi();
		in.Move(win.GetX() + 18, win.GetY() + 4);
		in.process(3, 0);
		double l = ((String)in.get()).atoi();
		in.Move(win.GetX() + 18, win.GetY() + 5);
		in.process(3, 0);
		double _S = ((String)in.get()).atoi();
		Wing wing(name,_MAC, l, _S);
		
		wingB.add(wing);
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("������� ����", [this, &myInterface]() {
		funConsole::clearScr();
		FunctionMenu table("������� ����", 1);
		table.SetHeight(9).SetWidth(30).HCenter().VCenter();
		unsigned int j = 0;
		for (auto i = wingB.getObjects().begin(); i != wingB.getObjects().end(); i++)
			table.addItem(i->dataF.getName(), [this, &myInterface, i, &j]() {
			funConsole::clearScr();
			wingMenu(i->dataF, j);
			j++;
			funConsole::clearScr();
			myInterface.Select();
				});
		table.Select();
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("����������� ���i �� �����", [this, &myInterface]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(4).VCenter().HCenter();
		win.Show();
		win.Write(0, 0, "����i�� �����:");
		win.Write(0, 1, "������ (0-txt/1-html):");
		InputV2 in(20, win.GetX() + 15, win.GetY() + 1);
		in.process(2, 0);
		String fileName = (String)(in.get());
		in.Move(win.GetX() + 23, win.GetY() + 2);
		in.setLength(1);
		in.process(1, 0);
		int format = ((String)in.get()).atoi();
		wingB.save((char*)(fileName.get()), (Aerodynamics::Data::Format)format);
		apB.save((char*)(fileName.get()), Aerodynamics::Data::Format::txt);
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("�i���������� ���i � �����", [this, &myInterface]() {
		funConsole::clearScr();

		namespace fs = std::filesystem;

		std::string folder = "WingBases/txt";

		// �������� ������������� ����������
		if (fs::exists(folder) && fs::is_directory(folder) && !fs::is_empty(folder)) {
			FunctionMenu fileMenu("���i� �� ����", 1);
			fileMenu.SetHeight(9).SetWidth(30).HCenter().VCenter();
			Data::Array<String> names;
			int i = 0;
			for (const auto& entry : fs::directory_iterator(folder)) {
				names.Add(entry.path().filename().string().c_str());
				fileMenu.addItem(names[i].get(), [this, &names, &fileMenu]() {
					funConsole::clearScr();
					int i = fileMenu.GetSelect() - 1;
					apB.read((char*)(names[i].get()));
					wingB.read((char*)(names[i].get()), &apB);
					Window win;
					win.SetWidth(40).SetHeight(3).VCenter().HCenter();
					win.Show();
					win.Write(0, 0, "���i �����������");
					_getch();
					});
				i++;
			}
			fileMenu.Select();
		}
		else {
			Window win;
			win.SetWidth(40).SetHeight(3).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, "����i� �� ��������");
			_getch();
		}
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("�������� ��i �����", [this, &myInterface]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(3).VCenter().HCenter();
		win.Show();
		win.Write(0, 0, "�� �������i?(1/0)");
		InputV2 in(1, win.GetX() + 18, win.GetY() + 1);
		in.process(1, 0);
		if (((String)in.get()).atoi()) {
			wingB.del();
		}
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.Select();
	funConsole::clearScr();
	return *this;
}

progMenu& Aerodynamics::UI::progMenu::wingMenu(Wing& wing, unsigned int j)
{
	FunctionMenu wingMenu("���� �����", 1);
	wingMenu.SetHeight(8).SetWidth(40).HCenter().VCenter();
	wingMenu.addItem("������� ���i", [this, &wingMenu, &wing]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(6).VCenter().HCenter();
		win.Show();
		String name = (String)"������          :" + wing.getName().c_str();
		win.Write(0, 0, name);
		String Y = (String)"���(�)          :" + (String)wing.getMAC();
		win.Write(0, 1, Y);
		String l = (String)"�������(�)      :" + String(wing.getL());
		win.Write(0, 2, l);
		String S = (String)"�����(�^2)      :" + (String)wing.getS();
		win.Write(0, 3, S);
		_getch();
		funConsole::clearScr();
		wingMenu.Select();
		});
	wingMenu.addItem("�������� ���������i��i ����������i", [this, &wingMenu, &wing]() {
		funConsole::clearScr();
		FunctionMenu aeroMenu(" angle |  Cx   |  Cy   |   K   ");
		aeroMenu.SetHeight(9).SetWidth(33).HCenter().VCenter();
		Aerodynamics::Analytics::AeroProperties aero = wing.getAeroProperties();
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
			for (double angle = min; angle < max; angle += step) {
				String i = String(angle, 2).setSize(7) + "|" + String(aero.getCx(angle), 2).setSize(7)
					+ "|" + String(aero.getCy(angle), 2).setSize(7) + "|" + String(aero.getK(angle), 2).setSize(7);
				aeroMenu.addItem(i, [this, &aeroMenu]() {
					funConsole::clearScr();
					});
			}
		}
		aeroMenu.Select();

		funConsole::clearScr();
		wingMenu.Select();
		});
	wingMenu.addItem("������ ���������i��i ����������i", [this, &wingMenu, &wing]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(3).VCenter().HCenter();
		win.Show();
		win.Write(0, 0, "����i�� �-�� ����������� �����:");
		InputV2 in(3, win.GetX() + 32, win.GetY() + 1);
		in.process(3);
		int l = ((String)in.get()).atoi();
		funConsole::clearScr();
		win.SetHeight(6).SetWidth(40).VCenter().HCenter();

		Analytics::AeroProperties aero;
		for (int i = 0; i < l; i++) {
			win.Show();
			String name = (String)"   ����� " + (String)(i + 1);
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
			aero.add(Cx, Cy, angle);
			funConsole::clearScr();
		}

		apB.add(aero);
		wing.setAeroProperties(aero, wingB.getIDLast() - 1);
		wingMenu.Select();
	});
	wingMenu.addItem("���������� �����", [this, &wingMenu, &wing]() {
		funConsole::clearScr();
		FunctionMenu editMenu("����������� �����", 1);
		editMenu.SetHeight(7).SetWidth(35).HCenter().VCenter();
		editMenu.addItem("��i���� ������", [this, &editMenu, &wing]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, wing.getName().c_str());
			win.Write(0, 1, "���� ������:");
			InputV2 in(20, win.GetX() + 14, win.GetY() + 2);
			in.process(0, 0);
			wing.setName(in.get());
			funConsole::clearScr();
			editMenu.Select();
			});
		editMenu.addItem("��i���� �������", [this, &editMenu, &wing]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, String(wing.getL()).get());
			win.Write(0, 1, "���� �������(�):");
			InputV2 in(20, win.GetX() + 17, win.GetY() + 2);
			in.process(3, 0);
			double l = ((String)in.get()).atoi();
			wing.setL(l);
			funConsole::clearScr();
			editMenu.Select();
			});
		editMenu.addItem("��i���� ���", [this, &editMenu, &wing]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, String(wing.getMAC()).get());
			win.Write(0, 1, "���� ���(�)        :");
			InputV2 in(20, win.GetX() + 23, win.GetY() + 2);
			in.process(3, 0);
			double MAC = ((String)in.get()).atoi();
			wing.setMAC(MAC);
			funConsole::clearScr();
			editMenu.Select();
			});
		editMenu.addItem("��i���� �����", [this, &editMenu, &wing]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(4).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, String(wing.getS()).get());
			win.Write(0, 1, "���� �����(�):");
			InputV2 in(20, win.GetX() + 19, win.GetY() + 2);
			in.process(3, 0);
			double S = ((String)in.get()).atoi();
			wing.setS(S);
			funConsole::clearScr();
			editMenu.Select();
			});
		editMenu.Select();
		funConsole::clearScr();
		wingMenu.Select();
		});
	wingMenu.addItem("�������� �����", [this, &wingMenu, &j]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(3).VCenter().HCenter();
		win.Show();
		win.Write(0, 0, "�� �������i?(1/0):");
		InputV2 in(2, win.GetX() + 19, win.GetY() + 1);
		in.process(3, 0);
		if (((String)in.get()).atoi()) {
			wingB.remove(j);
		}
		else {
			funConsole::clearScr();
			wingMenu.Select();
		}
		funConsole::clearScr();
		});
	wingMenu.Select();
	return *this;
}

progMenu& Aerodynamics::UI::progMenu::aircraftsMenu()
{
	funConsole::clearScr();
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
		in.process(0,0);
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
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(12).VCenter().HCenter();
		win.Show();
		win.Write(0, 0, "1 - D");
		win.Write(0, 1, "2 - X");
		win.Write(0, 2, "3 - Y");
		win.Write(0, 3, "4 - G");
		win.Write(0, 4, "5 - ������������");
		win.Write(0, 5, "6 - ��������");
		win.Write(0, 6, "7 - �����i���");
		win.Write(0, 7, "8 - ������ �����");
		win.Write(0, 8, "9 - ������ ��");
		win.Write(0, 9, "��������� �� :");
		InputV2 in(12, win.GetX() + 18, win.GetY() + 10);
		in.process(1, 0);
		int i = ((String)in.get()).atoi()-1;
		aircB.sort((Aerodynamics::Data::Parametrs)i);
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("����������� ���i �� �����", [this, &myInterface]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(4).VCenter().HCenter();
		win.Show();
		win.Write(0, 0, "����i�� �����:");
		win.Write(0, 1, "������ (0-txt/1-html):");
		InputV2 in(20 , win.GetX() + 15, win.GetY() + 1);
		in.process(2, 0);
		String fileName = (String)(in.get());
		in.Move(win.GetX() + 23, win.GetY() + 2);
		in.setLength(1);
		in.process(1, 0);
		int format = ((String)in.get()).atoi();
		aircB.save((char*)(fileName.get()), (Aerodynamics::Data::Format)format);
		wingB.save((char*)(fileName.get()), Aerodynamics::Data::Format::txt);
		apB.save((char*)(fileName.get()),txt);
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("�i���������� ���i � �����", [this, &myInterface]() {
		funConsole::clearScr();

		namespace fs = std::filesystem;

		std::string folder = "AircraftBases/txt";

		// �������� ������������� ����������
		if (fs::exists(folder) && fs::is_directory(folder) && !fs::is_empty(folder)) {
			FunctionMenu fileMenu("���i� �� ���i������ �����", 1);
			fileMenu.SetHeight(9).SetWidth(30).HCenter().VCenter();
			Data::Array<String> names;
			int i = 0;
			for (const auto& entry : fs::directory_iterator(folder)) {
				names.Add(entry.path().filename().string().c_str());
				fileMenu.addItem(names[i].get(), [this, &names,&fileMenu]() {
					funConsole::clearScr();
					int i = fileMenu.GetSelect()-1;
					apB.read((char*)(names[i].get()));
					wingB.read((char*)(names[i].get()), &apB);
					aircB.read((char*)(names[i].get()),&wingB, &apB);
					Window win;
					win.SetWidth(40).SetHeight(3).VCenter().HCenter();
					win.Show();
					win.Write(0, 0, "���i �����������");
					_getch();
				});
				i++;
			}
			fileMenu.Select();
		}
		else {
			Window win;
			win.SetWidth(40).SetHeight(3).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, "����i� �� ��������");
			_getch();
		}
		funConsole::clearScr();
		myInterface.Select();
		});
	myInterface.addItem("�������� ��i ����", [this, &myInterface]() {
		funConsole::clearScr();
		Window win;
		win.SetWidth(40).SetHeight(3).VCenter().HCenter();
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
	aircraftMenu.SetHeight(12).SetWidth(40).HCenter().VCenter();
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
		String wName = (String)"������ �����    :"+ airc.getWing().getName().c_str();
		win.Write(0, 6, wName);
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
			max += step/2;
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
		win.SetHeight(6).SetWidth(40).VCenter().HCenter();
		
		Analytics::AeroProperties aero;
		for (int i = 0; i < l; i++) {
			win.Show();
			String name = (String)"   ����� " + (String)(i + 1);
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
			aero.add(Cx, Cy, angle);
			funConsole::clearScr();
		}
		apB.add(aero);
		airc.setAeroProperties(aero,apB.getIDLast()-1);
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
		centerMenu.SetHeight(6).SetWidth(30).HCenter().VCenter();
		centerMenu.addItem("�������� �����������", [this,&airc, &centerMenu]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(3).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, (String)"x = "+String(airc.getAlignment()*100,2).get()+(String)"%");
			_getch();
			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.addItem("��i���� �����������", [this,&airc, &centerMenu]() {
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
		centerMenu.addItem("��������� �����������", [this,&airc, &centerMenu]() {
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
			
			FunctionMenu centerMenu("���������� �����������", 1);
			centerMenu.SetHeight(11).SetWidth(50).HCenter().VCenter();
			centerMenu.addItem("�������� ��i��i ���i", [&centerMenu, &distance, &cargoG, &_x,&weight,&MAC,&tail]() {
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
				centerMenu.Select();
				});
			centerMenu.addItem("��i���� ���� �������", [&centerMenu, &cargoG]() {
				funConsole::clearScr();
				Window win;
				win.SetWidth(40).SetHeight(3).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, "����i�� ���� �������(��):");
				InputV2 in(6, win.GetX() + 26, win.GetY() + 1);
				in.process(1);
				cargoG = ((String)in.get()).atoi();
				funConsole::clearScr();
				centerMenu.Select();
				});
			centerMenu.addItem("��i���� ���� �����", [&centerMenu,&airc, &weight]() {
				funConsole::clearScr();
				Window win;
				win.SetWidth(40).SetHeight(3).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, "����i�� ���� �������(��):");
				InputV2 in(6, win.GetX() + 26, win.GetY() + 1);
				in.process(1);
				weight = ((String)in.get()).atoi();
				airc.setG(weight * Aerodynamics::Analytics::AtmosphereConstants::g);
				funConsole::clearScr();
				centerMenu.Select();
				});
			centerMenu.addItem("�����i����� �� �i������", [&centerMenu, &distance]() {
				funConsole::clearScr();
				Window win;
				win.SetWidth(40).SetHeight(3).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, "����i�� �i������(�):");
				InputV2 in(6, win.GetX() + 21, win.GetY() + 1);
				in.process(1, 0);
				distance = ((String)in.get()).atoi();
				funConsole::clearScr();
				centerMenu.Select();
				});
			centerMenu.addItem("��i���� ��������� �����������", [&centerMenu, &_x]() {
				funConsole::clearScr();
				Window win;
				win.SetWidth(40).SetHeight(3).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, "����i�� �����������(%):");
				InputV2 in(6, win.GetX() + 24, win.GetY() + 1);
				in.process(1);
				_x = ((String)in.get()).atof()/100.;
				funConsole::clearScr();
				centerMenu.Select();
				});
			centerMenu.addItem("��i���� ���", [&centerMenu, &MAC]() {
				funConsole::clearScr();
				Window win;
				win.SetWidth(40).SetHeight(3).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, "����i�� ���(�):");
				InputV2 in(6, win.GetX() + 16, win.GetY() + 1);
				in.process(1, 0);
				MAC = ((String)in.get()).atoi();
				funConsole::clearScr();
				centerMenu.Select();
			});
			centerMenu.addItem("���� �����i�����", [&centerMenu, &tail]() {
				funConsole::clearScr();
				Window win;
				win.SetWidth(45).SetHeight(3).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, "���� �����i�����(1 <- / 0 ->):");
				InputV2 in(1, win.GetX() + 30, win.GetY() + 1);
				in.process(1, 0);
				tail = ((String)in.get()).atoi();
				funConsole::clearScr();
				centerMenu.Select();
				});
			centerMenu.addItem("���������", [&centerMenu,&airc, &distance,&tail,&cargoG,&weight,&MAC,&_x]() {
				funConsole::clearScr();
				airc.evalAlignment(distance, cargoG, weight, tail, MAC, _x);
				Window win;
				win.SetWidth(40).SetHeight(3).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, (String)"���� �����������(%):" + String(airc.getAlignment() * 100, 2));
				_getch();
				});
			centerMenu.Select();

			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.Select();
		funConsole::clearScr();
		aircraftMenu.Select();
		});
	aircraftMenu.addItem("������� �����", [this, &aircraftMenu, &airc]() {
			funConsole::clearScr();
			if (wingB.size() == 0) {
				Window win;
				win.SetWidth(40).SetHeight(3).VCenter().HCenter();
				win.Show();
				win.Write(0, 0, "���� ����");
				_getch();
				funConsole::clearScr();
			}	
			else {
				FunctionMenu centerMenu("�����i�� �����", 1);
				centerMenu.SetHeight(6).SetWidth(30).HCenter().VCenter();
				unsigned int j = 0;
				for (auto i = wingB.getObjects().begin(); i != wingB.getObjects().end(); i++) {
					centerMenu.addItem(i->dataF.getName(), [this,&airc, &centerMenu, i, &j]() {
						funConsole::clearScr();
						airc.setWing(i->dataF,i->id);
						Window win;
						win.SetWidth(40).SetHeight(3).VCenter().HCenter();
						win.Show();
						win.Write(0, 0, "���i��� ������");
						_getch();
						funConsole::clearScr();
						});
					j++;
				}
				centerMenu.Select();
			}
			
			aircraftMenu.Select();
			});
	aircraftMenu.addItem("��������� �i������ ����(Y)", [this, &aircraftMenu, &airc]() {
		funConsole::clearScr();
		double Cy;
		int wS;
		if (!airc.getAeroProperties().empty()) {
			Cy= airc.getAeroProperties().getCy(0);
		}
		else {
			Cy = 0.1;
		}
		double density = Aerodynamics::Analytics::AtmosphereConstants::AIR_DENSITY;
		int vmin = airc.getVMin();
		if (airc.getWingObject().id+1) {
			wS = airc.getWing().getS();
		}
		else {
			wS = 0;
		}

		FunctionMenu centerMenu("���� ���������� Y", 1);
		centerMenu.SetHeight(10).SetWidth(35).HCenter().VCenter();
		centerMenu.addItem("�������� Y", [this,&airc, &centerMenu]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(3).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, (String)"Y = " + String(airc.getY(), 2).get()+(String)" H");
			_getch();
			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.addItem("�������� ��i��i ���i", [&centerMenu, &Cy,&density,&vmin,&wS ]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(6).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, (String)"Cy                        :" + String(Cy,2));
			win.Write(0, 1, (String)"�i���i���                 :" + String(density,3));
			win.Write(0, 2, (String)"�i�i������ �����i���(�/�) :" + String(vmin));
			win.Write(0, 3, (String)"����� �����(S)            :" + String(wS));
			_getch();
			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.addItem("��i���� Cy", [&centerMenu, &Cy]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(3).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, "����i�� Cy:");
			InputV2 in(6, win.GetX() + 12, win.GetY() + 1);
			in.process(1);
			Cy = ((String)in.get()).atof();
			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.addItem("��i���� �i���i��� ���i���", [&centerMenu,&airc, &density]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(3).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, "����i�� ���� �������(��):");
			InputV2 in(6, win.GetX() + 26, win.GetY() + 1);
			in.process(1);
			density = ((String)in.get()).atof();
			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.addItem("��i���� �i�i������ �����i���", [&centerMenu,&airc, &vmin]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(45).SetHeight(3).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, "����i�� �i�i������ �����i���(�/�):");
			InputV2 in(6, win.GetX() + 36, win.GetY() + 1);
			in.process(1);
			vmin = ((String)in.get()).atoi();
			airc.setVMin(vmin);
			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.addItem("��i���� ����� �����", [&centerMenu, &wS]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(3).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, "����i�� S(�^2):");
			InputV2 in(6, win.GetX() + 16, win.GetY() + 1);
			in.process(1, 0);
			wS = ((String)in.get()).atoi();
			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.addItem("���������", [&centerMenu,&airc, &Cy, &density, &wS]() {
			funConsole::clearScr();
			airc.evalY(Cy,density,wS);
			Window win;
			win.SetWidth(40).SetHeight(3).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, (String)"���� Y(H):" + String(airc.getY()));
			_getch();
			});
		centerMenu.Select();
		funConsole::clearScr();
		aircraftMenu.Select();
	});
	aircraftMenu.addItem("��������� �i�i������ �����i���", [this, &aircraftMenu, &airc]() {
		funConsole::clearScr();
		double Cy;

		int wS;
		if (!airc.getAeroProperties().empty()) {
			Cy = airc.getAeroProperties().getCy(0);
		}
		else {
			Cy = 0.1;
		}
		int G = airc.getG();
		double density = Aerodynamics::Analytics::AtmosphereConstants::AIR_DENSITY;
		int vmin = airc.getVMin();
		if (airc.getWingObject().id + 1) {
			wS = airc.getWing().getS();
		}
		else {
			wS = 0;
		}

		FunctionMenu centerMenu("���� ���������� Y", 1);
		centerMenu.SetHeight(10).SetWidth(35).HCenter().VCenter();
		centerMenu.addItem("�������� �i�i������ �����i��", [this, &airc, &centerMenu]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(3).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, (String)"V(min) = " + String(airc.getVMin(), 2).get() + (String)" �/�");
			_getch();
			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.addItem("�������� ��i��i ���i", [&centerMenu, &Cy, &density,&G, &vmin, &wS]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(6).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, (String)"Cy                        :" + String(Cy, 2));
			win.Write(0, 1, (String)"�i���i���                 :" + String(density, 3));
			win.Write(0, 2, (String)"���� ���i���(�)           :" + String(G));
			win.Write(0, 3, (String)"����� �����(S)            :" + String(wS));
			_getch();
			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.addItem("��i���� Cy", [&centerMenu, &Cy]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(3).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, "����i�� Cy:");
			InputV2 in(6, win.GetX() + 12, win.GetY() + 1);
			in.process(1);
			Cy = ((String)in.get()).atof();
			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.addItem("��i���� �i���i��� ���i���", [&centerMenu, &airc, &density]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(3).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, "����i�� ���� �������(��):");
			InputV2 in(6, win.GetX() + 26, win.GetY() + 1);
			in.process(1);
			density = ((String)in.get()).atof();
			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.addItem("��i���� ���� ���i���", [&centerMenu, &airc, &G]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(3).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, "����i�� ���� ���i���(�):");
			InputV2 in(6, win.GetX() + 25, win.GetY() + 1);
			in.process(1);
			G = ((String)in.get()).atoi();
			airc.setG(G);
			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.addItem("��i���� ����� �����", [&centerMenu, &wS]() {
			funConsole::clearScr();
			Window win;
			win.SetWidth(40).SetHeight(3).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, "����i�� S(�^2):");
			InputV2 in(6, win.GetX() + 16, win.GetY() + 1);
			in.process(1, 0);
			wS = ((String)in.get()).atoi();
			funConsole::clearScr();
			centerMenu.Select();
			});
		centerMenu.addItem("���������", [&centerMenu, &airc, &Cy, &density, &wS,&G]() {
			funConsole::clearScr();
			airc.evalVMin(Cy, density,G, wS);
			Window win;
			win.SetWidth(40).SetHeight(3).VCenter().HCenter();
			win.Show();
			win.Write(0, 0, (String)"���� V(min) = " + String(airc.getY(), 2) + String(" �/�"));
			_getch();
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

