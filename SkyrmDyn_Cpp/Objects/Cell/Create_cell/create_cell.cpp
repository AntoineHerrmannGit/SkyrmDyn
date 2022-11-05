#include "Objects/Cell/cell.h"

#include "Error_messages/error_messages.h"

#include <math.h>

void Cell::setup_cell( std::string &lattice_name ) {
    if( lattice_name == "1D_chain" ) {
        create_3D_simple_cubic();
    }
    else if( lattice_name == "2D_square" ) {
        create_3D_simple_cubic();
    }
    else if( lattice_name == "2D_centered_square" ) {
        create_2D_centered_square();
    }
    else if( lattice_name == "2D_triangular" ) {
        create_2D_triangular();
    }
    else if( lattice_name == "2D_honeycomb" ) {
        create_3D_straight_honeycomb();
    }
    else if( lattice_name == "3D_simple_cubic" ) {
        create_3D_simple_cubic();
    }
    else if( lattice_name == "3D_FCC" ) {
        create_3D_FCC();
    }
    else if( lattice_name == "3D_BCC" ) {
        create_3D_BCC();
    }
    else if( lattice_name == "3D_diamond" ) {
        create_3D_dimond();
    }
    else if( lattice_name == "3D_triangular" ) {
        create_3D_triangular();
    }
    else if( lattice_name == "3D_straight_honeycomb" ) {
        create_3D_straight_honeycomb();
    }
    else if( lattice_name == "3D_staggered_honeycomb" ) {
        create_3D_staggered_honeycomb();
    }
    else {
        throw ( AssignationError( "lattice_name" ) );
    }
}


void Cell::create_3D_simple_cubic() {
    cell.push_back( create_atom( position.get_component(0) + 0.5, position.get_component(1) + 0.5, position.get_component(2) + 0.5, 0, 0, 1 ) );
    nb_atoms = 1;
}

void Cell::create_3D_FCC() {
    cell.push_back( create_atom( position.get_component(0) + 0.25, position.get_component(1) + 0.25, position.get_component(2) + 0.25, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 0.25, position.get_component(1) + 0.75, position.get_component(2) + 0.75, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 0.75, position.get_component(1) + 0.25, position.get_component(2) + 0.75, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 0.75, position.get_component(1) + 0.75, position.get_component(2) + 0.25, 0, 0, 1 ) );
    nb_atoms = 4;
}

void Cell::create_3D_BCC() {
    cell.push_back( create_atom( position.get_component(0) + 0.25, position.get_component(1) + 0.25, position.get_component(2) + 0.25, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 0.75, position.get_component(1) + 0.75, position.get_component(2) + 0.75, 0, 0, 1 ) );
    nb_atoms = 2;
}

void Cell::create_3D_dimond() {
    cell.push_back( create_atom( position.get_component(0) + 0.125, position.get_component(1) + 0.125, position.get_component(2) + 0.125, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 0.625, position.get_component(1) + 0.625, position.get_component(2) + 0.125, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 0.625, position.get_component(1) + 0.125, position.get_component(2) + 0.625, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 0.125, position.get_component(1) + 0.625, position.get_component(2) + 0.625, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 0.375, position.get_component(1) + 0.375, position.get_component(2) + 0.375, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 0.875, position.get_component(1) + 0.875, position.get_component(2) + 0.375, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 0.875, position.get_component(1) + 0.375, position.get_component(2) + 0.875, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 0.375, position.get_component(1) + 0.875, position.get_component(2) + 0.875, 0, 0, 1 ) );
    nb_atoms = 8;
}


void Cell::create_3D_straight_honeycomb() {
    cell.push_back( create_atom( position.get_component(0) + sqrt( 3 )*3.0/4.0, position.get_component(1) + 0.5, position.get_component(2) + 0.5, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + sqrt( 3 )/4.0, position.get_component(1) + 1, position.get_component(2) + 0.5, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + sqrt( 3 )/4.0, position.get_component(1) + 2, position.get_component(2) + 0.5, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + sqrt( 3 )*3.0/4.0, position.get_component(1) + 2.5, position.get_component(2) + 0.5, 0, 0, 1 ) );
    nb_atoms = 4;
}

