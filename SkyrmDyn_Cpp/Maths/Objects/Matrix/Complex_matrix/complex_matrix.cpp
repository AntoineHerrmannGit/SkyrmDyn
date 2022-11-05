#include "complex_matrix.h"

#include "Error_messages/error_messages.h"

#include <vector>
#include <complex>

// Constructor
//-----------------------------------
Complex_matrix::Complex_matrix( int new_dimension )
{
    std::vector< std::vector< std::complex< double > > > tmp;
    for( int i=0; i<new_dimension; i++ ) {
        std::vector< std::complex< double > > tmp2;
        for( int j=0; j<new_dimension; j++ ) {
            tmp2.push_back(0);
        }
        tmp.push_back(tmp2);
    }
    matrix = tmp;
    dimension = new_dimension;
};
Complex_matrix::Complex_matrix() {
    std::vector< std::vector< std::complex< double > > > tmp;
    for( int i=0; i<3; i++ ) {
        std::vector< std::complex< double > > tmp2;
        for( int j=0; j<3; j++ ) {
            if( i==j ) {
                tmp2.push_back(1);
            }
            else {
                tmp2.push_back(0);
            }
        }
        tmp.push_back(tmp2);
    }
    matrix = tmp;
    dimension = 3;
}

// Gettters
//-----------------------------------
std::vector< std::vector< std::complex< double > > >& Complex_matrix::get_matrix() {
    return matrix;
}
std::vector< std::vector< std::complex< double > > > Complex_matrix::get_matrix_copy() {
    return matrix;
}

std::complex< double >& Complex_matrix::get_component( int i, int j ) {
    return matrix[i][j];
}
std::complex< double > Complex_matrix::get_component_copy( int i, int j ) {
    return matrix[i][j];
}

int Complex_matrix::get_dimension() {
    return dimension;
}

Complex_matrix Complex_matrix::get_submatrix( int i, int j ) {
    Complex_matrix sub_matrix( dimension - 1 );
    int p=0;
    int q=0;
    for( int n=0; n<dimension; n++ ) {
        for( int k=0; k<dimension; k++ ) {
            if( i!=n && j!=k ) {
                std::complex< double > element = get_component( n, k );
                sub_matrix.set_component( p, q, element );
                q++;
            }
            if( q == dimension - 1 ) {
                q = 0;
                p++;
            }
        }
    }
    return sub_matrix;
}

// Settters
//-----------------------------------
void Complex_matrix::set_component( int i, int j, std::complex< double > &element ) {
    matrix[i][j] = element;
}

// Public Library
//-----------------------------------
void Complex_matrix::transpose() {
    std::vector< std::vector< std::complex< double > > > tmp = matrix;
    int dim = sizeof(matrix)/sizeof(matrix[0]);
    for( int i=0; i<dim; i++ ) {
        for( int j=0; j<dim; j++ ) {
            matrix[i][j] = tmp[j][i];
        }
    }
}

void Complex_matrix::hermitian_conjugate() {
    std::vector< std::vector< std::complex< double > > > tmp = matrix;
    int dim = sizeof(matrix)/sizeof(matrix[0]);
    for( int i=0; i<dim; i++ ) {
        for( int j=0; j<dim; j++ ) {
            matrix[i][j] = std::conj( tmp[j][i] );
        }
    }
}

std::complex< double > Complex_matrix::determinant() {
    std::complex< double > det;
    if( dimension == 1 ) {
        det = get_component(0,0);
    }
    else if( dimension == 2 ) {
        det = get_component(0,0)*get_component(1,1)
            - get_component(0,1)*get_component(1,0);
    }
    else if( dimension == 3 ) {
        det = get_component(0,0)*get_component(1,1)*get_component(2,2)
            + get_component(1,0)*get_component(2,1)*get_component(0,2)
            + get_component(2,0)*get_component(0,1)*get_component(1,2)
            - get_component(0,2)*get_component(1,1)*get_component(2,0)
            - get_component(0,1)*get_component(1,0)*get_component(2,2)
            - get_component(0,0)*get_component(1,2)*get_component(2,1);
    }
    else {
        det = 0;
        for( int i=0; i<dimension; i++ ) {
            Complex_matrix sub_matrix = get_submatrix( i, 0 );
            det += get_component( i, 0 )*sub_matrix.determinant();
        }
    }
    return det;
}

