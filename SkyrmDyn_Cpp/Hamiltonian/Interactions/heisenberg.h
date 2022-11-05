#ifndef HEISENBERG_H
#define HEISENBERG_H

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Objects/Atom/atom.h"
#include "Objects/Parameter/parameter.h"

double RKKY( double &r, double &T, int dimension );
double heisenberg_energy( Atom& atom1, Atom& atom2, Parameter& para );

Array_double heisenberg_eff_mag_field( Atom& atom1, Atom& atom2, Parameter& para );

#endif // HEISENBERG_H



