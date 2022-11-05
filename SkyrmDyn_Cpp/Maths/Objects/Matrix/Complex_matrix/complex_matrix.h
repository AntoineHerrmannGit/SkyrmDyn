#ifndef COMPLEX_MATRIX_H
#define COMPLEX_MATRIX_H

#include <vector>
#include <complex>

class Complex_matrix
{
public:
    // Constructor
    //-----------------------------------
    Complex_matrix( int new_dimension );
    Complex_matrix();

    // Gettters
    //-----------------------------------
    std::vector< std::vector< std::complex< double > > >& get_matrix();
    std::vector< std::vector< std::complex< double > > > get_matrix_copy();

    std::complex< double >& get_component( int i, int j );
    std::complex< double > get_component_copy( int i, int j );

    int get_dimension();

    Complex_matrix get_submatrix( int i, int j );

    // Settters
    //-----------------------------------
    void set_component( int i, int j, std::complex< double > &element );

    // Public library
    //-----------------------------------
    std::complex< double > determinant();
    void inverse();
    void transpose();
    void hermitian_conjugate();

    // Operators
    //-----------------------------------
    void operator=( Complex_matrix& other );

    void operator+( Complex_matrix& other );
    void operator+=( Complex_matrix& other );

    void operator-( Complex_matrix& other );
    void operator-=( Complex_matrix& other );

    void operator*( Complex_matrix& other );
    void operator*=( Complex_matrix& other );

    void operator/( Complex_matrix& other );
    void operator/=( Complex_matrix& other );

    void operator^( int p );

private:
    std::vector< std::vector< std::complex< double > > > matrix;
    int dimension = 0;
};

#endif // COMPLEX_MATRIX_H
