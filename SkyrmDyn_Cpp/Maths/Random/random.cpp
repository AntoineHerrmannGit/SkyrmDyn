#include "random.h"

#include "Constants/constants.h"

#include "Maths/Functions/distribution_functions.h"

#include "Maths/Objects/Array/Array_double/array_double.h"

#include <random> // for std::mt19937
#include <chrono> // for std::chrono
#include <math.h>

double random( double a, double b ) {
    // Generates a random number between a and b

    // Creates a random seed
    std::random_device seed;

    // Creates a Messner Twister random engine initialized with the seed
    std::mt19937_64 gen( seed() );

    // Creates a random distribution on the Messner Twister engine
    std::uniform_real_distribution<> dis( a, b );

    // Extracts a random number and return
    double rand = dis( gen );
    return rand;
}

double white_noise( double mean, double sigma ) {
    double x = 0;
    double y = 2;
    double test = 1;
    while( y > test ) {
        x = random( mean - 5*sigma, mean + 5*sigma );
        y = random( mean - 5*sigma, mean + 5*sigma );
        test = gaussian( x, mean, sigma );
    }
    return x;
}

Array_double random_vector() {
    double theta = random( 0, pi );
    double phi = random( 0, 2*pi );
    Array_double vect;
    vect.set_component( 0, sin(theta) * cos(phi) );
    vect.set_component( 1, sin(theta) * sin(phi) );
    vect.set_component( 2, cos(theta) );
    return vect;
}
