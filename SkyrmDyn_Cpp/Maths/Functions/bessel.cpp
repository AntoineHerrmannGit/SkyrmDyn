#include "bessel.h"

#include "special.h"
#include "Constants/constants.h"

#include <math.h>

double BesselJ( int n, double x ) {
    double j = 0;
    float step = 0.001;
    float t = 0;
    while( t<pi ) {
        j += step * cos( n * t - x * sin(t) );
        t += step;
    }
    return j / pi;
}

double BesselY( int n, double x ) {
    double first_term = 0;
    float step = 0.001;
    float t = 0;
    while( t<pi ) {
        first_term += step * sin( x * sin(t) - n * t );
        t += step;
    }

    double second_term = 0;
    t = 0;
    while( t<pi ) {
        second_term += step * ( exp( n*t ) + pow( -1,n ) * exp( -n*t ) ) * exp( -x*sinh( t ) );
        t += step;
    }
    return ( first_term - second_term ) / pi;
}
