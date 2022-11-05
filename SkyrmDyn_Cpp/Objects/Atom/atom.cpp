#include "atom.h"

#include "Error_messages/error_messages.h"

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Maths/Operators/vector_operators.h"

#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>

// Constructor
//-----------------------------------
Atom::Atom( Array_double &new_position, Array_double &new_spin ) {
    position.set_array( new_position );
    spin.set_array( new_spin );
};
Atom::Atom() {

}

// Getters
//-----------------------------------
Array_double& Atom::get_position() {
    return position;
};
Array_double Atom::get_position_copy() {
    return position;
};

Array_double& Atom::get_spin() {
    return spin;
};
Array_double Atom::get_spin_copy() {
    return spin;
};

Array_double& Atom::get_memory_spin() {
    return spin;
};
Array_double Atom::get_memory_spin_copy() {
    return spin;
};

Cell* Atom::get_mother_cell() {
    return mother_cell;
}

std::vector< Atom* >& Atom::get_nearest_neighbors() {
    return nearest_neighbors;
}
std::vector<Atom *> Atom::get_nearest_neighbors_copy() {
    return nearest_neighbors;
}

std::vector< std::vector< Atom* > >& Atom::get_neighbors_list() {
    return neighbors;
}
std::vector< std::vector< Atom* > > Atom::get_neighbors_list_copy() {
    return neighbors;
}

std::vector< Atom* >& Atom::get_neighbors( int rank ) {
    return neighbors[ rank ];
}
std::vector< Atom* > Atom::get_neighbors_copy( int rank ) {
    return neighbors[ rank ];
}


// Setters
//-----------------------------------
void Atom::set_position( const Array_double& new_position ) {
    position = new_position;
};

void Atom::set_spin( const Array_double& new_spin ) {
    spin = new_spin;
};

void Atom::set_memory_spin( const Array_double& new_spin ) {
    memory_spin = new_spin;
};

void Atom::set_nearest_neighbors( std::vector< Atom* > list_of_nearest_neighbors ) {
    nearest_neighbors = list_of_nearest_neighbors;
};

void Atom::set_neighbors_list( std::vector< std::vector< Atom* > >& neighbors_list ) {
    neighbors = neighbors_list;
};

void Atom::set_neighbors_crown( std::vector< Atom* >& neighbors_list, int rank ) {
    neighbors[ rank ] = neighbors_list;
};

void Atom::set_neighbor( std::vector< Atom* > neighbors_list ) {
    neighbors.push_back( neighbors_list );
};

void Atom::set_mother_cell( Cell* cell ) {
    mother_cell = cell;
}

// Public libraries
//-----------------------------------
bool Atom::operator==( Atom& rhs ) {
    if( ( rhs.get_position() == position ) && ( rhs.get_spin() == spin ) ) {
        return true;
    }
    else {
        return false;
    }
}
bool Atom::operator!=( Atom& rhs ) {
    if( ( rhs.get_position() != position ) || ( rhs.get_spin() != spin ) ) {
        return true;
    }
    else {
        return false;
    }
}

void Atom::resize_neighbor_crown( int rank, int nb_elements ) {
    int nb_pop_back = (int) neighbors[rank].size() - nb_elements;
    if( nb_pop_back <= (int) neighbors[rank].size() ) {
        for( int i=0; i<nb_pop_back; i++ ) {
            neighbors.pop_back();
        }
        neighbors.shrink_to_fit();
    }
    else {
        throw( OperationImpossible( "reducing size of neighbors list of rank " + std::to_string(rank), "nb_elements", "pop_back empty list" ) );
    }
}


// Private Libraries
//-----------------------------------








