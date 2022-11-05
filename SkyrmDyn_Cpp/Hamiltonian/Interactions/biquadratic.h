#ifndef BIQUADRATIC_H
#define BIQUADRATIC_H

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Objects/Atom/atom.h"
#include "Objects/Parameter/parameter.h"

double biquadratic_energy( Atom& atom1, Atom& atom2, Parameter& para );

Array_double biquadratic_field(  Atom& atom1, Atom& atom2, Parameter& para );

#endif // BIQUADRATIC_H
