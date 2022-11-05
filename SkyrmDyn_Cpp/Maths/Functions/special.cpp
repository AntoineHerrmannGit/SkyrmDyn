#include "special.h"

#include <math.h>

int factorial( int n ){
    if( n==0 ) {
        return 1;
    }
    else {
        int fact = 1;
        for( int i=1; i<=n; i++ ) {
            fact = fact * i;
        }
        return fact;
    }
}

double SinInt( double x ) {
    float step = 0.001;
    if( x <= 1e-9 ) {
        return 0;
    }
    else if( x <= 100*step ) {
        while( x <= 100*step ) {
            step = step / 10;
        }
    }
    float t = step;
    double sinint = 0;
    while( t<x ) {
        sinint += sin( t ) / t;
        t += step;
    }
    return sinint;
}
