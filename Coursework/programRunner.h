#pragma once
#include "aerodynamics.h"
#include "AeroPropertiesBase.h"
#include "WingBase.h"
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
		setlocale(0, ".1251");
		FunctionMenu myInterface("√ŒÀŒ¬Õ≈ Ã≈Õﬁ", 1);
		myInterface.SetHeight(5).SetWidth(20).HCenter().VCenter();
		myInterface.addItem("1", [this, &myInterface]() {
			if (1) {
				::SetColor(White, Black);
				cls();
				Window w;
				w.SetWidth(20).SetHeight(3).SetColor(Green).SetBgColor(Yellow).VCenter().HCenter();
				w.Show();
				w.Write(0, 0, "User created");
			}
			_getch();
			::SetColor(White, Black);
			cls();
			myInterface.Select();
			});
		myInterface.addItem("œ≥‰≥‚˛Èø", [this, &myInterface]() {
			if (1) {
				::SetColor(White, Black);
				cls();
				Window w;
				w.SetWidth(30).SetHeight(3).SetColor(Green).SetBgColor(Yellow).VCenter().HCenter();
				w.Show();
				w.Write(0, 0, "Error user name or password");
				_getch();
			}
			::SetColor(White, Black);
			cls();
			myInterface.Select();
			});
		myInterface.Select();
		return *this;
	}
};

