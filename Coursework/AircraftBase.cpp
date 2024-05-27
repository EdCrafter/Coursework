#include "AircraftBase.h"
namespace Aerodynamics {
	namespace Data {

		
		bool AircraftBase::save(char* file, Format format )
		{
			if (!(*this).size()) return false;
			fstream fileP;
			if (!fileP) {
				return false;
			}
			String folder = "AircraftBases";
			
			typename std::list<Object>::iterator i;
			int idW,idAP;
			if (format == txt) {
				String subfolder = "txt";
				String fullPath = folder + "/" + subfolder + "/" + file + ".txt";
				#ifdef _WIN32
						if (!std::filesystem::exists((folder + "/" + subfolder).get())) {
							std::system(("mkdir " + folder).get());
							std::system(("mkdir " + folder + "\\" + subfolder).get());
						}
				#else
						if (!std::filesystem::exists((folder + "/" + subfolder).get())) {
							std::system(("mkdir -p " + folder + "/" + subfolder).c_str());
						}
				#endif
				fileP.open(fullPath.get(), ios::binary | ios::out);
				for (i = dataFs.begin(); i != dataFs.end(); i++) {
					idW = i->dataF.getWingObject().id;
					
					idAP =  i->dataF.getAPObject().id;
					
					fileP << i->id<<" " << i->dataF.getName() << " " << i->dataF.getD() << " " ;
					fileP << i->dataF.getX() << " " << i->dataF.getY() << " " << i->dataF.getG() << " " << i->dataF.getAlignment() << " ";
					fileP << i->dataF.getL()  << " " << idW << " " << idAP << "\n";
				}
			}
			else if (format == html) {
				String subfolder = "HTML";
				String fullPath = folder + "/" + subfolder + "/" + file + ".html";
				#ifdef _WIN32
						if (!std::filesystem::exists((folder + "/" + subfolder).get())) {
							std::system(("mkdir " + folder).get());
							std::system(("mkdir " + folder + "\\" + subfolder).get());
						}
				#else
						if (!std::filesystem::exists((folder + "/" + subfolder).get())) {
							std::system(("mkdir -p " + folder + "/" + subfolder).c_str());
						}
				#endif
				fileP.open(fullPath.get(), ios::binary | ios::out);
				fileP << "<!DOCTYPE html><html lang = \"en\" ><head><meta charset = \"UTF-8\"><meta name = \"viewport\" content = \"width=device-width, initial-scale=1.0\"><title>Aircraft Base</title>";
				fileP << "<style>table {font - family: Arial, sans - serif;border - collapse: collapse;width: 100 %;}th, td{ border: 1px solid #dddddd;";
				fileP << "text - align: left;padding: 8px;}th{background - color: #f2f2f2;}tr:nth - child(even) {background - color: #f2f2f2;}</style></head><body>";
				fileP << "<table><tr><th>Aircraft ID</th><th>Aircraft Name</th><th>Traction force(H)</th><th>Head resistance(H)</th>"; 
				fileP << "<th>Lifting force(H)</th><th>Weight(kg)</th><th>Alignment</th><th>Len(m)</th><th>Wing ID</th><th>Aero Properties ID</th></tr>"; 
				for (i = dataFs.begin(); i != dataFs.end(); i++) {
					if (i->dataF.getWingObject().dataF.getName() != "") {
						idW = i->dataF.getWingObject().id;
					}
					else {
						idW = -1;
					}
					if (i->dataF.getAPObject().dataF.getVectorAK()->size()) {
						idAP = i->dataF.getAPObject().id;
					}
					else {
						idAP = -1;
					}
					fileP <<"<tr><td>"<< i->id << "</td><td>" << i->dataF.getName() <<  "</td><td>" << i->dataF.getD() << "</td><td>";
					fileP << i->dataF.getX() <<  "</td><td>" << i->dataF.getY() <<  "</td><td>" << i->dataF.getG() <<  "</td><td>" << i->dataF.getAlignment() << "</td><td>";
					fileP << i->dataF.getL() <<  "</td><td>" << idW <<  "</td><td>" << idAP << "</td></tr>";
				}
				fileP << "</table>";
				fileP << "</body><html>";
			}
			else {
				throw exception("Undefined format");
			}
			fileP.close();
			return true;
		}
			
		
	
			

