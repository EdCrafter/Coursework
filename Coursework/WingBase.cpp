#include "WingBase.h"
namespace Aerodynamics {
	namespace Data {


		bool WingBase::save(char* file, Format format)
		{
			if (!(*this).size()) return false;
			fstream fileP;
			fileP.open(file, ios::binary|ios::out);
			typename std::list<Object>::iterator i;
			if (format == txt) {
				for (i = dataFs.begin(); i != dataFs.end(); i++) {
					fileP << i->id << " " << i->dataF.getName() << " " << i->dataF.getMAC() << " ";
					fileP << i->dataF.getL() << " " << i->dataF.getS() << " " << i->dataF.getAeroPropertiesObj().id <<"\n";
				}
			}
			else if (format == html) {
				fileP << "<!DOCTYPE html><html lang = \"en\" ><head><meta charset = \"UTF-8\"><meta name = \"viewport\" content = \"width=device-width, initial-scale=1.0\"><title>Wing Base</title>";
				fileP << "<style>table {font - family: Arial, sans - serif;border - collapse: collapse;width: 100 %;}th, td{ border: 1px solid #dddddd;";
				fileP << "text - align: left;padding: 8px;}th{background - color: #f2f2f2;}tr:nth - child(even) {background - color: #f2f2f2;}</style></head><body>";
				fileP << "<table><tr><th>Wing ID</th><th>Wing Name</th><th>Mean Aerodynamic Chord(m)</th><th>Len(m)</th>";
				fileP << "<th>Wing Area(sq m)</th><th>Aero Properties ID</th></tr>";
				for (i = dataFs.begin(); i != dataFs.end(); i++) {
					fileP << "<tr><td>" << i->id << "</td><td>" << i->dataF.getName() << "</td><td>" << i->dataF.getMAC() << "</td><td>";
					fileP << i->dataF.getL() << "</td><td>" << i->dataF.getS() << "</td><td>" << i->dataF.getAeroPropertiesObj().id <<"</td></tr>";
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





		WingBase& WingBase::read(char* file, AeroPropertiesBase* apb)
		{
			unsigned int id;
			string name;
			double MAC,l, S;
			unsigned int apId;
			fstream fileP;
			fileP.open(file, ios::binary|ios::in);

			if (!fileP) return *this;

			dataFs.clear();
			while (fileP >> id >> name >>MAC>> l >>S>> apId)
			{
				if (fileP.eof())break;
				Wing w(name, MAC, l, S);
				w.setAeroPropertiesID(apId, apb);
				Object newObj(id, w);
				dataFs.push_back(newObj);
			}
			fileP.close();
			return *this;
		}

		
	}
}