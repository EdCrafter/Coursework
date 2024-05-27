#include "AeroPropertiesBase.h"
#include "AeroProperties.h"
#include <string>
#include <sstream>
namespace Aerodynamics {
	namespace Data {


		bool AeroPropertiesBase::save(char* file, Format format)
		{
			if (!(*this).size()) return false;
			fstream fileP;
			if (!fileP) {
				return false;
			}
			String folder = "AeroPropertiesBases";


			typename std::list<Object>::iterator i;
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
					fileP << i->id << "\n";
					auto end = i->dataF.getVectorAK()->end();
					for (auto j = i->dataF.getVectorAK()->begin(); j != end; j++) {
						fileP << j->Cx << " " << j->Cy << " " << j->a << "\n";
					}
					fileP<< "\n";
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
			double Cx,Cy,ang;
			string line;
			fstream fileP;
			std::string fileName = "AeroPropertiesBases/txt/" + (string)file;
			fileP.open(fileName, ios::binary|ios::in);

			if (!fileP) return *this;

			dataFs.clear();
			while (std::getline(fileP, line)) {
				if (line.empty()) {
					continue; // Пропускаем пустые строки
				}
				id = std::stoi(line); // Читаем ID
				Aerodynamics::Analytics::AeroProperties a;
				while (std::getline(fileP, line) && !line.empty()) {
					std::istringstream iss(line);
					iss >> Cx >> Cy >> ang;
					a.add(Cx,Cy,ang);
				}
				Object newObj(id, a);
				dataFs.push_back(newObj);
				this->idLast = id;
			}

			fileP.close();
			
			return *this;
		}

		
		
	}
}