#include "Objects/Lattice/lattice.h"

#include "Objects/Parameter/parameter.h"

#include "Error_messages/error_messages.h"

#include "Maths/Objects/Array/Array_int/array_int.h"

#include <string.h>
#include <cmath>
#include <vector>

#include <algorithm>

void Lattice::setup_lattice_configuration() {
    Array_int lattice_size = parameters.get_lattice_size();
    std::string lattice_name = parameters.get_lattice_name();

    for( int i=0; i<lattice_size.get_component(0); i++ ) {
        for( int j=0; j<lattice_size.get_component(1); j++ ) {
            for( int k=0; k<lattice_size.get_component(2); k++ ) {
                Array_int position( 3 );
                position.set_component(0,i);
                position.set_component(1,j);
                position.set_component(2,k);

                Cell cell( lattice_name, position );
                lattice.push_back( cell );
                nb_atoms += cell.get_nb_atoms();
            }
        }
    }
};

Array_double Lattice::get_lattice_length() {
    Array_double lattice_length;
    std::vector< std::string > square_lattices = { "1D_chain", "2D_square", "2D_centered_square", "3D_simple_cubic", "3D_FCC", "3D_BCC", "3D_diamond" };
    std::vector< std::string > triangular_lattices = { "2D_triangular", "3D_triangular" };
    std::vector< std::string > honeycomb_lattices = { "2D_honeycomb", "3D_straight_honeycomb" };

    if( std::find( square_lattices.begin(), square_lattices.end(), parameters.get_lattice_name() ) != square_lattices.end() ) {
        lattice_length.set_component( 0, parameters.get_lattice_size().get_component( 0 ) - 1 );
        lattice_length.set_component( 1, parameters.get_lattice_size().get_component( 1 ) - 1 );
        lattice_length.set_component( 2, parameters.get_lattice_size().get_component( 2 ) - 1 );
        lattice_length *= parameters.get_lattice_step();
    }
    else if( std::find( triangular_lattices.begin(), triangular_lattices.end(), parameters.get_lattice_name() ) != triangular_lattices.end() ) {
        lattice_length.set_component( 0, 2 * ( parameters.get_lattice_size().get_component( 0 ) - 1 ) );
        lattice_length.set_component( 1, sqrt(3) * ( parameters.get_lattice_size().get_component( 1 ) - 1 ) );
        lattice_length.set_component( 2, sqrt(5) * ( parameters.get_lattice_size().get_component( 2 ) - 1 ) );
        lattice_length *= parameters.get_lattice_step();
    }
    else if( std::find( honeycomb_lattices.begin(), honeycomb_lattices.end(), parameters.get_lattice_name() ) != honeycomb_lattices.end() ) {
        lattice_length.set_component( 0, 3 * ( parameters.get_lattice_size().get_component( 0 ) - 1 ) );
        lattice_length.set_component( 1, sqrt(3) * ( parameters.get_lattice_size().get_component( 1 ) - 1 ) );
        lattice_length.set_component( 2, 2 * ( parameters.get_lattice_size().get_component( 2 ) - 1 ) );
        lattice_length *= parameters.get_lattice_step();
    }
    else if( parameters.get_lattice_name() == "3D_staggered_honeycomb" ) {
        lattice_length.set_component( 0, 3 * ( parameters.get_lattice_size().get_component( 0 ) - 1 ) );
        lattice_length.set_component( 1, sqrt(3) * ( parameters.get_lattice_size().get_component( 1 ) - 1 ) );
        lattice_length.set_component( 2, sqrt(3) * ( parameters.get_lattice_size().get_component( 2 ) - 1 ) );
        lattice_length *= parameters.get_lattice_step();
    }
    else {
        throw( AssignationError( "lattice_name" ) );
    }

    return lattice_length;
};
