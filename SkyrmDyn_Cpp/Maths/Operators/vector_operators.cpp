#include "vector_operators.h"

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Maths/Objects/Tensor/Tensor_3D/tensor_3d.h"
#include "Maths/Objects/Tensor/Vector_tensor/vector_tensors.h"

#include "Error_messages/error_messages.h"

#include <math.h>

double dot( Array_double v1, Array_double v2 ) {
    if( v1.get_dimension() == v2.get_dimension() ) {
        int dim = v1.get_dimension();
        double scalar = 0;
        for( int i=0; i<dim; i++ ) {
            scalar += v1.get_component( i )*v2.get_component( i );
        }
        return scalar;
    }
    else {
        throw( OperationImpossible( "dot product", "vector", "different size" ) );
    }
}

Array_double cross( Array_double v1, Array_double v2 ) {
    Array_double cross_vect( v1.get_dimension() );
    if( v1.get_dimension() == v2.get_dimension() ) {
        int dim = v1.get_dimension();
        for( int i=0; i<dim-2; i++) {
            double element = v1.get_component( i+1 ) * v2.get_component( i+2 )
                           - v1.get_component( i+2 ) * v2.get_component( i+1 );
            cross_vect.set_component( i, element );
        }
        double element = v1.get_component( dim-1 ) * v2.get_component( 0 )
                       - v1.get_component( 0 ) * v2.get_component( dim-1 );
        cross_vect.set_component( dim-2, element );

        element = v1.get_component( 0 ) * v2.get_component( 1 )
                - v1.get_component( 1 ) * v2.get_component( 0 );
        cross_vect.set_component( dim-1, element );

        return cross_vect;
    }
    else {
        throw( OperationImpossible( "cross product", "vectors", "different size" ) );
    }
}


void rotate( Array_double& vector, Array_double axis, double angle ) {
    axis.normalize();

    double r_xx = cos( angle ) + ( 1-cos( angle ) ) * axis.get_x() * axis.get_x();
    double r_xy = ( 1-cos( angle ) ) * axis.get_x() * axis.get_y() - axis.get_z() * sin( angle );
    double r_xz = ( 1-cos( angle ) ) * axis.get_x() * axis.get_z() + axis.get_y() * sin( angle );

    double r_yx = ( 1-cos( angle ) ) * axis.get_x() * axis.get_y() + axis.get_z() * sin( angle );
    double r_yy = cos( angle ) + ( 1-cos( angle ) ) * axis.get_y() * axis.get_y();
    double r_yz = ( 1-cos( angle ) ) * axis.get_z() * axis.get_y() - axis.get_x() * sin( angle );

    double r_zx = ( 1-cos( angle ) ) * axis.get_x() * axis.get_z() - axis.get_y() * sin( angle );
    double r_zy = ( 1-cos( angle ) ) * axis.get_z() * axis.get_y() + axis.get_x() * sin( angle );
    double r_zz = cos( angle ) + ( 1-cos( angle ) ) * axis.get_z() * axis.get_z();

    Real_matrix rot(3);
    rot.set_component( 0, 0, r_xx );
    rot.set_component( 0, 1, r_xy );
    rot.set_component( 0, 2, r_xz );

    rot.set_component( 1, 1, r_yx );
    rot.set_component( 1, 1, r_yy );
    rot.set_component( 1, 2, r_yz );

    rot.set_component( 0, 2, r_zx );
    rot.set_component( 1, 2, r_zy );
    rot.set_component( 2, 2, r_zz );

    vector = rot.multiply_right_by_array_double( vector );
}

std::vector< Array_double > orthonormal_basis( Array_double vect1, Array_double vect2 ) {
    vect1.normalize();
    double shadow = dot( vect1, vect2 );
    Array_double tmp = vect1;
    tmp.multiply_by_scalar( shadow );
    vect2.substract( tmp );
    vect2.normalize();
    Array_double vect3 = cross( vect1, vect2 );
    std::vector< Array_double > result;
    result.push_back( vect1 );
    result.push_back( vect2 );
    result.push_back( vect3 );
    return result;
}


Array_double average_vector( std::vector< Array_double > vectors ) {
    Array_double average;
    int n=0;
    for( Array_double vector : vectors ) {
        average.add( vector );
        n++;
    }
    average.multiply_by_scalar( 1/n );
    return average;
}


