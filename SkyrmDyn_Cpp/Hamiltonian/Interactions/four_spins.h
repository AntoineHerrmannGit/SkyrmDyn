#ifndef FOUR_SPINS_H
#define FOUR_SPINS_H

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Objects/Atom/atom.h"
#include "Objects/Parameter/parameter.h"

double four_spin_energy( Atom& atom1, Atom& atom2, Atom& atom3, Atom& atom4, Parameter& para );

Array_double four_spin_field( Atom& atom1, Atom& atom2, Atom& atom3, Atom& atom4, Parameter& para );

#endif // FOUR_SPINS_H
