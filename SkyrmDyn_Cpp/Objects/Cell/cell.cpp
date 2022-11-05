#include "cell.h"

#include "Error_messages/error_messages.h"

#include "Objects/Atom/atom.h"

#include "Maths/Objects/Array/Array_int/array_int.h"
#include "Maths/Objects/Array/Array_double/array_double.h"

#include <vector>
#include <math.h>


// Constructor
//-----------------------------------
Cell::Cell( std::string &lat_name, Array_int &new_position )
{
    label = new_position;
    name = lat_name;
    setup_position( lat_name, new_position );
    setup_cell( lat_name );
};
Cell::Cell() {

}

// Getters
//-----------------------------------
std::vector< Atom >& Cell::get_cell() {
    return cell;
}
std::vector< Atom > Cell::get_cell_copy() {
    return cell;
}

std::string& Cell::get_name() {
    return name;
}

Array_double& Cell::get_position() {
    return position;
}
Array_double Cell::get_position_copy() {
    return position;
}

Array_int& Cell::get_label() {
    return label;
}

Atom& Cell::get_atom( int n ) {
    return cell[n];
};
Atom Cell::get_atom_copy( int n ) {
    return cell[n];
};

std::vector< Cell* > Cell::get_neighboring_cells() {
    return neighboring_cells;
}

int Cell::get_nb_atoms() {
    return nb_atoms;
}

// Setters
//-----------------------------------
void Cell::set_atom( Atom& atom, int i ) {
    if( i< nb_atoms ) {
        cell[i] = atom;
    }
    else {
        throw( AssignationError( "atom" ) );
    }
}

void Cell::set_neighboring_cells( std::vector< Cell* > new_neighboring_cells ) {
    neighboring_cells = new_neighboring_cells;
}

// Public libraries
//-----------------------------------
bool Cell::check_atom_in_cell( Atom& atom ) {
    for( Atom& atoms : cell ) {
        if( atom == atoms ) {
            return true;
        }
    }
    return false;
}

bool Cell::operator==( Cell& cellular ) {
    if( ( cellular.get_position() == position ) &&
        ( cellular.get_label() == label ) &&
        ( cellular.get_name() == name ) &&
        ( cellular.get_nb_atoms() == nb_atoms ) ){
            return true;
        }
    else {
        return false;
    }
}
bool Cell::operator!=( Cell& cellular ) {
    if( ( cellular.get_position() != position ) ||
        ( cellular.get_label() != label ) ||
        ( cellular.get_name() != name ) ||
        ( cellular.get_nb_atoms() != nb_atoms ) ){
        return true;
    }
    else {
        int i=0;
        for( Atom atom : cellular.get_cell() ) {
            if( atom != cell[i] ) {
                return true;
            }
            else {
                i++;
            }
        }
        return false;
    }
}



// Private library
//-----------------------------------