void Complex_matrix::inverse() {
    Complex_matrix inv_tmp(dimension);
    std::vector< std::vector< std::complex< double > > > inv = inv_tmp.get_matrix();
    std::complex< double > det = determinant();
    if( det != (std::complex< double >) 0 ) {
        for( int i=0; i<dimension; i++ ) {
            for( int j=0; j<dimension; j++ ) {
                Complex_matrix sub_matrix = get_submatrix( i, j );
                std::complex< double > element = sub_matrix.determinant() / det;
                inv[i][j] = element;
            }
        }
        matrix = inv;
    }
    else {
        throw( OperationImpossible( "inverting", "zero matrix determinant", "singular matrix" ) );
    }
}

// Operators
//-----------------------------------
void Complex_matrix::operator=( Complex_matrix& other ) {
    int dim = other.get_dimension();
    std::vector< std::vector< std::complex< double > > > other_matrix = other.get_matrix();
    if( dim == dimension ) {
        for( int a=0; a<dimension; a++ ) {
            for( int b=0; b<dimension; b++ ) {
                matrix[a][b] = other_matrix[a][b];
            }
        }
    }
    else {
        throw( AssignationError( "other matrix" ) );
    }
}

void Complex_matrix::operator+( Complex_matrix& other ) {
    int dim = other.get_dimension();
    std::vector< std::vector< std::complex< double > > > other_matrix = other.get_matrix();
    if( dim == dimension ) {
        for( int a=0; a<dimension; a++ ) {
            for( int b=0; b<dimension; b++ ) {
                matrix[a][b] += other_matrix[a][b];
            }
        }
    }
    else {
        throw( AssignationError( "other matrix" ) );
    }
}
void Complex_matrix::operator-( Complex_matrix& other ) {
    int dim = other.get_dimension();
    std::vector< std::vector< std::complex< double > > > other_matrix = other.get_matrix();
    if( dim == dimension ) {
        for( int a=0; a<dimension; a++ ) {
            for( int b=0; b<dimension; b++ ) {
                matrix[a][b] -= other_matrix[a][b];
            }
        }
    }
    else {
        throw( AssignationError( "other matrix" ) );
    }
}

void Complex_matrix::operator+=( Complex_matrix& other ) {
    int dim = other.get_dimension();
    std::vector< std::vector< std::complex< double > > > other_matrix = other.get_matrix();
    if( dim == dimension ) {
        for( int a=0; a<dimension; a++ ) {
            for( int b=0; b<dimension; b++ ) {
                matrix[a][b] += other_matrix[a][b];
            }
        }
    }
    else {
        throw( AssignationError( "other matrix" ) );
    }
}
void Complex_matrix::operator-=( Complex_matrix& other ) {
    int dim = other.get_dimension();
    std::vector< std::vector< std::complex< double > > > other_matrix = other.get_matrix();
    if( dim == dimension ) {
        for( int a=0; a<dimension; a++ ) {
            for( int b=0; b<dimension; b++ ) {
                matrix[a][b] -= other_matrix[a][b];
            }
        }
    }
    else {
        throw( AssignationError( "other matrix" ) );
    }
}

