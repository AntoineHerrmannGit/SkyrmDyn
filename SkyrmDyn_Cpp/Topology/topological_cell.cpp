#include "topological_cell.h"

#include "Maths/Objects/Array/Array_double/array_double.h"
#include "Objects/Atom/atom.h"

#include <vector>

// Constructor
//-----------------------------------
topological_cell::topological_cell()
{

}

topological_cell::topological_cell( Array_double new_position, std::vector< Atom* > new_cell ) {
    cell = new_cell;
    position = new_position;
}

// Getters
//-----------------------------------
std::vector< Atom* > topological_cell::get_cell() {
    return cell;
}
Array_double topological_cell::get_Berry_curvature() {
    return Berry_curvature;
}
double topological_cell::get_charge() {
    return charge;
}
Array_double topological_cell::get_position() {
    return position;
}

// Setters
//-----------------------------------
void topological_cell::set_cell( std::vector< Atom* > new_cell ) {
    cell = new_cell;
}
void topological_cell::set_Berry_curvature( Array_double new_Berry_curvature ) {
    Berry_curvature = new_Berry_curvature;
}
void topological_cell::set_charge( double new_charge ) {
    charge = new_charge;
}
void topological_cell::set_position( Array_double new_position ) {
    position = new_position;
}
