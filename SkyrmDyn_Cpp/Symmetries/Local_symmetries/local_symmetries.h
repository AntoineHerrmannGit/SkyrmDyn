#ifndef LOCAL_SYMMETRIES_H
#define LOCAL_SYMMETRIES_H

#include "Maths/Objects/Array/Array_double/array_double.h"
#include "Objects/Atom/atom.h"

bool check_rotation_symmetry( Atom& atom1, Atom& atom2, Array_double axis, int n );
bool check_mirror_symmetry( Atom& atom1, Atom& atom2 );
bool check_planar_symmetry( Atom& atom1, Atom& atom2 );
bool check_inversion_symmetry( Atom& atom1, Atom& atom2 );

std::vector< Atom > create_neighbors_cloud( Atom& atom1, Atom& atom2 );

std::vector< Atom > create_virtual_neighbors_cloud( Atom& atom1, Atom& atom2 );

std::vector< Array_double > get_planar_symmetry_plan( Atom& atom1, Atom& atom2 );

#endif // LOCAL_SYMMETRIES_H
