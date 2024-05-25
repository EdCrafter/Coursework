#pragma once
#include "base.h"
#include "aircraft.h"
#include "wing.h"
#include "AeroProperties.h"
namespace Aerodynamics {
	namespace Data {
	
		class AircraftBase : public Aerodynamics::Data::base<Aerodynamics::Data::Aircraft>
		{
			Aerodynamics::Data::Type t; 
			int sizeM;
		public:
			AircraftBase(unsigned int id = 0) : Aerodynamics::Data::base<Aerodynamics::Data::Aircraft>(id) {
				
			}

			AircraftBase& read(char* file, WingBase*, AeroPropertiesBase*);
			bool save(char* file, Format format = txt);
			AircraftBase& sort(Parametrs param);
			AircraftBase& sortAdr(int h, int u, typename std::list<Object>::iterator l, typename std::list<Object>::iterator r);


		};

	}
}