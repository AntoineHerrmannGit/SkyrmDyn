#ifndef ARRAY_DOUBLE_H
#define ARRAY_DOUBLE_H

#include "Maths/Objects/Array/Array_float/array_float.h"
#include "Maths/Objects/Array/Array_int/array_int.h"

#include <vector>

class Array_double
{
public:
    // Constructor
    //-----------------------------------
    Array_double( int new_dimension );
    Array_double();

    // Getters
    //-----------------------------------
    double get_component( int i );
    int get_dimension();

    double get_x();
    double get_y();
    double get_z();

    // Setters
    //-----------------------------------
    void set_array( Array_double &new_array );
    void set_component( int i, double element );

    // Public libraries
    //-----------------------------------
    double norm();
    void normalize();
    void add( Array_double array );
    void substract( Array_double array );
    void multiply_by_scalar( double scalar );

    bool operator== ( Array_double& rhs );
    bool operator!= ( Array_double& rhs );
    bool is_equal( Array_double& rhs );
    bool is_not_equal( Array_double& rhs );

    void operator+ ( Array_double& rhs );
    void operator+= ( Array_double& rhs );
    void operator- ( Array_double& rhs );
    void operator-= ( Array_double& rhs );

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
    std::vector<double> vector;

    void setup_vector( int new_dimenison );
};

#endif // ARRAY_DOUBLE_H
