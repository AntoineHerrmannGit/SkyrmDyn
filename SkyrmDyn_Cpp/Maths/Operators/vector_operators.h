#ifndef VECTOR_OPERATORS_H
#define VECTOR_OPERATORS_H

#include "Maths/Objects/Array/Array_double/array_double.h"

#include <vector>

double dot( Array_double v1, Array_double v2 );
Array_double cross( Array_double v1, Array_double v2 );

void rotate( Array_double& vector, Array_double axis, double angle );

std::vector< Array_double > orthonormal_basis( Array_double vect1, Array_double vect2 );

Array_double average_vector( std::vector< Array_double > vectors );

#endif // VECTOR_OPERATORS_H
