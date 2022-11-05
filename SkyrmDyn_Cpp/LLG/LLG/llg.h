#ifndef LLG_H
#define LLG_H

#include "Maths/Objects/Array/Array_double/array_double.h"
#include "Maths/Objects/Matrix/Real_matrix/real_matrix.h"

#include "Objects/Atom/atom.h"
#include "Objects/Parameter/parameter.h"

Atom make_euler_llg_step( Atom& atom, Array_double &magnetic_field, Parameter& para );

Real_matrix build_llg_coupling_matrix( Atom& atom, Parameter& para );

Array_double build_llg_second_term( Atom& atom, Array_double& magnetic_field, Parameter& para );


Atom make_euler_llg_step_backward( Atom& atom, Array_double &magnetic_field, Parameter& para );

Real_matrix build_llg_backward_coupling_matrix( Atom& atom, Parameter& para );

Array_double build_llg_backward_second_term( Atom& atom, Array_double& magnetic_field, Parameter& para );


Atom make_rk4_llg_step( Atom& atom, Array_double &magnetic_field, Parameter& para );






#endif // LLG_H
