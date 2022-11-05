#ifndef ARRAY_INT_H
#define ARRAY_INT_H

#include <vector>

class Array_int
{
public:
    // Constructor
    //-----------------------------------
    Array_int( int dimension );
    Array_int();

    // Getters
    //-----------------------------------
    int get_component( int i );
    int get_dimension();

    int get_x();
    int get_y();
    int get_z();

    // Setters
    //-----------------------------------
    void set_array( Array_int &new_array );
    void set_component( int i, int element );

    // Public libraries
    //-----------------------------------
    void add( Array_int array );
    void substract( Array_int array );
    void multiply_by_scalar( int scalar );

    bool operator== ( Array_int& rhs );
    bool operator!= ( Array_int& rhs );

    void operator+ ( Array_int& rhs );
    void operator+= ( Array_int& rhs );
    void operator- ( Array_int& rhs );
    void operator-= ( Array_int& rhs );

    void operator* ( double scalar );
    void operator*= ( double scalar );
    void operator/ ( double scalar );
    void operator/= ( double scalar );


private:
    std::vector<int> vector;

    void setup_vector( int new_dimenison );
};

#endif // ARRAY_INT_H
