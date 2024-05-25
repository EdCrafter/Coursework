#pragma once
#include "aerodynamics.h"
#include <list>
#include <fstream>
#include <conio.h>
#include <iostream>
#include "String.h"

namespace Aerodynamics {
	namespace Data {
		enum Parametrs
		{
			pD, pX, pY, pG ,px, pl,pv,pwingN,pname
		};
		enum Format {
			txt ,
			html
		};
		enum Type {
			tDouble,tWing,tString
		};
		template <class T>
		class base
		{
		public:
			struct Object {
				unsigned int id;
				T dataF;
				Object() {
					id = -1;
				}
				Object(unsigned int id, T dataF) : id(id), dataF(dataF) {}
			};

		protected:

			unsigned int idLast;
			
			std::list<Object> dataFs;

		public:

			base(unsigned int id=0) : idLast(id) {
				
			}
			Object& operator [](int i) { return getAt(i); }
			base<T>& add(T a){
				if (!find(a)) {
					Object newObj(idLast, a);
					dataFs.push_back(newObj);
					idLast++;
				}
				return *this;
			}
			bool serchID(unsigned int id) {
				
				typename std::list<Object>::iterator i;
				for (i = dataFs.begin(); i != dataFs.end(); i++)
					if (i->id == id) return true;
				return false;
			}
			int size() {
				return dataFs.size();
			}
			Object& getData(unsigned int id) {
				typename std::list<Object>::iterator i;
				for (i = dataFs.begin(); i != dataFs.end(); i++)
					if (i->id == id) return (T&)(*i);
				return (Object&)(*i);
			}
			Object& getAt(int idx) {
				int l;
				typename std::list<Object>::iterator iter;
				iter = dataFs.begin();
				for (l = 0; l < idx; iter++, l++);
				return (Object&)(*iter);
			}
			base<T>& del() {
				dataFs.clear();
				return *this;
			}
			base<T>& remove(unsigned int id) {
				 typename std::list<Object>::iterator i;
				
				if (dataFs.size() == 1)
				{
					dataFs.clear();
					return *this;
				}
				for (i = dataFs.begin(); i != dataFs.end(); i++)
					if (i->id == id) { dataFs.erase(i); break; }
				return *this;
			}
			unsigned int getIDLast() {
				return idLast;
			}
			virtual bool save(char* file , Format format = txt) = 0;
			bool find(T& data) {
				typename std::list<Object>::iterator r = dataFs.end();
				
				for ( typename std::list<Object>::iterator i = dataFs.begin(); i != r; i++) {
					if (i->dataF == data) {
						return true;
					}
				}
				return false;
			}
			Object& getAtID(unsigned int idx) {
				if (idx<0 || idx>idLast || dataFs.empty()) {
					throw range_error("Error id");
				}
				typename std::list<Object>::iterator r = dataFs.end();
				for ( typename std::list<Object>::iterator i = dataFs.begin(); i != r; i++) {
					if (i->id == idx) {
						return *i;
					}
				}
				throw range_error("Error id");
			}
			std::list<Object>& getObjects() {
				return dataFs;
			}

		};

		
		

	}
}

