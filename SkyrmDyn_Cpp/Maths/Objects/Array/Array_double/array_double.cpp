#include "array_double.h"

#include "Error_messages/error_messages.h"

#include <math.h>

// Constructor
//-----------------------------------
Array_double::Array_double( int new_dimension ) {
    setup_vector( new_dimension );
};

Array_double::Array_double() {
    setup_vector( 3 );
};


// Getters
//-----------------------------------
int Array_double::get_dimension() {
    return (int)vector.size();
}

double Array_double::get_component( int i ) {
    return vector[i];
}

double Array_double::get_x() {
    return vector[0];
}
double Array_double::get_y() {
    return vector[1];
}
double Array_double::get_z() {
    return vector[2];
}

// Setters
//-----------------------------------
void Array_double::set_array( Array_double &new_array ) {
    if( new_array.get_dimension() == get_dimension() ) {
        for( int i=0; i<get_dimension(); i++ ) {
            double element = new_array.get_component( i );
            set_component( i, element );
        }
    }
    else {
        throw( "Error in attribution of Array_double : dimensions not matching" );
    }
}
void Array_double::set_component( int i, double element ) {
    vector[i] = element;
}

// Public library
//-----------------------------------

double Array_double::norm() {
    double n = 0;
    for( int i=0; i<get_dimension(); i++ ) {
        n += get_component(i)*get_component(i);
    }
    n = sqrt(n);
    return n;
}

void Array_double::normalize() {
    double norm = 0;
    for( int i=0; i<get_dimension(); i++ ) {
        norm += get_component(i)*get_component(i);
    }
    norm = sqrt(norm);
    for( int i=0; i<get_dimension(); i++ ) {
        double element = get_component(i) / norm;
        set_component( i, element );
    }
}
void Array_double::add( Array_double array ) {
    int dimension = get_dimension();
    for( int i=0; i<dimension; i++ ) {
        vector[i] += array.get_component(i);
    }
}
void Array_double::substract( Array_double array ) {
    int dimension = get_dimension();
    for( int i=0; i<dimension; i++ ) {
        vector[i] -= array.get_component(i);
    }
}
void Array_double::multiply_by_scalar( double scalar ) {
    int dimension = get_dimension();
    for( int i=0; i<dimension; i++ ) {
        vector[i] = vector[i]*scalar;
    }
}

bool Array_double::operator== ( Array_double& rhs ) {
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
bool Array_double::operator!= ( Array_double& rhs ) {
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
bool Array_double::is_equal( Array_double& rhs ) {
    int len = rhs.get_dimension();
    int dim = vector.size();
    if( len == dim ) {
        for( int i=0; i<len; i++ ) {
            double xi = vector[i];
            double rhsi = rhs.get_component( i );
            if( ( xi - rhsi ) < -1e-15 || ( xi - rhsi ) > 1e-15 ) {
                return false;
            }
        }
        return true;
    }
    else {
        throw( "Error in Array_double : is_equal() : objects of different length." );
    }
}
bool Array_double::is_not_equal( Array_double& rhs ) {
    int len = rhs.get_dimension();
    int dim = vector.size();
    if( len == dim ) {
        for( int i=0; i<len; i++ ) {
            double xi = vector[i];
            double rhsi = rhs.get_component( i );
            if( ( xi - rhsi ) < -1e-15 || ( xi - rhsi ) > 1e-15 ) {
                return true;
            }
        }
        return false;
    }
    else {
        throw( "Error in Array_double : is_equal() : objects of different length." );
    }
}

void Array_double::operator+ ( Array_double& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] += rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "addition", "vector", "vectors of different size" ) );
    }
}
void Array_double::operator+= ( Array_double& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] += rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "addition", "vector", "vectors of different size" ) );
    }
}
void Array_double::operator- ( Array_double& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] -= rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "substraction", "vector", "vectors of different size" ) );
    }
}
void Array_double::operator-= ( Array_double& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] -= rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "substraction", "vector", "vectors of different size" ) );
    }
}

void Array_double::operator+ ( Array_float& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] += rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "addition", "vector", "vectors of different size" ) );
    }
}
void Array_double::operator+= ( Array_float& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] += rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "addition", "vector", "vectors of different size" ) );
    }
}
void Array_double::operator- ( Array_float& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] -= rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "substraction", "vector", "vectors of different size" ) );
    }
}
void Array_double::operator-= ( Array_float& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] -= rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "substraction", "vector", "vectors of different size" ) );
    }
}

void Array_double::operator+ ( Array_int& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] += rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "addition", "vector", "vectors of different size" ) );
    }
}
void Array_double::operator+= ( Array_int& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] += rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "addition", "vector", "vectors of different size" ) );
    }
}
void Array_double::operator- ( Array_int& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] -= rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "substraction", "vector", "vectors of different size" ) );
    }
}
void Array_double::operator-= ( Array_int& rhs ) {
    if( rhs.get_dimension() == get_dimension() ){
        for( int i=0; i<get_dimension(); i++ ) {
            vector[i] -= rhs.get_component( i );
        }
    }
    else {
        throw( OperationImpossible( "substraction", "vector", "vectors of different size" ) );
    }
}

void Array_double::operator* ( double scalar ) {
    for( int i=0; i<get_dimension(); i++ ) {
        vector[i] *= scalar;
    }
}
void Array_double::operator*= ( double scalar ) {
    for( int i=0; i<get_dimension(); i++ ) {
        vector[i] *= scalar;
    }
}
void Array_double::operator/ ( double scalar ) {
    for( int i=0; i<get_dimension(); i++ ) {
        vector[i] /= scalar;
    }
}
void Array_double::operator/= ( double scalar ) {
    for( int i=0; i<get_dimension(); i++ ) {
        vector[i] /= scalar;
    }
}

// Privatelibrary
//-----------------------------------
void Array_double::setup_vector( int new_dimension ) {
    for( int i=0; i<new_dimension; i++ ) {
        vector.push_back(0);
    }
}
