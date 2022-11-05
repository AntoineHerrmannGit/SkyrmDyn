#include "four_spins.h"
#include "heisenberg.h"

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Maths/Operators/vector_operators.h"

#include "Objects/Atom/atom.h"
#include "Objects/Parameter/parameter.h"

#include <math.h>


double four_spin_energy( Atom& atom1, Atom& atom2, Atom& atom3, Atom& atom4, Parameter& para ) {
    double dist_12 = atom1.distance( atom2 );
    double dist_23 = atom2.distance( atom3 );
    double dist_34 = atom3.distance( atom4 );
    double dist_13 = atom1.distance( atom3 );
    double dist_14 = atom1.distance( atom4 );
    double dist_24 = atom2.distance( atom4 );

    Array_double spin1 = atom1.get_spin();
    Array_double spin2 = atom2.get_spin();
    Array_double spin3 = atom3.get_spin();
    Array_double spin4 = atom4.get_spin();

    double T = para.get_temperature_T();
    double F = para.get_four_spins_F();
    int dimension = para.get_dimension();

    double first_term = RKKY( dist_12, T, dimension ) * dot( spin1, spin2 ) * RKKY( dist_34, T, dimension ) *  dot( spin3, spin4 );
    double second_term = RKKY( dist_14, T, dimension ) * dot( spin1, spin4 ) * RKKY( dist_23, T, dimension ) * dot( spin2, spin3 );
    double third_term = - RKKY( dist_13, T, dimension ) * dot( spin1, spin3 ) * RKKY( dist_24, T, dimension ) * dot( spin2, spin4 );

    double energy = F * ( first_term + second_term + third_term );

    return energy;
}

Array_double four_spin_field( Atom& atom1, Atom& atom2, Atom& atom3, Atom& atom4, Parameter& para ) {
    double dist_12 = atom1.distance( atom2 );
    double dist_23 = atom2.distance( atom3 );
    double dist_34 = atom3.distance( atom4 );
    double dist_13 = atom1.distance( atom3 );
    double dist_14 = atom1.distance( atom4 );
    double dist_24 = atom2.distance( atom4 );

    Array_double spin1 = atom1.get_spin();
    Array_double spin2 = atom2.get_spin();
    Array_double spin3 = atom3.get_spin();
    Array_double spin4 = atom4.get_spin();

    double T = para.get_temperature_T();
    double F = para.get_four_spins_F();
    int dimension = para.get_dimension();

    Array_double first_term = spin2;
    first_term.multiply_by_scalar( -0.125 * F * RKKY( dist_12, T, dimension ) * RKKY( dist_34, T, dimension ) * dot( spin3, spin4 ) );
    Array_double second_term = spin4;
    second_term.multiply_by_scalar( -0.125 * F * RKKY( dist_14, T, dimension ) * RKKY( dist_23, T, dimension ) * dot( spin2, spin3 ) );
    Array_double third_term = spin3;
    third_term.multiply_by_scalar( 0.125 * F * RKKY( dist_13, T, dimension ) * RKKY( dist_24, T, dimension ) * dot( spin2, spin4 ) );

    Array_double field = first_term;
    field.add( second_term );
    field.add( third_term );

    return field;
}
