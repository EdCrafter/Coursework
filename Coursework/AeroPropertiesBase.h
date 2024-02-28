#pragma once
#include "base.h"
#include "AeroProperties.h"

namespace Aerodynamics {
	namespace Data {

		class AeroPropertiesBase : public Aerodynamics::Data::base<Aerodynamics::Analytics::AeroProperties>
		{
			Aerodynamics::Data::Type t; int sizeM;
		public:
			AeroPropertiesBase(unsigned int id = 0) : base<Aerodynamics::Analytics::AeroProperties>(id) {}
			AeroPropertiesBase& read(char* file);
			bool save(char* file, Aerodynamics::Data::Format format = Aerodynamics::Data::Format::txt);
		};
	}
}