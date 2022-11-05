#ifndef RANDOM_H
#define RANDOM_H

#include "Maths/Objects/Array/Array_double/array_double.h"

double random( double a, double b );

double white_noise( double mean, double sigma );

Array_double random_vector();

#endif // RANDOM_H
