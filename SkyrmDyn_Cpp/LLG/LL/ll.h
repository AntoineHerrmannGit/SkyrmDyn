#ifndef LL_H
#define LL_H

#include "Objects/Atom/atom.h"
#include "Objects/Parameter/parameter.h"

Atom make_euler_ll_step( Atom& atom, Array_double &magnetic_field, Parameter& para );
Atom make_rk4_ll_step( Atom& atom, Array_double &magnetic_field, Parameter& para );

#endif // LL_H
