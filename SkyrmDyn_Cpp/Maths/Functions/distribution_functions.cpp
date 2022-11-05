#include "distribution_functions.h"

#include "Constants/constants.h"

#include <math.h>

double gaussian( double x, double mean, double sigma ) {
    double gauss = 1/( sigma * sqrt( 2*pi ) ) * exp( -pow( ( x-mean ) / ( 2*sigma ), 2 )  );
    return gauss;
}
double lorentzian( double x, double mean, double sigma ) {
    double lorentz = 1/( sigma*pi * ( 1 + pow( (x-mean) / sigma, 2 ) ) );
    return lorentz;
}
double exponential( double x, double lambda ) {
    double expo = lambda * exp( -lambda*x );
    return expo;
}
int delta( double i, double j ) {
    if( i==j ) {
        return 1;
    }
    else {
        return 0;
    }
}


