#include "dipole.h"

#include "Constants/constants.h"

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Maths/Operators/vector_operators.h"

#include "Objects/Atom/atom.h"
#include "Objects/Parameter/parameter.h"

#include <math.h>

double dipole_energy( Atom& atom1, Atom& atom2, Parameter& para ) {
    Array_double spin1 = atom1.get_spin_copy();
    Array_double spin2 = atom2.get_spin_copy();

    Array_double relative_position = atom1.relative_position( atom2 );
    double distance = atom1.distance( atom2 );

    double M_s = para.get_demag_M_s();
    double factor = -mu_0*M_s*M_s;

    double energy = factor * ( 3 * dot( spin1, relative_position ) * dot( spin2, relative_position )
                             - dot( spin1, spin2 ) ) / pow( distance, 3 );

    return energy;
}

Array_double dipole_field( Atom& atom1, Atom& atom2, Parameter& para ) {
    Array_double field = atom1.relative_position( atom2 ); // Here plays the role of relative position
    field.normalize();
    double distance = atom1.distance( atom2 );

    double M_s = para.get_demag_M_s();
    double factor = - 0.5 * mu_0 * M_s * M_s / pow( distance, 3 );

    Array_double spin2 = atom2.get_spin_copy();
    double scalar = 3 * dot( spin2, field );
    field.multiply_by_scalar( scalar );

    field.substract( spin2 );
    field.multiply_by_scalar( factor );

    return field;
}

