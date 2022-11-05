#include "real_matrix.h"

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Error_messages/error_messages.h"

#include <vector>
#include <complex>

// Constructor
//-----------------------------------
Real_matrix::Real_matrix( int new_dimension )
{
    std::vector< std::vector< double > > tmp;
    for( int i=0; i<new_dimension; i++ ) {
        std::vector< double > tmp2;
        for( int j=0; j<new_dimension; j++ ) {
            tmp2.push_back(0);
        }
        tmp.push_back(tmp2);
    }
    matrix = tmp;
    dimension = new_dimension;
};
Real_matrix::Real_matrix() {
    std::vector< std::vector< double > > tmp;
    for( int i=0; i<3; i++ ) {
        std::vector< double > tmp2;
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
std::vector< std::vector< double > >& Real_matrix::get_matrix() {
    return matrix;
}
std::vector< std::vector< double > > Real_matrix::get_matrix_copy() {
    return matrix;
}

double& Real_matrix::get_component( int i, int j ) {
    return matrix[i][j];
}
double Real_matrix::get_component_copy( int i, int j ) {
    return matrix[i][j];
}

int Real_matrix::get_dimension() {
    return dimension;
}

Real_matrix Real_matrix::get_submatrix( int i, int j ) {
    Real_matrix sub_matrix( dimension - 1 );
    int p=0;
    int q=0;
    for( int n=0; n<dimension; n++ ) {
        for( int k=0; k<dimension; k++ ) {
            if( i!=n && j!=k ) {
                double element = get_component( n, k );
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
void Real_matrix::set_component( int i, int j, double &element ) {
    matrix[i][j] = element;
}

// Public library
//-----------------------------------
void Real_matrix::transpose() {
    std::vector< std::vector< double > > tmp = matrix;
    int dim = sizeof(matrix)/sizeof(matrix[0]);
    for( int i=0; i<dim; i++ ) {
        for( int j=0; j<dim; j++ ) {
            matrix[i][j] = tmp[j][i];
        }
    }
}

double Real_matrix::determinant() {
    double det;
    if( dimension == 1 ) {
        det = get_component(0,0);
    }
    else if( dimension == 2 ) {
        det = get_component(0,0)*get_component(1,1) -                get_component(0,1)*get_component(1,0);
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
            Real_matrix sub_matrix( dimension - 1 );
            det += get_component( i, 0 )*sub_matrix.determinant();
        }
    }
    return det;
}

//void Real_matrix::inverse() {
//    Real_matrix inv_tmp(dimension);
//    std::vector< std::vector< double > > inv = inv_tmp.get_matrix();
//    double det = determinant();
//    if( det != 0 ) {
//        for( int i=0; i<dimension; i++ ) {
//            for( int j=0; j<dimension; j++ ) {
//                Real_matrix sub_matrix = get_submatrix( i, j );
//                double element = sub_matrix.determinant() / det * pow( -1, i+j );
//                inv[i][j] = element;
//            }
//        }
//        matrix = inv;
//    }
//    else {
//        throw( OperationImpossible( "inverting", "zero matrix determinant", "singular matrix" ) );
//    }
//}

Array_double Real_matrix::multiply_right_by_array_double( Array_double &vector ) {
    int dim = vector.get_dimension();
    Array_double result(dim);
    for( int i=0; i<dim; i++ ) {
        double tmp = 0;
        for( int j=0; j<dim; j++ ) {
            tmp += vector.get_component(j)*get_component(i,j);
        }
        result.set_component(i, tmp);
    }
    return result;
}

Array_double Real_matrix::multiply_left_by_array_double( Array_double &vector ) {
    int dim = vector.get_dimension();
    Array_double result(dim);
    for( int i=0; i<3; i++ ) {
        double tmp = 0;
        for( int j=0; j<dim; j++ ) {
            tmp += vector.get_component(j)*get_component(j,i);
        }
        result.set_component(i, tmp);
    }
    return result;
}

// Operators
//-----------------------------------
void Real_matrix::operator=( Real_matrix& other ) {
    int dim = other.get_dimension();
    std::vector< std::vector< double > > other_matrix = other.get_matrix();
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

void Real_matrix::operator+( Real_matrix& other ) {
    int dim = other.get_dimension();
    std::vector< std::vector< double > > other_matrix = other.get_matrix();
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
void Real_matrix::operator-( Real_matrix& other ) {
    int dim = other.get_dimension();
    std::vector< std::vector< double > > other_matrix = other.get_matrix();
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

void Real_matrix::operator+=( Real_matrix& other ) {
    int dim = other.get_dimension();
    std::vector< std::vector< double > > other_matrix = other.get_matrix();
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
void Real_matrix::operator-=( Real_matrix& other ) {
    int dim = other.get_dimension();
    std::vector< std::vector< double > > other_matrix = other.get_matrix();
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

void Real_matrix::operator*( Real_matrix& other ) {
    std::vector< std::vector< double > > other_matrix = other.get_matrix();
    int dim = other.get_dimension();
    if( dim == dimension ) {
        std::vector< std::vector< double > > new_matrix( other_matrix );
        for( int a=0; a<dimension; a++ ) {
            for( int b=0; b<dimension; b++ ) {
                double element = 0;
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
void Real_matrix::operator*=( Real_matrix& other ) {
    std::vector< std::vector< double > > other_matrix = other.get_matrix();
    int dim = other.get_dimension();
    if( dim == dimension ) {
        std::vector< std::vector< double > > new_matrix( other_matrix );
        for( int a=0; a<dimension; a++ ) {
            for( int b=0; b<dimension; b++ ) {
                double element = 0;
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

void Real_matrix::operator/( Real_matrix& other ) {
    other.inverse();
    std::vector< std::vector< double > > other_matrix = other.get_matrix();
    int dim = other.get_dimension();
    if( dim == dimension ) {
        std::vector< std::vector< double > > new_matrix( other_matrix );
        for( int a=0; a<dimension; a++ ) {
            for( int b=0; b<dimension; b++ ) {
                double element = 0;
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
void Real_matrix::operator/=( Real_matrix& other ) {
    other.inverse();
    std::vector< std::vector< double > > other_matrix = other.get_matrix();
    int dim = other.get_dimension();
    if( dim == dimension ) {
        std::vector< std::vector< double > > new_matrix( other_matrix );
        for( int a=0; a<dimension; a++ ) {
            for( int b=0; b<dimension; b++ ) {
                double element = 0;
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

void Real_matrix::operator^( int p ) {
    if( p<0 ) {
        inverse();
        for( int k=0; k<p; k-- ) {
            std::vector< std::vector< double > > new_matrix( dimension );
            for( int a=0; a<dimension; a++ ) {
                for( int b=0; b<dimension; b++ ) {
                    double element = 0;
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
            std::vector< std::vector< double > > new_matrix( dimension );
            for( int a=0; a<dimension; a++ ) {
                for( int b=0; b<dimension; b++ ) {
                    double element = 0;
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

// Private library
//-----------------------------------

