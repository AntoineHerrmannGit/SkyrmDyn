#ifndef EFFECTIVE_MAGNETIC_FIELD_H
#define EFFECTIVE_MAGNETIC_FIELD_H

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Objects/Atom/atom.h"
#include "Objects/Parameter/parameter.h"

Array_double build_effective_magnetic_field();

Array_double build_effective_2_body_magnetic_field( Atom& atom1, Atom* atom2, Parameter& para );
Array_double build_effective_4_body_magnetic_field( Atom& atom1, Atom& atom2, Atom& atom3, Atom& atom4, Parameter& para );

#endif // EFFECTIVE_MAGNETIC_FIELD_H
