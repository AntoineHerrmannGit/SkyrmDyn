#include "Objects/Lattice/lattice.h"

#include "Error_messages/error_messages.h"

#include "Objects/Atom/atom.h"
#include "Objects/Cell/cell.h"
#include "Objects/Parameter/parameter.h"

#include "Maths/Objects/Array/Array_double/array_double.h"

#include <cmath>

Atom Lattice::apply_tor_boundary_conditions( Atom& atom1, Atom& atom2 ) {
    // Creates a virtual image of the atom2 with respect to the atom1
    // with toric boundary conditions

    Array_double lattice_length = get_lattice_length();
    Atom virtual_image = atom2;
    Array_double virtual_position = virtual_image.get_position();

    Array_double relative_position = atom1.relative_position( virtual_image );

    for( int i=0; i<3; i++ ) {
        if( relative_position.get_component( i ) > 0.5 * lattice_length.get_component( i ) ) {
            double new_position = virtual_image.get_position().get_component( i ) - lattice_length.get_component( i );
            virtual_position.set_component( i, new_position );
        }
        else if( relative_position.get_component( i ) < -0.5 * lattice_length.get_component( i ) ) {
            double new_position = virtual_image.get_position().get_component( i ) + lattice_length.get_component( i );
            virtual_position.set_component( i, new_position );
        }
    }

    virtual_image.set_position( virtual_position );
    return virtual_image;
}
Atom Lattice::apply_sphere_boundary_conditions( Atom& atom1, Atom& atom2 ) {
    Array_double lattice_length = get_lattice_length();
    Atom virtual_image = atom2;

    return virtual_image;
}
Atom Lattice::apply_linear_boundary_conditions( Atom& atom1, Atom& atom2 ) {
    // Creates a virtual image of the atom2 with respect to the atom1
    // with x-linear boundary conditions

    Array_double lattice_length = get_lattice_length();
    Atom virtual_image = atom2;
    Array_double virtual_position = virtual_image.get_position();

    Array_double relative_position = atom1.relative_position( virtual_image );

    if( relative_position.get_component( 0 ) > 0.5 * lattice_length.get_component( 0 ) ) {
        double new_position = virtual_image.get_position().get_component( 0 ) - lattice_length.get_component( 0 );
        virtual_position.set_component( 0, new_position );
    }
    else if( relative_position.get_component( 0 ) < -0.5 * lattice_length.get_component( 0 ) ) {
        double new_position = virtual_image.get_position().get_component( 0 ) + lattice_length.get_component( 0 );
        virtual_position.set_component( 0, new_position );
    }

    return virtual_image;
}

bool test_neighboring_cells( Cell& cell1, Cell& cell2, Parameter parameters ) {
    Array_int label1 = cell1.get_label();
    Array_int label2 = cell2.get_label();
    Array_int relative_position = label1;
    relative_position - label2;
    if( parameters.get_bounday_conditions() == "none" ) {
        if( ( std::abs( relative_position.get_x() ) <= 1 ) &&
            ( std::abs( relative_position.get_y() ) <= 1 ) &&
            ( std::abs( relative_position.get_z() ) <= 1 ) &&
            ( cell1 != cell2 ) ) {
            return true;
        }
        return false;
    }
    else if( parameters.get_bounday_conditions() == "tor" ) {
        bool x_neighboring_cell = false;
        bool y_neighboring_cell = false;
        bool z_neighboring_cell = false;
        Array_int lattice_size = parameters.get_lattice_size();
        if( ( std::abs( relative_position.get_x() ) <= 1 ) ||
            ( std::abs( relative_position.get_x() ) % lattice_size.get_x() >= (int) std::round( lattice_size.get_x() - 1 ) ) ) {
            x_neighboring_cell = true;
        }
        if( ( std::abs( relative_position.get_y() ) <= 1 ) ||
            ( std::abs( relative_position.get_y() ) % lattice_size.get_y() >= (int) std::round( lattice_size.get_y() - 1 ) ) ) {
            y_neighboring_cell = true;
        }
        if( ( std::abs( relative_position.get_z() ) <= 1 ) ||
            ( std::abs( relative_position.get_z() ) % lattice_size.get_z() >= (int) std::round( lattice_size.get_z() - 1 ) ) ) {
            z_neighboring_cell = true;
        }
        if( x_neighboring_cell && y_neighboring_cell && z_neighboring_cell ) {
            if( cell1 != cell2 ) {
                return true;
            }
        }
        return false;
    }
    else if( parameters.get_bounday_conditions() == std::string( "sphere" ) ) {
        bool x_neighboring_cell = false;
        bool y_neighboring_cell = false;
        bool z_neighboring_cell = false;
        Array_int lattice_size = parameters.get_lattice_size();
        if( ( std::abs( relative_position.get_x() ) <= 1 ) ||
            ( std::abs( relative_position.get_x() ) % (int) std::round( 0.5*lattice_size.get_x() ) >= (int) std::round( 0.5*lattice_size.get_x() - 1 ) ) ) {
            x_neighboring_cell = true;
        }
        if( ( std::abs( relative_position.get_y() ) <= 1 ) ||
            ( std::abs( relative_position.get_y() ) % (int) std::round( 0.5*lattice_size.get_y() ) >= (int) std::round( 0.5*lattice_size.get_y() - 1 ) ) ) {
            y_neighboring_cell = true;
        }
        if( ( std::abs( relative_position.get_z() ) <= 1 ) ||
            ( std::abs( relative_position.get_z() ) % (int) std::round( 0.5*lattice_size.get_z() ) >= (int) std::round( 0.5*lattice_size.get_z() - 1 ) ) ) {
            z_neighboring_cell = true;
        }
        if( x_neighboring_cell && y_neighboring_cell && z_neighboring_cell ) {
            if( cell1 != cell2 ) {
                return true;
            }
        }
        return false;
    }
    else if( parameters.get_bounday_conditions() == std::string( "linear" ) ) {
        bool x_neighboring_cell = false;
        bool y_neighboring_cell = false;
        bool z_neighboring_cell = false;
        Array_int lattice_size = parameters.get_lattice_size();
        if( ( std::abs( relative_position.get_x() ) <= 1 ) ||
            ( std::abs( relative_position.get_x() ) % lattice_size.get_x() >= (int) std::round( lattice_size.get_x() - 1 ) ) ) {
            x_neighboring_cell = true;
        }
        if( std::abs( relative_position.get_y() ) <= 1 ) {
            y_neighboring_cell = true;
        }
        if( std::abs( relative_position.get_z() ) <= 1 ) {
            z_neighboring_cell = true;
        }
        if( x_neighboring_cell && y_neighboring_cell && z_neighboring_cell ) {
            if( cell1 != cell2 ) {
                return true;
            }
        }
        return false;
    }
    else {
        throw( AssignationError( "bounday_conditions" ) );
    }
}
