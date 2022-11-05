#include "lattice.h"

#include "Objects/Atom/atom.h"
#include "Objects/Cell/cell.h"
#include "Objects/Lattice/Boundary_conditions/boundary_conditions.h"
#include "Objects/Parameter/parameter.h"

#include "Maths/Objects/Array/Array_int/array_int.h"
#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Maths/Operators/vector_operators.h"

#include "Error_messages/error_messages.h"

#include <vector>
#include <string>
#include <math.h>
#include <fstream>

// Constructor
//-----------------------------------
Lattice::Lattice() {
    setup_lattice_configuration();
    setup_initial_spin_config();

    attribute_local_environment();
    setup_neighbors();

    setup_atomic_memory();

    write_atomic_positions();
    write_atomic_spins();
    write_atoms();

    //energy = total_energy();
    //magnetization = total_magnetization();

    write_magnetization();
    write_energy();
}



// Getters
//-----------------------------------
std::vector< Cell >& Lattice::get_lattice() {
    return lattice;
};
std::vector< Cell > Lattice::get_lattice_copy() {
    return lattice;
};

Cell& Lattice::get_cell( int &i, int &j, int &k ) {
    Array_int lattice_dimension = parameters.get_lattice_size();
    int p = lattice_dimension.get_x()*i + lattice_dimension.get_y()*j + lattice_dimension.get_z()*k;
    return lattice[p];
};
Cell Lattice::get_cell_copy( int &i, int &j, int &k ) {
    Array_int lattice_dimension = parameters.get_lattice_size();
    int p = lattice_dimension.get_x()*i + lattice_dimension.get_y()*j + lattice_dimension.get_z()*k;
    return lattice[p];
};

int Lattice::get_dimension() {
    std::string dim = parameters.get_lattice_name();
    dim = dim[0];
    int dimension = std::stoi( dim );
    return dimension;
}

Parameter& Lattice::get_parameter() {
    return parameters;
}
Parameter Lattice::get_parameter_copy() {
    return parameters;
}

double Lattice::get_energy() {
    return energy;
}

Array_double& Lattice::get_magnetization() {
    return magnetization;
}
Array_double Lattice::get_magnetization_copy() {
    return magnetization;
}

double Lattice::get_topological_charge() {
    return topological_charge;
}

double& Lattice::get_temperature() {
    return temperature;
}
double Lattice::get_temperature_copy() {
    return temperature;
}

// Public libraries
//-----------------------------------
Cell& Lattice::find_cell( Atom& atom ) {
    for( Cell& cell : lattice ) {
        // find is not accepting the overloaded operator==
        if( cell.check_atom_in_cell( atom ) ) {
            return cell;
        }
    }
    throw( UnfoudVariableError( "cell" ) );
}

std::vector< Cell* > Lattice::find_neighboring_cells( Cell& cell ) {
    std::vector< Cell* > neighboring_cells;
    for( Cell& cells : lattice ) {
        if( test_neighboring_cells( cell, cells, parameters ) ) {
            neighboring_cells.push_back( &cells );
        }
    }
    return neighboring_cells;
}

void Lattice::attribute_local_environment() {
    for( Cell& cell : lattice ) {
        for( Atom& atom : cell.get_cell() ) {
            atom.set_mother_cell( &cell );
        }
        std::vector< Cell* > tmp_surrounding_cells = find_neighboring_cells( cell );
        cell.set_neighboring_cells( tmp_surrounding_cells );
    }
}


// Private library
//-----------------------------------




