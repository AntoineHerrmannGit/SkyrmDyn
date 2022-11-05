#ifndef ZEEMAN_H
#define ZEEMAN_H

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Objects/Atom/atom.h"
#include "Objects/Parameter/parameter.h"

double zeeman_energy( Atom& atom, Parameter& para );

#endif // ZEEMAN_H
