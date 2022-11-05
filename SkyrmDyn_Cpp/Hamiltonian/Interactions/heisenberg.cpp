#include "heisenberg.h"

#include "Constants/constants.h"

#include "Maths/Functions/bessel.h"
#include "Maths/Functions/special.h"

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Maths/Operators/vector_operators.h"

#include "Objects/Atom/atom.h"
#include "Objects/Parameter/parameter.h"

#include <iostream>
#include <math.h>

using namespace std;

/*
------------------------------------
RKKY function
arguments :
    double r : distance between atoms
    double T : electronic temperature
    int dimension : dimension of the system ( 3D / 2D / 1D )
return :
    double RKKY : response function
------------------------------------
*/

double RKKY( double &r, double &T, int dimension ) {
    double factor;
    double function;
    double x_F = k_F * r;

    if( dimension == 3 ) {
        factor = 2 * m_e * pow( k_F, 4 ) / ( pow( pi, 3) * pow( hbar, 2 ) );
        function = ( sin( 2 * x_F ) - 2 * x_F * cos( 2 * x_F ) ) / pow( 2 * x_F, 4 ) + pow( pi, 2 ) / 24 * pow( ( T / T_F ), 2 ) * cos( 2 * x_F ) / ( 2 * x_F );
    }
    else if( dimension == 2 ) {
        factor = - m_e * pow( k_F, 2 ) / ( 2 * pi * pow( hbar, 2 ) );
        double J0 = BesselJ( 0, x_F );
        double J1 = BesselJ( 1, x_F );
        double Y0 = BesselY( 0, x_F );
        double Y1 = BesselY( 1, x_F );
        function = J0 * Y0 + J1 * Y1 - pow( pi, 2 ) / 12 * pow( ( T / T_F ), 2 ) * ( J0 * Y1 + J1 * Y0 );
    }
    else if( dimension == 1 ) {
        factor = m_e / ( pi * pow( hbar, 2 ) );
        double Si = SinInt( 2 * x_F );
        function = ( pi / 2 ) - Si - pow( pi, 2 ) / 24 * pow( ( T / T_F ), 2 ) * ( x_F * cos( 2 * x_F ) - 2 * sin( 2 * x_F ) );
    }

    else {
        cout << "Error in << heisenberg ( RKKY ) >> : dimension is not well defined" << endl;
        return 0;
    }
    return factor * function;
}

double heisenberg_energy( Atom& atom1, Atom& atom2, Parameter& para ) {
    double T = para.get_temperature_T();
    double exchange_J = para.get_exchange_J();
    double r = atom1.distance( atom2 );
    int dimension = para.get_dimension();

    Array_double spin1 = atom1.get_spin_copy();
    Array_double spin2 = atom2.get_spin_copy();

    double rkky = RKKY( r, T, dimension );
    double s1s2 = dot( spin1, spin2 );
    double energy = - exchange_J / ( g * mu_B ) * rkky * s1s2;
    return energy;
}

Array_double heisenberg_eff_mag_field( Atom& atom1, Atom& atom2, Parameter& para ) {
    double T = para.get_temperature_T();
    double exchange_J = para.get_exchange_J();
    double r = atom1.distance( atom2 );
    int dimension = para.get_dimension();

    double fact = 0.5 * RKKY( r, T, dimension ) * exchange_J;
    Array_double spin = atom2.get_spin();

    spin.multiply_by_scalar( fact );
    return spin;
}






















