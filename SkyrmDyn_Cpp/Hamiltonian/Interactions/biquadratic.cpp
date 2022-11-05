#include "biquadratic.h"

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Maths/Operators/vector_operators.h"

#include "Objects/Atom/atom.h"


double biquadratic_energy( Atom& atom1, Atom& atom2, Parameter& para ) {
    Array_double spin1 = atom1.get_spin_copy();
    Array_double spin2 = atom2.get_spin_copy();
    double B = para.get_biquadratic_B();
    double energy = - B * dot( spin1, spin2 ) * dot( spin1, spin2 );
    return energy;
}

Array_double biquadratic_field( Atom& atom1, Atom& atom2, Parameter& para ) {
    Array_double spin1 = atom1.get_spin_copy();
    Array_double spin2 = atom2.get_spin_copy();
    double B = para.get_biquadratic_B();
    double term = 2 * B * dot( spin1, spin2 );

    Array_double field = spin2;
    field.multiply_by_scalar( term );
    return field;
}
