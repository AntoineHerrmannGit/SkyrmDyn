#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <math.h>

using namespace std;

// Natural constants
//-------------------------
const double hbar = 1; // 0.6582119570;             // eV.fs             # wiki
const double m_e = 1; // 510998.95000;              // eV/c^2            # wiki
const double e = 1; // 1.60217657e-19;              // C                 # wiki
const double c = 1; // 299.792458;                  // nm/fs             # wiki

// Magnetic constants
//-------------------------
const double g = 1; // 0.5;
const double mu_0 = 1.0;                      // eV/T              # definition
const double mu_B = 1; // 5.7883817555e-5;          // eV/T              # wiki
const double e_0 = 1; // 1 / ( c*c );               // ( fs/nm ) ^2      # wiki

// Temperature constants
//-------------------------
const double k_B = 1; // 8.6173303e-5;              // eV/K              # wiki
const double T_F = 1; // 28000.0;                   // K                 # wiki

// Fermi constants
//-------------------------
const double e_F = k_B * T_F;
const double k_F = sqrt( 2.0 * m_e * e_F / ( hbar * hbar ) );
const double v_F = hbar * k_F / m_e;

// Maths constants
//-------------------------
const double pi = 3.14159265358979323846;

#endif // CONSTANTS_H
