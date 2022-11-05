#include "tensor_3d.h"

#include <vector>

// Constructor
//-----------------------------------
Tensor_3D::Tensor_3D( int dimension )
{
    setup_tensor( dimension );
}

// Gettters
//-----------------------------------
std::vector< std::vector< std::vector< double > > > Tensor_3D::get_tensor() {
    return tensor;
}
double Tensor_3D::get_tensor_component( int i, int j, int k ) {
    return tensor[i][j][k];
};

// Settters
//-----------------------------------
void Tensor_3D::set_tensor_component( int i, int j, int k, double &element ) {
    tensor[i][j][k] = element;
};

// Private libraries
//-----------------------------------
void Tensor_3D::setup_tensor( int dimension ) {
    for( int i=0; i<dimension; i++) {
        std::vector< std::vector< double > > tmp2;
        for( int j=0; j<dimension; j++) {
            std::vector< double > tmp;
            for( int k=0; k<dimension; k++) {
                tmp.push_back(0);
            }
            tmp2.push_back(tmp);
        }
        tensor.push_back(tmp2);
    }
}
