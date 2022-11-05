#ifndef ILLG_H
#define ILLG_H

#include "Maths/Objects/Array/Array_double/array_double.h"
#include "Maths/Objects/Matrix/Real_matrix/real_matrix.h"

#include "Objects/Atom/atom.h"
#include "Objects/Parameter/parameter.h"

Atom make_euler_illg_step( Atom& atom, Array_double& local_magnetic_field, Parameter& para );

Real_matrix build_illg_coupling_matrix( Atom& atom, Parameter& para );

Array_double build_illg_second_term( Atom& atom, Array_double& magnetic_field, Parameter& para );

#endif // ILLG_H
