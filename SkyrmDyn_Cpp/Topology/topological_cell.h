#ifndef TOPOLOGICAL_CELL_H
#define TOPOLOGICAL_CELL_H

#include "Objects/Atom/atom.h"

#include "Maths/Objects/Array/Array_double/array_double.h"

#include <vector>


class topological_cell
{
public:
    // Constructor
    //-----------------------------------
    topological_cell();
    topological_cell( Array_double position, std::vector< Atom* > cell );

    // Getters
    //-----------------------------------
    std::vector< Atom* > get_cell();
    Array_double get_Berry_curvature();
    double get_charge();
    Array_double get_position();

    // Setters
    //-----------------------------------
    void set_cell( std::vector< Atom* > cell );
    void set_Berry_curvature( Array_double Berry_curvature );
    void set_charge( double charge );
    void set_position( Array_double position );

    // Public library
    //-----------------------------------
    void compute_Berry_curvature();
    void compute_charge( Array_double direction );

private:
    std::vector< Atom* > cell;
    Array_double Berry_curvature;
    double charge = 0;

    Array_double position;
};

#endif // TOPOLOGICAL_CELL_H
