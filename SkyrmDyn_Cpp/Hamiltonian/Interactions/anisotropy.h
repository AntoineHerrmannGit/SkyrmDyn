#ifndef ANISOTROPY_H
#define ANISOTROPY_H

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Objects/Atom/atom.h"
#include "Objects/Parameter/parameter.h"

double anisotropy_energy( Atom& atom, Parameter& para );

Array_double anisotropy_field( Atom& atom, Parameter& para );

#endif // ANISOTROPY_H
