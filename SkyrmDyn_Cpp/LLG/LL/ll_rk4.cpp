#include "LLG/LL/ll.h"
#include "Objects/Lattice/lattice.h"

#include "Constants/constants.h"

#include "Maths/Operators/vector_operators.h"

#include "Objects/Atom/atom.h"

Atom make_rk4_ll_step( Atom& atom, Array_double &magnetic_field, Parameter& para ) {
    double gamma = e/(2*m_e);
    double damping = para.get_damping();
    double llg_time_step = para.get_llg_time_step();

    Array_double spin = atom.get_spin();

    Array_double first_term = cross( spin, magnetic_field );
    first_term *= (-gamma);
    Array_double intermediate_term = cross( spin, cross( spin, magnetic_field ) );
    intermediate_term *= ( -damping );
    first_term += intermediate_term;

    intermediate_term = first_term;
    intermediate_term *= (0.5 * llg_time_step);
    intermediate_term += spin;
    Array_double second_term = cross( intermediate_term , magnetic_field );
    second_term *= (-gamma);
    intermediate_term = cross( intermediate_term, cross( intermediate_term, magnetic_field ) );
    intermediate_term *= ( -damping );
    second_term += intermediate_term;
    second_term *= 2;

    intermediate_term = second_term;
    intermediate_term *= (0.5 * llg_time_step);
    intermediate_term += spin;
    Array_double third_term = cross( intermediate_term , magnetic_field );
    third_term *= (-gamma);
    intermediate_term = cross( intermediate_term, cross( intermediate_term, magnetic_field ) );
    intermediate_term *= ( -damping );
    third_term += intermediate_term;
    third_term *= 2;

    intermediate_term = third_term;
    intermediate_term *= llg_time_step;
    intermediate_term += spin;
    Array_double fourth_term = cross( intermediate_term , magnetic_field );
    fourth_term *= (-gamma);
    intermediate_term = cross( intermediate_term, cross( intermediate_term, magnetic_field ) );
    intermediate_term *= ( -damping );
    fourth_term += intermediate_term;

    intermediate_term = first_term;
    intermediate_term += second_term;
    intermediate_term += third_term;
    intermediate_term += fourth_term;
    intermediate_term *= ( llg_time_step / 6 );

    spin += intermediate_term;
    spin.normalize();
    atom.set_spin( spin );
    return atom;
}



