#include "temperature_field.h"

#include "Maths/Random/random.h"

#include "Constants/constants.h"

#include <math.h>

Array_double temperature_field( double T, double D ) {
    // Generates a randomly oriented temperature field with amplitude obeying Langevin field
    Array_double noise;
    if( T==0 ) {
        double t = sqrt( 2*pi ) / sqrt( 2 * D * k_B * T );
        double r = white_noise( 0, t );
        double theta = random( 0, pi );
        double phi = random( 0, 2*pi );
        noise.set_component( 0, r * sin(theta) * cos(phi) );
        noise.set_component( 0, r * sin(theta) * sin(phi) );
        noise.set_component( 0, r * cos(theta) );
    }
    else {
        noise.set_component(0, 0);
        noise.set_component(1, 0);
        noise.set_component(2, 0);
    }
    return noise;
}




