#include <stdexcept>
using namespace std;
#ifndef AERODYNAMICS_HPP
#define AERODYNAMICS_HPP

namespace Aerodynamics {
    
    namespace UI {}
    namespace Analytics {
        struct AeroQuality
        {
            double Cx, Cy, a;
            AeroQuality() = default;
            AeroQuality(double Cx, double Cy, double a) : Cx(Cx), Cy(Cy) {
                while (a > 360) {
                    a -= 360;
                }
                while (a < -360) {
                    a += 360;
                }
                this->a = a;
            }
        };
        namespace AtmosphereConstants {
            const double SEA_LEVEL_PRESSURE = 101325.0;
            const double SEA_LEVEL_TEMPERATURE = 288.15;
            const double AIR_DENSITY = 1.225;
            const double SPEED_OF_SOUND = 343.2;
            const double TROPOSPHERE_DENSITY = 1.225; // êã/ì^3
            const double STRATOSPHERE_DENSITY = 0.1;   // êã/ì^3
            const double MESOSPHERE_DENSITY = 0.01;   // êã/ì^3
            const double THERMOSPHERE_DENSITY = 0.00001;   // êã/ì^3
            const double EXOSPHERE_DENSITY = 0.0000001;
            const double g = 9.81;
        }
        static double evalY(double Cy, double density,double v,double S) {
            double Y;
            Y=Cy* density* v* v / 2 * S;
            return Y;
        }
        static int length(int a) {
            if (!a) return 1;
			int l = 0;
            while (a > 0) {
				a /= 10;
				l++;
			}
			return l;
		}
        static int length(double a,unsigned int n=0) {
            if (!a) return 1;
            int l = 0;
            if (n) l = 1;
            double d = 1. / ((n+1)*10);
            while (a > d) {
                a /= 10;
                l++;
            }
            return l;
        }
    }
    namespace Data {
        
    }
    
}

#endif // AERODYNAMICS_HPP
/*
16.35 - 16.44 9
20.05 - 21.22 1.17
12.22 - 13.18 56
14.55 - 15.28 33
10.42 - 11.10 28
14.04 - 14.29 25
9.17  - 10.40 1.23
13.50 - 14.00 10
19.40 - 19.57
20.22 - 20.33
10.00 - 10.20
10.55 - 12.02
8.40  - 9.09
9.43  - 10.26
10.50 - 11.40
13.20 - 14.18
14.39 - 15.15
15.35 - 15.50
8.55  - 10.00
13.20 - 14.50
21.40 - 22.13
8h
5ã

*/
