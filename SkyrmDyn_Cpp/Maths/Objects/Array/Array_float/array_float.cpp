#include "array_float.h"

#include "Error_messages/error_messages.h"

#include <math.h>

// Constructor
//-----------------------------------
Array_float::Array_float( int new_dimension ) {
    setup_vector( new_dimension );
};

Array_float::Array_float() {
    setup_vector( 3 );
};

// Getters
//-----------------------------------
float Array_float::get_component( int i ) {
    return vector[i];
}
int Array_float::get_dimension() {
    return vector.size();
}

float Array_float::get_x() {
    return vector[0];
}
float Array_float::get_y() {
    return vector[1];
}
float Array_float::get_z() {
    return vector[2];
}

// Setters
//-----------------------------------
void Array_float::set_array( Array_float &new_array ) {
    int dimension = vector.size();
    for( int i=0; i<dimension; i++ ) {
        float element = new_array.get_component( i );
        set_component( i, element );
    }
}
void Array_float::set_component( int i, float element ) {
    vector[i] = element;
}

// Public library
//-----------------------------------
void Array_float::normalize() {
    double norm = 0;
    int dimension = vector.size();
    for( int i=0; i<dimension; i++ ) {
        norm += get_component(i)*get_component(i);
    }
    norm = sqrt(norm);
    for( int i=0; i<dimension; i++ ) {
        float element = get_component(i) / norm;
        set_component( i, element );
    }
}
void Array_float::add( Array_float array ) {
    int dimension = vector.size();
    for( int i=0; i<dimension; i++ ) {
        vector[i] += array.get_component(i);
    }
}
void Array_float::substract( Array_float array ) {
    int dimension = vector.size();
    for( int i=0; i<dimension; i++ ) {
        vector[i] -= array.get_component(i);
    }
}
void Array_float::multiply_by_scalar( float scalar ) {
    int dimension = vector.size();
    for( int i=0; i<dimension; i++ ) {
        vector[i] = vector[i]*scalar;
    }
}

bool Array_float::operator== ( Array_float& rhs ) {
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
bool Array_float::operator!= ( Array_float& rhs ) {
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

void Array_float::operator+ ( Array_float& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] += rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "addition", "vector", "vectors of different size" ) );
    }
}
void Array_float::operator+= ( Array_float& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] += rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "addition", "vector", "vectors of different size" ) );
    }
}
void Array_float::operator- ( Array_float& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] -= rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "substraction", "vector", "vectors of different size" ) );
    }
}
void Array_float::operator-= ( Array_float& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] -= rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "substraction", "vector", "vectors of different size" ) );
    }
}

void Array_float::operator+ ( Array_int& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] += rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "addition", "vector", "vectors of different size" ) );
    }
}
void Array_float::operator+= ( Array_int& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] += rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "addition", "vector", "vectors of different size" ) );
    }
}
void Array_float::operator- ( Array_int& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] -= rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "substraction", "vector", "vectors of different size" ) );
    }
}
void Array_float::operator-= ( Array_int& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] -= rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "substraction", "vector", "vectors of different size" ) );
    }
}

void Array_float::operator* ( double scalar ) {
    for( int i=0; i<get_dimension(); i++ ) {
        vector[i] *= scalar;
    }
}
void Array_float::operator*= ( double scalar ) {
    for( int i=0; i<get_dimension(); i++ ) {
        vector[i] *= scalar;
    }
}
void Array_float::operator/ ( double scalar ) {
    for( int i=0; i<get_dimension(); i++ ) {
        vector[i] /= scalar;
    }
}
void Array_float::operator/= ( double scalar ) {
    for( int i=0; i<get_dimension(); i++ ) {
        vector[i] /= scalar;
    }
}


// Privatelibrary
//-----------------------------------
void Array_float::setup_vector( int new_dimension ) {
    for( int i=0; i<new_dimension; i++ ) {
        vector.push_back(0);
    }
}
