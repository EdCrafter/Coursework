#pragma once
#include "aerodynamics.h"
#include "AeroProperties.h"
#include "AeroPropertiesBase.h"
namespace Aerodynamics {
	namespace Data {
		class Wing
		{
			string name;
			double MAC, l,S;
			AeroPropertiesBase::Object ap;
		public:
			Wing() = default;
			Wing(string name,double MAC = 0, double l = 0, double S = 0) :name(name), MAC(MAC),l(l), S(S) {}
			double Vmin(double CyMax, double density, double G, double S) {
				double v;
				v = sqrt(2 * G / (CyMax * density * S));
				return v;
			}
			double getMAC() {
				return MAC;
			}
			double getL() {
				return l;
			}
			double getS() {
				return S;
			}
			string getName() {
				return name;
			}
			Analytics::AeroProperties& getAeroProperties() {
				return ap.dataF;
			}
			AeroPropertiesBase::Object getAeroPropertiesObj() {
				return ap;
			}
			Analytics::AeroProperties getAeroPropertiesID(unsigned int id) {
				return ap.dataF;
			}
			Wing& setMAC(double _bAv) {
				if (_bAv > 0) {
					MAC = _bAv;
				}
				else {
					throw logic_error("The average back must be more than zero");
				}
				return *this;
			}
			Wing& setAeroProperties(Analytics::AeroProperties _ap) {
				ap.dataF = _ap;
				return *this;
			}
			Wing& setAeroPropertiesID(unsigned int id,AeroPropertiesBase* _ap) {
				ap = _ap->getAtID(id);
				return *this;
			}
			bool operator ==  (Wing& w){
				if (w.ap.dataF == this->ap.dataF && w.MAC == this->MAC && w.l == this->l && w.S == this->S) {
					return true;
				}
		
				return false;
				
			}
			Wing& operator = (Wing& w) {
				name = w.name;
				MAC = w.MAC;
				l = w.l;
				S = w.S;

				return* this;
			}
			Wing& setL(double _l) {
				if (_l > 0) {
					l = _l;
				}
				else {
					throw logic_error("The length must be more than zero");
				}
				return *this;
			}
			Wing& setS(double _S) {
				if (_S > 0) {
					S = _S;
				}
				else {
					throw logic_error("The area must be more than zero");
				}
				return *this;
			}
			Wing& setName(string _name) {
				name = _name;
				return *this;
			}
		};
	}
}

