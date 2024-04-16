#include "AeroPropertiesBase.h"
#include "AeroProperties.h"
namespace Aerodynamics {
	namespace Data {


		bool AeroPropertiesBase::save(char* file, Format format)
		{
			if (!(*this).size()) return false;
			fstream fileP;
			fileP.open(file, ios::binary|ios::out);
			typename std::list<Object>::iterator i;
			if (format == txt) {
				for (i = dataFs.begin(); i != dataFs.end(); i++) {
					fileP << i->id << " " << i->dataF.getVectorAK()<< "\n";
				}
			}
			else if (format == html) {
				fileP << "<!DOCTYPE html><html lang = \"en\" ><head><meta charset = \"UTF-8\"><meta name = \"viewport\" content = \"width=device-width, initial-scale=1.0\"><title>Aircraft Base</title>";
				fileP << "<style>table {font - family: Arial, sans - serif;border - collapse: collapse;width: 100 %;}th, td{ border: 1px solid #dddddd;";
				fileP << "text - align: left;padding: 8px;}th{background - color: #f2f2f2;}tr:nth - child(even) {background - color: #f2f2f2;}</style></head><body>";
				fileP << "<table><tr><th>Aero Properties ID</th><th>Address aero qualities base</th></tr>";
				for (i = dataFs.begin(); i != dataFs.end(); i++) {
					fileP << "<tr><td>" << i->id << "</td><td>" << i->dataF.getVectorAK() << "</td></tr>";
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





		AeroPropertiesBase& AeroPropertiesBase::read(char* file)
		{
			unsigned int id;
			int addrV;

			fstream fileP;
			fileP.open(file, ios::binary|ios::in);

			if (!fileP) return *this;

			dataFs.clear();
			while (fileP >> id >> addrV)
			{
				if (fileP.eof())break;
				Aerodynamics::Analytics::AeroProperties a;
				vector<Aerodynamics::Analytics::AeroQuality>* i = (vector<Aerodynamics::Analytics::AeroQuality>*)addrV;
				a.set(*i);
			
				Object newObj(id, a);
				dataFs.push_back(newObj);
			}
			fileP.close();
			return *this;
		}

		
		
	}
}