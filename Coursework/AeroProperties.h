#pragma once
#include "aerodynamics.h"
#include <vector>
namespace Aerodynamics {
	namespace Analytics {
		class AeroProperties
		{
			vector<AeroQuality> arK;
		public:
			AeroProperties() {
				arK.reserve(10);
			}
			AeroProperties& add(double Cx, double Cy, double a) {
				AeroQuality K(Cx, Cy, a);
				arK.push_back(K);
				return *this;
			}
			AeroProperties& sort(int l, int r)
			{
				int i, j;
				double x;
				AeroQuality y;
				i = l; j = r;
				x = arK[(l + r) / 2].a;
				do
				{
					while ((arK[i].a < x) && (i < r)) i++;
					while ((x < arK[j].a) && (j > l)) j--;
					if (i <= j)
					{
						y = arK[i];
						arK[i] = arK[j];
						arK[j] = y;
						i++; j--;
					}
				} while (i <= j);
				if (l < j) sort(l, j);
				if (i < r) sort(i, r);
				return *this;
			}
			AeroProperties& clear() {
				arK.clear();
				return *this;
			}
			AeroQuality operator [] (int i) {
				return arK[i];
			}
			int size() {
				return arK.size();
			}
			bool empty() {
				return arK.empty();
			}
			double getK(double angle) {
				if (!arK.empty()) {
					double K;
					int e = arK.size() / 2;
					int count = arK.size();
					short iterM = 0;
					while (1) {
						if (arK[e].a > angle) {
							e /= 2;
							iterM = 0;
						}
						else if (angle > arK[e].a) {
							e += e / 2;
							iterM++;
							if (!count || iterM==2) {
								if (e + 1 >= arK.size()) {
									K = arK[e].Cy / arK[e].Cx;
								}
								else {
									double h = (angle - arK[e].a) / (arK[e + 1].a - angle);
									K = (arK[e].Cy + h * arK[e + 1].Cy) / (arK[e].Cx + h * arK[e + 1].Cx);
								}
								break;
							}
						}
						else {
							K = arK[e].Cy / arK[e].Cx;
							break;
						}
						count /= 2;
					}
					return K;
				}
				else {
					throw exception("Aircraft have not aero properties");
				}
			}
			bool operator == (AeroProperties& ap) {
				
				int s = ap.size();
				int count = 0;
				double a;
				for (int i = 0; i < s; i++) {
					a = ap[i].a;
					if (abs(ap[i].Cx - (*this).getCx(a))<0.5 && abs(ap[i].Cy - (*this).getCy(a)) < 0.5) {
						count++;
					}
				}
				if (count == s - 1) return true;
				return false;
			}
			double getCx(double angle) {
				if (!arK.empty()) {
					double fCx;
					int e = arK.size() / 2;
					int count = arK.size();
					short iterM = 0;
					while (1) {
						if (arK[e].a > angle) {
							e /= 2;
							iterM = 0;
						}
						else if (angle > arK[e].a) {
							e += e / 2;
							iterM++;
							if (!count || iterM == 2) {
								if (e + 1 >= arK.size()) {
									fCx = arK[e].Cx;
								}
								else {
									double h = (angle - arK[e].a) / (arK[e + 1].a - angle);
									fCx = (arK[e].Cx + h * arK[e + 1].Cx)/(1+h);
								}
								break;
							}
						}
						else {
							fCx = arK[e].Cx;
							break;
						}
						count /= 2;
					}
					return fCx;
				}
				else {
					throw exception("Aircraft have not aero properties");
				}
			}
			double getCy(double angle) {
				if (!arK.empty()) {
					double fCy;
					int e = arK.size() / 2;
					int count = arK.size();
					short iterM = 0;
					while (1) {
						if (arK[e].a > angle) {
							e /= 2;
							iterM = 0;
						}
						else if (angle > arK[e].a) {
							e += e / 2;
							iterM++;
							if (!count || iterM == 2) {
								if (e + 1 >= arK.size()) {
									fCy = arK[e].Cy;
								}
								else {
									double h = (angle - arK[e].a) / (arK[e + 1].a - angle);
									fCy = (arK[e].Cy + h * arK[e + 1].Cy)/(1+h);
								}
								break;
							}
						}
						else {
							fCy = arK[e].Cy;
							break;
						}
						count /= 2;
					}
					return fCy;
				}
				else {
					throw exception("Aircraft have not aero properties");
				}
			}
			vector<AeroQuality>* getVectorAK() {
				return &arK;
			}
			AeroProperties& set(vector<AeroQuality> _arK) {
				arK = _arK;
				return *this;
			}
		};
	}
}
