#ifndef ARRAY_FLOAT_H
#define ARRAY_FLOAT_H

#include "Maths/Objects/Array/Array_int/array_int.h"

#include <vector>

class Array_float
{
public:
    // Constructor
    //-----------------------------------
    Array_float( int dimension );
    Array_float();

    // Getters
    //-----------------------------------
    float get_component( int i );
    int get_dimension();

    float get_x();
    float get_y();
    float get_z();

    // Setters
    //-----------------------------------
    void set_array( Array_float &new_array );
    void set_component( int i, float element );

    // Public libraries
    //-----------------------------------
    void normalize();
    void add( Array_float array );
    void substract( Array_float array );
    void multiply_by_scalar( float scalar );

    bool operator== ( Array_float& rhs );
    bool operator!= ( Array_float& rhs );

    void operator+ ( Array_float& rhs );
    void operator+= ( Array_float& rhs );
    void operator- ( Array_float& rhs );
    void operator-= ( Array_float& rhs );
    void operator+ ( Array_int& rhs );
    void operator+= ( Array_int& rhs );
    void operator- ( Array_int& rhs );
    void operator-= ( Array_int& rhs );
    void operator* ( double scalar );
    void operator*= ( double scalar );
    void operator/ ( double scalar );
    void operator/= ( double scalar );


private:
    std::vector<float> vector;

    void setup_vector( int new_dimenison );
};

#endif // ARRAY_FLOAT_H
