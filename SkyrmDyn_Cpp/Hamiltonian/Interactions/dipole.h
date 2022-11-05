#ifndef DIPOLE_H
#define DIPOLE_H

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Objects/Atom/atom.h"
#include "Objects/Parameter/parameter.h"

double dipole_energy( Atom& atom1, Atom& atom2, Parameter& para );

Array_double dipole_field( Atom& atom1, Atom& atom2, Parameter& para );

#endif // DIPOLE_H
