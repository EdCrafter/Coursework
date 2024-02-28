#pragma once
#include "base.h"
#include "wing.h"
namespace Aerodynamics {
	namespace Data {
		class WingBase : public Aerodynamics::Data::base<Aerodynamics::Data::Wing>
		{
			Aerodynamics::Data::Type t; int sizeM;
		public:
			WingBase(unsigned int id = 0) : base<Aerodynamics::Data::Wing>(id) {}
			WingBase& read(char* file, AeroPropertiesBase* apb);
			bool save(char* file, Aerodynamics::Data::Format format = Aerodynamics::Data::Format::txt);
		};
	}
}
