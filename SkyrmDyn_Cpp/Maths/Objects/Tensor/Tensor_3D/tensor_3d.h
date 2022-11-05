#ifndef TENSOR_3D_H
#define TENSOR_3D_H

#include <vector>

class Tensor_3D
{
public:
    // Constructor
    //-----------------------------------
    Tensor_3D( int dimension );

    // Gettters
    //-----------------------------------
    std::vector< std::vector< std::vector< double > > > get_tensor();
    double get_tensor_component( int i, int j, int k );

    // Settters
    //-----------------------------------
    void set_tensor_component( int i, int j, int k, double &element );

private:
    std::vector< std::vector< std::vector< double > > > tensor;

    void setup_tensor( int dimension );
};

#endif // TENSOR_3D_H