void Cell::create_3D_staggered_honeycomb() {
    // Lower layer
    cell.push_back( create_atom( position.get_component(0) + sqrt( 3 )*3.0/4.0, position.get_component(1) + 0.5, position.get_component(2) + 0.75*sqrt( 3 ), 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + sqrt( 3 )/4.0, position.get_component(1) + 1, position.get_component(2) + 0.75*sqrt( 3 ), 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + sqrt( 3 )/4.0, position.get_component(1) + 2, position.get_component(2) + 0.75*sqrt( 3 ), 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + sqrt( 3 )*3.0/4.0, position.get_component(1) + 2.5, position.get_component(2) + 0.75*sqrt( 3 ), 0, 0, 1 ) );

    // Upper layer
    cell.push_back( create_atom( position.get_component(0) + sqrt( 3 )/4.0, position.get_component(1) + 0.5, position.get_component(2) + 0.75*sqrt( 3 ), 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + sqrt( 3 )*3.0/4.0, position.get_component(1) + 1, position.get_component(2) + 0.25*sqrt( 3 ), 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + sqrt( 3 )*3.0/4.0, position.get_component(1) + 2, position.get_component(2) + 0.25*sqrt( 3 ), 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + sqrt( 3 )/4.0, position.get_component(1) + 2.5, position.get_component(2) + 0.25*sqrt( 3 ), 0, 0, 1 ) );
    nb_atoms = 8;
}

void Cell::create_3D_triangular() {
    // Lower layer
    cell.push_back( create_atom( position.get_component(0) + 0.25, position.get_component(1) + sqrt( 3 )/12.0, position.get_component(2) + sqrt(5)/6.0, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 1.25, position.get_component(1) + sqrt( 3 )/12.0, position.get_component(2) + sqrt(5)/6.0, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 1.75, position.get_component(1) + sqrt( 3 )*7.0/12.0, position.get_component(2) + sqrt(5)/6.0, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 0.75, position.get_component(1) + sqrt( 3 )*7.0/12.0, position.get_component(2) + sqrt(5)/6.0, 0, 0, 1 ) );

    // Middle layer
    cell.push_back( create_atom( position.get_component(0) + 0.75, position.get_component(1) + sqrt( 3 )/4.0, position.get_component(2) + 0.5*sqrt(5), 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 1.75, position.get_component(1) + sqrt( 3 )/4.0, position.get_component(2) + 0.5*sqrt(5), 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 0.25, position.get_component(1) + 1 + sqrt( 3 )*3.0/4.0, position.get_component(2) + 0.5*sqrt(5), 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 1.25, position.get_component(1) + 1 + sqrt( 3 )*3.0/4.0, position.get_component(2) + 0.5*sqrt(5), 0, 0, 1 ) );

    // Upper layer
    cell.push_back( create_atom( position.get_component(0) + 0.25, position.get_component(1) + sqrt( 3 )*5.0/12.0, position.get_component(2) + sqrt(5)*5.0/6.0, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 1.25, position.get_component(1) + sqrt( 3 )*5.0/12.0, position.get_component(2) + sqrt(5)*5.0/6.0, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 1.75, position.get_component(1) + 1 + sqrt( 3 )*11.0/12.0, position.get_component(2) + sqrt(5)*5.0/6.0, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 0.75, position.get_component(1) + 1 + sqrt( 3 )*11.0/12.0, position.get_component(2) + sqrt(5)*5.0/6.0, 0, 0, 1 ) );
    nb_atoms = 12;
}


void Cell::create_2D_triangular() {
    cell.push_back( create_atom( position.get_component(0) + 0.75, position.get_component(1) + 0.25*sqrt(3), position.get_component(2) + 0.5, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 1.75, position.get_component(1) + 0.25*sqrt(3), position.get_component(2) + 0.5, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 0.25, position.get_component(1) + 1 + 0.25*sqrt(3), position.get_component(2) + 0.5, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 1.25, position.get_component(1) + 1 + 0.25*sqrt(3), position.get_component(2) + 0.5, 0, 0, 1 ) );
    nb_atoms = 4;
}

void Cell::create_2D_centered_square() {
    cell.push_back( create_atom( position.get_component(0) + 0.25, position.get_component(1) + 0.25, position.get_component(2) + 0.5, 0, 0, 1 ) );
    cell.push_back( create_atom( position.get_component(0) + 0.75, position.get_component(1) + 0.75, position.get_component(2) + 0.5, 0, 0, 1 ) );
    nb_atoms = 2;
}


Atom Cell::create_atom( double x, double y, double z, double sx, double sy, double sz ) {
    Array_double position(3);
    position.set_component(0, x);
    position.set_component(1, y);
    position.set_component(2, z);

    Array_double spin(3);
    spin.set_component(0, sx);
    spin.set_component(1, sy);
    spin.set_component(2, sz);

    Atom atom( position, spin );
    return atom;
}





