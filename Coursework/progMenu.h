#pragma once
#include "AircraftBase.h"
#include "Window.h"
#include "Input.h"
#include <filesystem>
using namespace Aerodynamics::Data;
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
			progMenu& wingsMenu();
			progMenu& aircraftsMenu();
			progMenu& wingMenu(Wing&wing, unsigned int j);
			progMenu& aircraftMenu(Aircraft& airc, unsigned int j);
		};
	}
}
