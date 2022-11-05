#include "vector_tensors.h"

#include "Maths/Objects/Matrix/Real_matrix/real_matrix.h"
#include "Maths/Objects/Tensor/Tensor_3D/tensor_3d.h"

Real_matrix Dot_tensor() {
    Real_matrix mat;
    for( int i=0; i<3; i++ ) {
        for( int j=0; j<3; j++ ) {
            if( i==j ) {
                double elmt = 1;
                mat.set_component( i, j, elmt );
            }
            else {
                double elmt = 0;
                mat.set_component( i, j, elmt );
            }
        }
    }
    return mat;
};

Tensor_3D Levi_Civita_tensor() {
    Tensor_3D cross( 3 );
    for( int i=0; i<3; i++ ) {
        for( int j=0; j<3; j++ ) {
            for( int k=0; k<3; k++ ) {
                if( ( i==0 && j==1 && k==2 ) || ( i==1 && j==2 && k==0 ) || ( i==2 && j==0 && k==1 ) ) {
                    double elmt = 1;
                    cross.set_tensor_component( i, j, k, elmt );
                }
                else if( ( i==2 && j==1 && k==0 ) || ( i==1 && j==0 && k==2 ) || ( i==0 && j==2 && k==1 ) ) {
                    double elmt = -1;
                    cross.set_tensor_component( i, j, k, elmt );
                }
                else {
                    double elmt = 0;
                    cross.set_tensor_component( i, j, k, elmt );
                }
            }
        }
    }
    return cross;
};

int Levi_Civita( int i, int j, int k ) {
    if( ( i==0 && j==1 && k==2 ) || ( i==1 && j==2 && k==0 ) || ( i==2 && j==0 && k==1 ) ) {
        return 1;
    }
    else if( ( i==2 && j==1 && k==0 ) || ( i==1 && j==0 && k==2 ) || ( i==0 && j==2 && k==1 ) ) {
        return -1;
    }
    else {
        return 0;
    }
}

int Levi_Civita_get_k( int i, int j ) {
    int k = 0;
    if( i==0 ) {
        if( j==1 ){
            k = 2;
        }
        else if( j== 2 ) {
            k = 1;
        }
    }
    else if( i==1 ) {
        if( j==0 ) {
            k = 2;
        }
        else if( j== 2 ) {
            k = 0;
        }
    }
    else {
        if( j==0 ) {
            k = 1;
        }
        else if( j== 1 ){
            k = 0;
        }
    }
    return k;
}

