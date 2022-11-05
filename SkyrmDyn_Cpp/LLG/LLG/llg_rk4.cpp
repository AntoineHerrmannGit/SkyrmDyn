#include "LLG/LLG/llg.h"
#include "Objects/Lattice/lattice.h"

#include "Constants/constants.h"

#include "Maths/Objects/Matrix/Real_matrix/real_matrix.h"

#include "Maths/Operators/vector_operators.h"

#include "Objects/Atom/atom.h"


Atom make_rk4_llg_step( Atom& atom, Array_double &magnetic_field, Parameter& para ) {
    double gamma = e/(2*m_e);
    double llg_time_step = para.get_llg_time_step();

    Array_double spin = atom.get_spin();

    Real_matrix coupling_matrix = build_llg_backward_coupling_matrix( atom, para );
    coupling_matrix.inverse();

    Array_double first_term = cross( spin, magnetic_field );
    first_term = coupling_matrix.multiply_right_by_array_double( first_term );
    first_term *= ( -gamma );

    Array_double second_term = first_term;
    second_term *= ( 0.5*llg_time_step );
    second_term += spin;
    second_term = cross( second_term, magnetic_field );
    second_term = coupling_matrix.multiply_right_by_array_double( second_term );
    second_term *= ( -2*gamma );

    Array_double third_term = second_term;
    third_term *= ( 0.5*llg_time_step );
    third_term += spin;
    third_term = cross( third_term, magnetic_field );
    third_term = coupling_matrix.multiply_right_by_array_double( third_term );
    third_term *= ( -2*gamma );

    Array_double fourth_term = third_term;
    fourth_term *= llg_time_step;
    fourth_term += spin;
    fourth_term = cross( fourth_term, magnetic_field );
    fourth_term = coupling_matrix.multiply_right_by_array_double( fourth_term );
    fourth_term *= ( -gamma );

    first_term += second_term;
    first_term += third_term;
    first_term += fourth_term;

    spin += first_term;
    spin.normalize();
    atom.set_spin( spin );
    return atom;
}



