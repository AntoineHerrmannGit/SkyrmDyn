#include "anisotropy.h"

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Maths/Operators/vector_operators.h"

double anisotropy_energy( Atom& atom, Parameter& para ) {
    Array_double spin = atom.get_spin();
    Array_double anisotropy_axis = para.get_anisotropy_field();
    double fact = - dot( spin, anisotropy_axis )*dot( spin, anisotropy_axis );
    return fact;
}

Array_double anisotropy_field( Atom& atom, Parameter& para ) {
    Array_double spin = atom.get_spin();
    Array_double anisotropy_axis = para.get_anisotropy_field();
    double fact = 2*dot( spin, anisotropy_axis );
    anisotropy_axis.multiply_by_scalar( fact );
    return anisotropy_axis;
}
