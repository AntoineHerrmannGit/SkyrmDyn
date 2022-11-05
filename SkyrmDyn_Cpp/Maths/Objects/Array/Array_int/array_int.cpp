#include "array_int.h"

#include "Error_messages/error_messages.h"

#include <math.h>

// Constructor
//-----------------------------------
Array_int::Array_int( int new_dimension ) {
    setup_vector( new_dimension );
};

Array_int::Array_int() {
    setup_vector( 3 );
};
// Getters
//-----------------------------------
int Array_int::get_component( int i ) {
    return vector[i];
}
int Array_int::get_dimension() {
    return vector.size();
}

int Array_int::get_x() {
    return vector[0];
}
int Array_int::get_y() {
    return vector[1];
}
int Array_int::get_z() {
    return vector[2];
}

// Setters
//-----------------------------------
void Array_int::set_array( Array_int &new_array ) {
    int dimension = vector.size();
    for( int i=0; i<dimension; i++ ) {
        int element = new_array.get_component( i );
        set_component( i, element );
    }
}
void Array_int::set_component( int i, int element ) {
    vector[i] = element;
}

// Public library
//-----------------------------------
void Array_int::add( Array_int array ) {
    int dimension = vector.size();
    for( int i=0; i<dimension; i++ ) {
        vector[i] += array.get_component(i);
    }
}
void Array_int::substract( Array_int array ) {
    int dimension = vector.size();
    for( int i=0; i<dimension; i++ ) {
        vector[i] -= array.get_component(i);
    }
}
void Array_int::multiply_by_scalar( int scalar ) {
    int dimension = vector.size();
    for( int i=0; i<dimension; i++ ) {
        vector[i] = vector[i]*scalar;
    }
}

bool Array_int::operator== ( Array_int& rhs ) {
    if( (int)vector.size() != rhs.get_dimension() ) {
        return false;
    }
    else {
        for( int i=0; i<(int)vector.size(); i++ ) {
            if( vector[i] != rhs.get_component(i) ) {
                return false;
            }
        }
        return true;
    }
}
bool Array_int::operator!= ( Array_int& rhs ) {
    if( (int)vector.size() != rhs.get_dimension() ) {
        return true;
    }
    else {
        for( int i=0; i<(int)vector.size(); i++ ) {
            if( vector[i] != rhs.get_component(i) ) {
                return true;
            }
        }
        return false;
    }
}

void Array_int::operator+ ( Array_int& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] += rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "addition", "vector", "vectors of different size" ) );
    }
}
void Array_int::operator+= ( Array_int& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] += rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "addition", "vector", "vectors of different size" ) );
    }
}
void Array_int::operator- ( Array_int& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] -= rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "substraction", "vector", "vectors of different size" ) );
    }
}
void Array_int::operator-= ( Array_int& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] -= rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "substraction", "vector", "vectors of different size" ) );
    }
}

void Array_int::operator* ( double scalar ) {
    for( int i=0; i<get_dimension(); i++ ) {
        vector[i] *= scalar;
    }
}
void Array_int::operator*= ( double scalar ) {
    for( int i=0; i<get_dimension(); i++ ) {
        vector[i] *= scalar;
    }
}
void Array_int::operator/ ( double scalar ) {
    for( int i=0; i<get_dimension(); i++ ) {
        vector[i] /= scalar;
    }
}
void Array_int::operator/= ( double scalar ) {
    for( int i=0; i<get_dimension(); i++ ) {
        vector[i] /= scalar;
    }
}


// Privatelibrary
//-----------------------------------
void Array_int::setup_vector( int new_dimension ) {
    for( int i=0; i<new_dimension; i++ ) {
        vector.push_back(0);
    }
}



