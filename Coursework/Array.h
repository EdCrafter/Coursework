
#pragma once
namespace Aerodynamics {
	namespace Data {
		template<class T>
		class Array
		{
			T* ar;
			unsigned int count, size, grow;
		public:
			Array(unsigned int g = 10);

			Array(Array& copy) { ar = nullptr; Copy(copy); }

			~Array() { SetSize(0); }

			unsigned int GetCount() { return count; }
			unsigned int GetSize() { return size; }
			unsigned int GetGrow() { return grow; }
			T& operator [](unsigned int i) { return ar[i]; }
			Array& operator = (Array& copy) { ar = nullptr; return Copy(copy); }

			Array& operator<< (Array& copy) { return Copy(copy); }
			//

			Array& SetSize(unsigned int s);
			Array& Copy(Array& copy);

			//todo
			Array& Add(Array& arr);
			void RemoveAt(unsigned int);
			Array& Slice(unsigned int start, unsigned int finish);
			Array& SubArray(unsigned int i, unsigned int _count);
			int FindIndex(T);
			int* FindMin();
			//

			Array& Add(T v) {
				if (size == count) { SetSize(size + grow); }
				ar[count++] = v;
				return *this;
			}
			Array(T* arr, int sizeAr, unsigned int g = 10) {
				if (g == 0) g = 5;
				grow = g;
				count = 0;
				size = grow;
				ar = 0;
				SetSize(size);
				for (unsigned int i = 0; i < sizeAr; i++)
				{
					if (size == count) { SetSize(size + grow); }
					ar[count++] = arr[i];
				}

			}
			Array& RemoveAll() { count = 0; return *this; }
			Array& FreeExtra() { SetSize(GetCount());  return *this; }
			bool checkingIndex(unsigned int i) {
				return (i < count);
			}
		};

		template<class T>
		Array<T>::Array(unsigned int g) {
			if (g == 0) g = 5;
			grow = g;
			count = 0;
			size = grow;
			ar = 0;
			SetSize(size);
		}

		template<class T>
		Array<T>& Array<T>::Copy(Array& copy) {
			SetSize(0);
			SetSize(copy.GetCount());
			count = copy.GetCount();
			grow = copy.GetGrow();
			for (unsigned int i = 0; i < count; i++)
				ar[i] = copy[i];
			return *this;
		}

		template<class T>
		Array<T>& Array<T>::SetSize(unsigned int s) {
			size = s;
			if (size < count) count = size;
			if (s == 0) {
				delete[]ar;
				ar = 0;
				return *this;
			}
			T* arNew = new T[size];
			if (ar) {
				for (unsigned int i = 0; i < count; i++)
					arNew[i] = ar[i];
				delete[] ar;
			}
			ar = arNew;
			return *this;
		}

		template<class T>
		Array<T>& Array<T>::Add(Array& arr) {
			int newCount = count + arr.GetCount();
			int prCount = count;
			SetSize(size + arr.GetSize());
			for (unsigned int i = count; i < (unsigned int)newCount; i++)
				ar[i] = arr[i - count];
			count = newCount;
			return *this;
		}

		template<class T>
		void Array<T>::RemoveAt(unsigned int ind) {
			if (ind >= count) {
				return;
			}
			for (unsigned int i = ind; i < count - 1; i++) {
				ar[i] = ar[i + 1];
			}
			count--;
			return;
		}

		template<class T>
		Array<T>& Array<T>::Slice(unsigned int start, unsigned int finish) {
			int newCount = finish - start + 1;
			if (newCount <= 0 || start > count || finish > count || finish < 0 || start < 0) { return *this; }

			Array<T>* a = new Array<T>;
			T* arNew = new T[newCount];
			a->ar = arNew;
			a->count = newCount;
			a->SetSize(newCount);
			for (unsigned int i = 0; i < newCount; i++) {
				a->ar[i] = ar[start + i];
			}

			return *a;
		}

		template<class T>
		Array<T>& Array<T>::SubArray(unsigned int i, unsigned int _count) {
			int finish = i + _count - 1;
			return Slice(i, finish);
		}

		template<class T>
		int Array<T>::FindIndex(T element) {
			for (int i = 0; i < count; i++) {
				if (element == ar[i]) {
					return i;
				}
			}
			return -1;
		}
		template<class T>
		int* Array<T>::FindMin() {
			int res[3] = { 0, -1, 0 };
			int countMin = 1;
			if (!count) {
				return res;
			}
			int minInd = 0;
			T min = ar[0];
			for (int i = 1; i < count; i++) {
				if (min > ar[i]) {
					minInd = i;
					countMin = 1;
				}
				else if (min == ar[i]) {
					countMin++;
				}
			}
			res[0] = minInd;
			res[1] = countMin;
			return res;
		}
	}
}


