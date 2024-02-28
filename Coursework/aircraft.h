#pragma once
#include "aerodynamics.h"
#include "WingBase.h"
#include "AeroPropertiesBase.h"
namespace Aerodynamics {
	namespace Data {
		class Aircraft
		{
			double D,X,Y,G; // powers
			double x,l;
			double vMin;
			WingBase::Object wing;
			AeroPropertiesBase::Object ap;
			string name;
		public:
			Aircraft(string name = "Aircraft",double l = 0, double D = 0, double X = 0, double Y = 0, double G = 0) : name(name), l(l), D(D), X(X), Y(Y), G(G) {
				if (l >= 0) {
					x = l / 2;
				}
				else {
					throw logic_error("Aircraft len must be more than 0");
				}
			}
			Aircraft& evalAlignment(double distance ,  double cargoG, double G = 0, bool tail = true , double MAC = 0,double _x = 0.5) {
				if (!MAC) {
					MAC = wing.dataF.getMAC();
				}
				x = (_x+pow(-1,(!tail))*(cargoG* distance /(G+cargoG))) / MAC;
				return *this;
			}
			Aircraft& setAlignment(double x) {
				if (x >= 0 && x<=1) {
					this->x = x;
				}
				return *this;
				
			}
			double getAlignment() {
				return x;
			}
			double getVMin() {
				return vMin;
			}
			double getM(double v =0,double a = Analytics::AtmosphereConstants::SPEED_OF_SOUND) {
				return v/a;
			}
			Aircraft& setVMin(double _v) {
				if (vMin < 0) {
					vMin = -vMin;
				}
				vMin = _v;
				return *this;
			}
			Aircraft& setAeroProperties(Analytics::AeroProperties _ap) {
				ap.dataF = _ap;
				return *this;
			}
			Aircraft& setAeroPropertiesID(unsigned int id , AeroPropertiesBase* apb) {
				ap = apb->getAtID(id);
				return *this;
			}
			Analytics::AeroProperties& getAeroProperties() {
				return ap.dataF;
			}
			double getK(double angle) {
				return ap.dataF.getK(angle);
			}
			double Vmin(double CyMax, double density, double G, double S) {
				double v;
				v = sqrt(2 * G / (CyMax * density * S));
				return v;
			}
			bool uniformMove(double eps = 10000) {

				if (abs(D - X) + eps > 0 && abs(Y - G) + eps > 0) {
					return true;
				}
				return false;
			}

			Aircraft& setWing(Wing _wing) {
				wing.dataF = _wing;
				return *this;
			}
			Aircraft& setWingID(unsigned int id ,WingBase* _wing) {
				wing = _wing->getAtID(id);
				return *this;
			}
			Aircraft& setL(double l) {
				if (l > 0) {
					this->l = l;
				}
				else {
					throw logic_error("Aircraft len must be more than 0");
				}
				return *this;
			}
			bool operator == (Aircraft& airc) {
				if (airc.wing.dataF == this->wing.dataF && airc.G == this->G && airc.l == this->l && airc.ap.dataF == this->ap.dataF) {
					return true;
				}
				
				return false;
				
			}
			double getD() {
				return D;
			}
			double getG() {
				return G;
			}
			double getX() {
				return X;
			}
			double getY() {
				return Y;
			}
			double getL() {
				return l;
			}
			Wing getWing() {
				return wing.dataF;
			}
			string getName() {
				return name;
			}
			WingBase::Object getWingObject() {
				return wing;
			}
			AeroPropertiesBase::Object getAPObject() {
				return ap;
			}
		};
	}
}
