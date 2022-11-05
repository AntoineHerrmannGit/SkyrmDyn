#include "zeeman.h"

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Maths/Operators/vector_operators.h"

double zeeman_energy( Atom& atom, Parameter& para ) {
    Array_double spin = atom.get_spin();
    Array_double magnetic_field = para.get_magnetic_field();
    double energy = - dot( spin, magnetic_field );
    return energy;
}
