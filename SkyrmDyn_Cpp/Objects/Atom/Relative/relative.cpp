#include "Objects/Atom/atom.h"

#include "Maths/Operators/vector_operators.h"

#include <math.h>

double Atom::distance( Atom& other ) {
    if( other.get_position().get_dimension() != position.get_dimension() ) {
        throw( "Error in atom in distance : comparing two positions of different dimensions \n" );
    }
    else {
        double dist = sqrt( dot( relative_position( other ), relative_position( other ) ) );
        return dist;
    }
}

Array_double Atom::relative_position( Atom& other ) {
    Array_double relative_position = other.get_position();
    relative_position.substract( position );
    return relative_position;
}
