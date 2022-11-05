#include "Maths/Objects/Matrix/Real_matrix/real_matrix.h"

#include "Error_messages/error_messages.h"

void Real_matrix::inverse() {
    if( determinant() != 0 ) {
        if( dimension == 1 ){
            matrix[0][0] = 1 / matrix[0][0];
        }
        else if( dimension == 2 ) {
            // Use Kramer's formula
            double det = determinant();
            matrix[0][1] = -matrix[0][1]/det;
            matrix[1][0] = -matrix[1][0]/det;
            double tmp = matrix[0][0];
            matrix[0][0] = matrix[1][1]/det;
            matrix[1][1] = tmp/det;
        }
        else {
            // Use Gauss pivot algorithm
            // Creates identity matrix
            Real_matrix inverse_matrix( dimension );
            for( int i=0; i<dimension; i++ ) {
                for( int j=0; j<dimension; j++ ) {
                    if( i==j ) {
                        double element = 1;
                        inverse_matrix.set_component( i, j, element );
                    }
                    else {
                        double element = 0;
                        inverse_matrix.set_component( i, j, element );
                    }
                }
            }
            // Starts pivot line by line and upper tringularize
            for( int i=0; i<dimension; i++ ) {
                // pivot should not be zero
                if( matrix[i][i] != 0 ) {
                    double tmp_i = matrix[i][i];
                    multiply_lines_by_scalar( i, 1/tmp_i );
                    inverse_matrix.multiply_lines_by_scalar( i, 1/tmp_i );
                    for( int j=0; j<dimension; j++ ) {
                        if ( j != i ) {
                            if( matrix[j][i] != 0 ) {
                                double tmp_ij = matrix[j][i];
                                multiply_lines_by_scalar( j, 1/tmp_ij );
                                substract_lines( j, i );
                                inverse_matrix.multiply_lines_by_scalar( j, 1/tmp_ij );
                                inverse_matrix.substract_lines( j, i );
                            }
                        }
                    }
                }
                // if pivot is zero, exchange with the first non zero pivot below in the same column
                else {
                    int j=i+1;
                    while( j<=dimension ) {
                        if( matrix[i][j] != 0 ) {
                            exchange_lines( i, j );
                            inverse_matrix.exchange_lines( i, j );
                            break;
                        }
                        j++;
                    }
                    i--;
                }
            }
            for( int i=0; i<dimension; i++ ) {
                double tmp_i = matrix[i][i];
                multiply_lines_by_scalar( i, 1/tmp_i );
                inverse_matrix.multiply_lines_by_scalar( i, 1/tmp_i );
            }
            matrix = inverse_matrix.get_matrix();
        }
    }
    else {
        throw( OperationImpossible( "inverse", "matrix", "singular matrix of determinant 0" ) );
    }
}

void Real_matrix::add_lines( int i, int j ) {
    for( int k=0; k<(int) matrix[i].size(); k++ ) {
        matrix[i][k] += matrix[j][k];
    }
}
void Real_matrix::substract_lines( int i, int j ) {
    for( int k=0; k<(int) matrix[i].size(); k++ ) {
        matrix[i][k] -= matrix[j][k];
    }
}
void Real_matrix::multiply_lines_by_scalar( int i, double scalar ) {
    for( int k=0; k<(int) matrix[i].size(); k++ ) {
        matrix[i][k] *= scalar;
    }
}
void Real_matrix::exchange_lines( int i, int j ) {
    std::vector< double > tmp = matrix[i];
    matrix[i] = matrix[j];
    matrix[j] = tmp;
}
void Real_matrix::Gauss_substitution( int i, int j, double element ) {
    std::vector< double > tmp_line = matrix[j];
    multiply_lines_by_scalar( j, element );
    substract_lines( i, j );
    matrix[j] = tmp_line;
}
