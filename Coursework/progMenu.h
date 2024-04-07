#pragma once
#include "AircraftBase.h"
#include "Window.h"
#include "Input.h"
namespace Aerodynamics{
	namespace UI {
		class progMenu
		{
			Aerodynamics::Data::AircraftBase aircB;
			Aerodynamics::Data::WingBase wingB;
			Aerodynamics::Data::AeroPropertiesBase apB;
		public:
			progMenu() = default;
			progMenu& start();
			progMenu& wingMenu();
			progMenu& aircraftMenu();
		};
	}
}
