#pragma once

#include "aerodynamics.h"
namespace Aerodynamics {
	enum typeATM
	{
		Troposphere,
		Stratosphere,
		Mesosphere,
		Thermosphere,
		Exosphere,
		Unknown
	};
	namespace Analytics {
		class Atmosphere
		{
			double p, density, T;
		public:
			Atmosphere() {
				T = AtmosphereConstants::SEA_LEVEL_TEMPERATURE;
				p = AtmosphereConstants::SEA_LEVEL_PRESSURE;
				density = AtmosphereConstants::AIR_DENSITY;
			}
			typeATM getLayerATMbyDensity(double airDensity = AtmosphereConstants::TROPOSPHERE_DENSITY){
				if (airDensity > AtmosphereConstants::TROPOSPHERE_DENSITY) {
					return Troposphere;
				}
				else if (airDensity > AtmosphereConstants::STRATOSPHERE_DENSITY) {
					return Stratosphere;
				}
				else if (airDensity > AtmosphereConstants::MESOSPHERE_DENSITY) {
					return Mesosphere;
				}
				else if (airDensity > AtmosphereConstants::THERMOSPHERE_DENSITY) {
					return Thermosphere;
				}
				else if (airDensity > AtmosphereConstants::EXOSPHERE_DENSITY) {
					return Exosphere;
				}
				else {
					return Unknown; 
				}
			};
			double getTempInH(double h){
				return AtmosphereConstants::SEA_LEVEL_TEMPERATURE - 0,0065 * h;
			}
			Atmosphere& setParam(typeATM sphere,double h) {
				if (sphere == Troposphere) {
					T = AtmosphereConstants::SEA_LEVEL_TEMPERATURE - 0.0065 * h;
					p = AtmosphereConstants::SEA_LEVEL_PRESSURE*pow(1-h/44300,5.256);
					density = AtmosphereConstants::AIR_DENSITY * pow(1-h/44300,4.256);
				}
				else if (sphere == Stratosphere) {
					T = AtmosphereConstants::SEA_LEVEL_TEMPERATURE - 0.0065 * h;
					p = 169.4 * exp(-((h-11000)/64340));
					density = 0.3636 * exp(-((h - 11000) / 64340));
				}
				else if (sphere == Mesosphere) {
					T = 163.15;
					density = AtmosphereConstants::MESOSPHERE_DENSITY;
					p = 0;
				}
				else if (sphere == Thermosphere) {
					T = 1773.15;
					density = AtmosphereConstants::THERMOSPHERE_DENSITY;
					p = 0;
				}
				else if (sphere == Exosphere) {
					T = 2773.15;
					density = AtmosphereConstants::EXOSPHERE_DENSITY;
					p = 0;
				}
				else {
					throw logic_error("You leave atmosphere");
				}
				return *this;
			}
			double getP() {
				return p;
			}
			double getDensity() {
				return density;
			}
			double getT() {
				return T;
			}
			double getTInCelcium() {
				return T + 273.15;
			}
			double evalA(double _T = AtmosphereConstants::SEA_LEVEL_TEMPERATURE) {
				return 20*sqrt(_T);
			}
		};

	}
}