void Complex_matrix::operator*( Complex_matrix& other ) {
    int dim = other.get_dimension();
    if( dim == dimension ) {
        std::vector< std::vector< std::complex< double > > > other_matrix = other.get_matrix();
        std::vector< std::vector< std::complex< double > > > new_matrix( other_matrix );
        for( int a=0; a<dimension; a++ ) {
            for( int b=0; b<dimension; b++ ) {
                std::complex< double > element = 0;
                for( int i=0; i<dimension; i++ ) {
                    element += matrix[a][i]*other_matrix[i][b];
                }
                new_matrix[a][b] = element;
            }
        }
        matrix = new_matrix;
    }
    else {
        throw( AssignationError( "right matrix" ) );
    }
}
void Complex_matrix::operator*=( Complex_matrix& other ) {
    int dim = other.get_dimension();
    if( dim == dimension ) {
        std::vector< std::vector< std::complex< double > > > other_matrix = other.get_matrix();
        std::vector< std::vector< std::complex< double > > > new_matrix( other_matrix );
        for( int a=0; a<dimension; a++ ) {
            for( int b=0; b<dimension; b++ ) {
                std::complex< double > element = 0;
                for( int i=0; i<dimension; i++ ) {
                    element += matrix[a][i]*other_matrix[i][b];
                }
                new_matrix[a][b] = element;
            }
        }
        matrix = new_matrix;
    }
    else {
        throw( AssignationError( "right matrix" ) );
    }
}

void Complex_matrix::operator/( Complex_matrix& other ) {
    int dim = other.get_dimension();
    if( dim == dimension ) {
        other.inverse();
        std::vector< std::vector< std::complex< double > > > other_matrix = other.get_matrix();
        std::vector< std::vector< std::complex< double > > > new_matrix( other_matrix );
        for( int a=0; a<dimension; a++ ) {
            for( int b=0; b<dimension; b++ ) {
                std::complex< double > element = 0;
                for( int i=0; i<dimension; i++ ) {
                    element += matrix[a][i]*other_matrix[i][b];
                }
                new_matrix[a][b] = element;
            }
        }
        matrix = new_matrix;
    }
    else {
        throw( AssignationError( "right matrix" ) );
    }
}
void Complex_matrix::operator/=( Complex_matrix& other ) {
    int dim = other.get_dimension();
    if( dim == dimension ) {
        other.inverse();
        std::vector< std::vector< std::complex< double > > > other_matrix = other.get_matrix();
        std::vector< std::vector< std::complex< double > > > new_matrix( other_matrix );
        for( int a=0; a<dimension; a++ ) {
            for( int b=0; b<dimension; b++ ) {
                std::complex< double > element = 0;
                for( int i=0; i<dimension; i++ ) {
                    element += matrix[a][i]*other_matrix[i][b];
                }
                new_matrix[a][b] = element;
            }
        }
        matrix = new_matrix;
    }
    else {
        throw( AssignationError( "right matrix" ) );
    }
}

void Complex_matrix::operator^( int p ) {
    if( p<0 ) {
        inverse();
        for( int k=0; k<p; k-- ) {
            std::vector< std::vector< std::complex< double > > > new_matrix( dimension );
            for( int a=0; a<dimension; a++ ) {
                for( int b=0; b<dimension; b++ ) {
                    std::complex< double > element = 0;
                    for( int i=0; i<dimension; i++ ) {
                        element += matrix[a][i]*matrix[i][b];
                    }
                    new_matrix[a][b] = element;
                }
            }
            matrix = new_matrix;
        }
    }
    else if( p>0 ) {
        for( int k=0; k<p; k-- ) {
            std::vector< std::vector< std::complex< double > > > new_matrix( dimension );
            for( int a=0; a<dimension; a++ ) {
                for( int b=0; b<dimension; b++ ) {
                    std::complex< double > element = 0;
                    for( int i=0; i<dimension; i++ ) {
                        element += matrix[a][i]*matrix[i][b];
                    }
                    new_matrix[a][b] = element;
                }
            }
            matrix = new_matrix;
        }
    }
    else if( p==0 ) {
        for( int k=0; k<p; k-- ) {
            for( int a=0; a<dimension; a++ ) {
                for( int b=0; b<dimension; b++ ) {
                    if( a==b ) {
                        matrix[a][b] = 1;
                    }
                    else {
                        matrix[a][b] = 0;
                    }
                }
            }
        }
    }
    else {
        throw( AssignationError( "power" ) );
    }
}

