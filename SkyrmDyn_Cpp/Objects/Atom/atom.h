#ifndef ATOM_H
#define ATOM_H

#include "Maths/Objects/Array/Array_double/array_double.h"

#include <string>
#include <vector>

class Cell;

class Atom
{
public:
    // Constructor
    //-----------------------------------
    Atom( Array_double &new_position, Array_double &new_spin );
    Atom();

    // Getters
    //-----------------------------------
    Array_double& get_position();
    Array_double get_position_copy();

    Array_double& get_spin();
    Array_double get_spin_copy();

    Array_double& get_memory_spin();
    Array_double get_memory_spin_copy();

    Cell* get_mother_cell();

    std::vector< Atom* >& get_nearest_neighbors();
    std::vector< Atom* > get_nearest_neighbors_copy();

    std::vector< std::vector< Atom* > >& get_neighbors_list();
    std::vector< std::vector< Atom* > > get_neighbors_list_copy();

    std::vector< Atom* >& get_neighbors( int rank );
    std::vector< Atom* > get_neighbors_copy( int rank );

    // Setters
    //-----------------------------------
    void set_position( const Array_double& new_position );
    void set_spin( const Array_double& new_spin );
    void set_memory_spin( const Array_double& new_spin );

    void set_mother_cell( Cell* cell );

    void set_nearest_neighbors( std::vector< Atom* > list_of_nearest_neighbors );
    void set_neighbors_list( std::vector< std::vector< Atom* > >& neighbors_list );
    void set_neighbors_crown( std::vector< Atom* >& neighbors_list, int rank );

    void set_neighbor( std::vector< Atom* > neighbors_list );

    // Public libraries
    //-----------------------------------
    bool operator==( Atom& rhs );
    bool operator!=( Atom& rhs );

    double distance( Atom& other );

    Array_double relative_position( Atom& other );

    void write_spin( int step );

    void resize_neighbor_crown( int rank, int nb_elements );

private:
    Array_double position;
    Array_double spin;
    Array_double memory_spin;

    Cell* mother_cell;

    std::vector< Atom* > nearest_neighbors;
    std::vector< std::vector< Atom* > > neighbors;
};

#endif // ATOM_H