		AircraftBase& AircraftBase::read(char* file,WingBase* wb, AeroPropertiesBase* apb)
		{
			unsigned int id;
			string name;
			double D, X, Y, G,x, l;
			int wingId, apId;
			fstream fileP;
			std::string fileName = "AircraftBases/txt/" + (string)file;
			fileP.open(fileName, ios::binary | ios::in);

			if (!fileP) {
				std::cerr << "Не удалось открыть файл для чтения: " << file << std::endl;
				return *this;
			}

			dataFs.clear();
			while (fileP >> id >> name >> D >> X >> Y >> G >> x >> l >> wingId >> apId)
			{
				Aircraft a(name, l, D, X, Y, G);
				a.setAlignment(x);
				if (wingId + 1) {
					a.setWingID(wingId, wb);
				}
				if (apId + 1) {
					a.setAeroPropertiesID(apId, apb);
				}
				Object newObj(id, a);
				dataFs.push_back(newObj);	
			}
			fileP.close();
			
			return *this;
		}

		AircraftBase& AircraftBase::sort(Parametrs param)
		{
			sizeM=0;
			int type = 0;
			switch (param)
			{
			case Aerodynamics::Data::pname:
				sizeM += sizeof(Aerodynamics::Data::WingBase::Object)+ sizeof(AeroPropertiesBase::Object);
			case Aerodynamics::Data::pwingN:
				sizeM += sizeof(double);
				type++;
			case Aerodynamics::Data::pv:
				sizeM += sizeof(double);
			case Aerodynamics::Data::pl:
				sizeM += sizeof(double);
			case Aerodynamics::Data::px:
				sizeM += sizeof(double);
			case Aerodynamics::Data::pG:
				sizeM += sizeof(double);
			case Aerodynamics::Data::pY:
				sizeM += sizeof(double);
			case Aerodynamics::Data::pX:
				sizeM += sizeof(double);
			case Aerodynamics::Data::pD:
				break;
			}
			if (type == 2) {
				t = tString;
			}
			else if (type == 1) {
				t = tWing;
			}
			else {
				t = tDouble;
			}
			 typename std::list<Object>::iterator l = dataFs.begin();
			 typename std::list<Object>::iterator r = dataFs.end();
			r--;
			int ls = dataFs.size()-1;
			sortAdr(0,ls,l,r);
			return *this;
		}
		AircraftBase& AircraftBase::sortAdr(int h,int u, typename std::list<Object>::iterator l,  typename std::list<Object>::iterator r){
			int i, j;
			 typename std::list<Object>::iterator f = l;
			 typename std::list<Object>::iterator e = r;
			Object y;
			i = h; j = u;
			if (t == tDouble) {
				double x;
				x = *(double*)((int)&((*l).dataF)+sizeM);
				do
				{
					while ((*(double*)((int)&((*f).dataF)+sizeM) < x) && (i < u)) {
						i++;
						f++;
					}
					while ((x < *(double*)((int)&((*e).dataF) +sizeM)) && (j > h)) {
						j--;
						e--;
					}
					if (i <= j)
					{
						y = (*f);
						(*f) = (*e);
						(*e) = y;
						i++; j--;
						if (f != r ){ f++; }
						if( e != l) {
							e--;
						}
					}
				} while (i <= j);
			}
			else {
				string x;

				x = *((string*)((int)&((*l).dataF) + sizeM));
				do{
					while (i < u) {
						string ss = (*((string*)((int)&((*f).dataF) + sizeM)));
						if (ss.compare(x.c_str()) < 0) {
							i++;
							f++;
						}
						else {
							break;
						}
					}
					while (j > h) {
						string ss = *((string*)((int)&((*e).dataF) + sizeM));
						if (ss.compare(x.c_str()) > 0) {
							j--;
							e--;
						}
						else {
							break;
						}
					}
					if (i <= j)
					{
						y = (*f);
						(*f) = (*e);
						(*e) = y;
						i++; j--;
						if (f != r) { 
							f++; 
						}
						if (e != l) {
							e--;
						}
					}
				} while (i <= j);
			}
		
	
			if (h < j) sortAdr(h, j,l,e);
			if (i < u) sortAdr(i, u,f,r);
			return *this;
		}
	}
}