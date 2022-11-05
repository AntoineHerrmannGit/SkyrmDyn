#include "Objects/Cell/cell.h"

#include <math.h>

void Cell::setup_position( std::string &lattice_name, Array_int &new_position ) {
    if( lattice_name == "1D_chain" || lattice_name == "2D_square" || lattice_name == "2D_centered_square"
        || lattice_name == "3D_simple_cubic" || lattice_name == "3D_FCC" || lattice_name == "3D_BCC" || lattice_name == "3D_diamond" ) {

        Array_double tmp( 3 );
        tmp.set_component( 0, new_position.get_x() );
        tmp.set_component( 1, new_position.get_y() );
        tmp.set_component( 2, new_position.get_z() );
        position = tmp;
    }

    else if( lattice_name == "2D_triangular" ) {
        position.set_component( 0, 2*new_position.get_x() );
        position.set_component( 1, sqrt(3)*new_position.get_y() );
        position.set_component( 2, new_position.get_z() );
    }
    else if( lattice_name == "2D_honeycomb" || lattice_name == "3D_straight_honeycomb" ) {
        Array_double tmp( 3 );
        tmp.set_component( 0, sqrt(3)*new_position.get_x() );
        tmp.set_component( 1, 3*new_position.get_y() );
        tmp.set_component( 2, new_position.get_z() );
        position = tmp;
    }

    else if( lattice_name == "3D_triangular" ) {
        Array_double tmp( 3 );
        tmp.set_component( 0, 2*new_position.get_x() );
        tmp.set_component( 1, sqrt(3)*new_position.get_y() );
        tmp.set_component( 2, sqrt(5)*new_position.get_z() );
        position = tmp;
    }
    else if( lattice_name == "3D_staggered_honeycomb" ) {
        Array_double tmp( 3 );
        tmp.set_component( 0, sqrt(3)*new_position.get_x() );
        tmp.set_component( 1, 3*new_position.get_y() );
        tmp.set_component( 2, sqrt(3)*new_position.get_z() );
        position = tmp;
    }
}




