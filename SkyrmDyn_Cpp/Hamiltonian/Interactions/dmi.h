#ifndef DMI_H
#define DMI_H

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Objects/Atom/atom.h"
#include "Objects/Parameter/parameter.h"

#include "Maths/Operators/vector_operators.h"

double dmi_energy( Atom& atom1, Atom& atom2, Parameter para );

Array_double dmi_field( Atom& atom1, Atom& atom2, Parameter& para );

Array_double dm_vector( Atom& atom1, Atom& atom2, Parameter& para );

#endif // DMI_H
