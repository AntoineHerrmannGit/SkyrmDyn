#ifndef REAL_MATRIX_H
#define REAL_MATRIX_H

#include "Maths/Objects/Array/Array_double/array_double.h"
#include "Maths/Objects/Matrix/Complex_matrix/complex_matrix.h"

#include <vector>

class Real_matrix
{
public:
    // Constructor
    //-----------------------------------
    Real_matrix( int dimension );
    Real_matrix();

    // Gettters
    //-----------------------------------
    std::vector< std::vector< double > >& get_matrix();
    std::vector< std::vector< double > > get_matrix_copy();

    double& get_component( int i, int j );
    double get_component_copy( int i, int j );

    int get_dimension();

    Real_matrix get_submatrix( int i, int j );

    // Settters
    //-----------------------------------
    void set_component( int i, int j, double &element );

    // Public libraries
    //-----------------------------------
    void transpose();
    double determinant();
    void inverse();

    Array_double multiply_right_by_array_double( Array_double& vector );
    Array_double multiply_left_by_array_double( Array_double& vector );

    Complex_matrix multiply_right_by_complex_matrix( Complex_matrix& rhs_matrix );
    Complex_matrix multiply_left_by_complex_matrix( Complex_matrix& lhs_matrix );

    // Operators
    //-----------------------------------
    void operator=( Real_matrix& other );

    void operator+( Real_matrix& other );
    void operator+=( Real_matrix& other );

    void operator-( Real_matrix& other );
    void operator-=( Real_matrix& other );

    void operator*( Real_matrix& other );
    void operator*=( Real_matrix& other );

    void operator/( Real_matrix& other );
    void operator/=( Real_matrix& other );

    void operator^( int p );

    // Internal libraries
    //-----------------------------------
    void add_lines( int i, int j );
    void substract_lines( int i, int j );
    void multiply_lines_by_scalar( int i, double scalar );
    void exchange_lines( int i, int j );
    void Gauss_substitution( int i, int j, double element );

private:
    std::vector< std::vector< double > > matrix;
    int dimension = 0;

};

#endif // REAL_MATRIX_H
