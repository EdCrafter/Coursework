#include "AircraftBase.h"
#include "wing.h"
#include <iostream>

int main() {
	
	Aerodynamics::Data::AircraftBase ab;

	Aerodynamics::Data::Aircraft airc("l",1,11,6,5,4);
	Aerodynamics::Data::Wing w("eee",1,1,1);
	airc.setWing(w);
	ab.add(airc);
	Aerodynamics::Data::Aircraft airc6("n",4,7,0,0,2);
	Aerodynamics::Data::Wing w1("aaa",1,1,1);
	airc6.setWing(w1);
	ab.add(airc6);
	Aerodynamics::Data::Aircraft airc2("m",3,4,-1,9,3);
	Aerodynamics::Data::Wing w2("bbb",1,1,1);
	airc2.setWing(w2);
	ab.add(airc2);
	Aerodynamics::Data::Aircraft airc1("a",2,6,22,-7,1);
	Aerodynamics::Data::Wing w3("ccc",1,1,1);
	airc1.setWing(w3);
	ab.add(airc1);
	ab.sort(Aerodynamics::Data::pname);
	char f[7] = "1.html";
	ab.save(f,Aerodynamics::Data::html);
	

	return 0;
}