#ifndef VECTOR_TENSORS_H
#define VECTOR_TENSORS_H

#include "Maths/Objects/Matrix/Real_matrix/real_matrix.h"
#include "Maths/Objects/Tensor/Tensor_3D/tensor_3d.h"

Real_matrix Dot_tensor();
Tensor_3D Levi_Civita_tensor();
int Levi_Civita( int i, int j, int k );
int Levi_Civita_get_k( int i, int j );

#endif // VECTOR_TENSORS_H
