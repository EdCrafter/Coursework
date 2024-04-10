
#pragma once
#include <string.h>
#include <iostream>
#include "aerodynamics.h"

namespace Aerodynamics {
	namespace Data {
		class String {
			char* str;
		public:
			String(String& s) { str = 0; add(s.str); }
			String(const String& s) { str = 0; add(s.str); }
			String(const char* s = 0) { str = 0; add(s); }
			String(char c, size_t len);
			String(int i) { 
				str = 0; 
				int l = Aerodynamics::Analytics::length(i);
				char* s = new char[l + 1];
				sprintf_s(s, l + 1, "%d", i);
				add(s);
			}
			String(double d,unsigned int n =0) { 
				str = 0;

				int l = Aerodynamics::Analytics::length(d,n);
				if (!n)  l -= 1;
				char *s = new char[l + n+2];
				String format = (String)"%."+String((int)n)+"lf";
				sprintf_s(s,l+n+2,format.get(), d);
				add(s); 
			}
			~String() { empty(); }
			const char* get() { return (str) ? str : ""; }
			size_t length() { return strlen(get()); }
			String& empty() { delete str; str = 0; return *this; }

			String& add(const char* s);
			String& add(string& s);
			String& add(String& s) { return add(s.str); }
			String& set(String& s) { empty(); return add(s.str); }
			String& operator = (String& s) { empty();  return add(s.str); }
			String& operator = (const String& s) { empty();  return add(s.str); }
			String& operator = (const char* s) { empty();  return add(s); }
			
			String& operator += (String& s) { return add(s.str); }
			String& operator += (const char* s) { return add(s); }

			String& operator << (String& s) { return add(s.str); }
			String& operator << (const char* s) { return add(s); }

			char& operator [](size_t i) { return ((char*)get())[i]; }
			operator const char* () { return get(); }

			int compare(const char* s1) { return strcmp(get(), s1); }

			bool operator ==(String& s1) { return compare(s1.get()) == 0; }
			bool operator ==(const char* s1) { return compare(s1) == 0; }
			bool operator !=(String& s1) { return compare(s1.get()) != 0; }
			bool operator !=(const char* s1) { return compare(s1) != 0; }

			bool operator !() { return length() == 0; }

			bool operator >(String& s1) { return compare(s1.get()) > 0; }
			bool operator >(const char* s1) { return compare(s1) > 0; }
			bool operator <(String& s1) { return compare(s1.get()) < 0; }
			bool operator <(const char* s1) { return compare(s1) < 0; }


			String operator + (const char* s) { return String(get()).add(s); }
			String operator + (String& s2) { return String(get()).add(s2); }
			friend String operator + (const char* s1, String& s2);
			friend std::ostream& operator << (std::ostream& c, String& s);
			//
			String& operator += (char s) { char str[2] = { s, 0 };  return add(str); };
			String& remove(size_t pos, size_t count);
			String& removeAt(size_t pos) { return remove(pos, 1); };
			String& insert(size_t pos, const char*);
			String& insertAt(size_t pos, char a) { char s[2] = { a,0 }; return insert(pos, s); };
			bool find(const char*);
			void reverse();
			void countCharacters();
			String& toLower() {
				int i = 0;
				while (i < length()) {
					str[i] |= (1 << 5);
					i++;
				}
				return *this;
			}
			bool hasCapitalLetter();
			int atoi();
			double atof();
			String& setSize(size_t len) {
				size_t l = length();
				if((l+len)%2) add(" ");
				String s = String(' ', (len - l) / 2);
				add(s);
				s.add(str);
				set(s);
				return *this;
			}
		};
	}
};