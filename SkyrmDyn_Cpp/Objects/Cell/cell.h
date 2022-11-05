#ifndef CELL_H
#define CELL_H

#include "Objects/Atom/atom.h"

#include "Maths/Objects/Array/Array_double/array_double.h"
#include "Maths/Objects/Array/Array_int/array_int.h"

#include <vector>
#include <string>

class Cell
{
public:
    // Constructor
    //-----------------------------------
    Cell( std::string &lat_name, Array_int &new_position );
    Cell();

    // Getters
    //-----------------------------------
    std::vector< Atom >& get_cell();
    std::vector< Atom > get_cell_copy();

    std::string& get_name();

    Array_double& get_position();
    Array_double get_position_copy();

    Array_int& get_label();

    Atom& get_atom( int n );
    Atom get_atom_copy( int n );

    std::vector< Cell* > get_neighboring_cells();

    int get_nb_atoms();

    // Setters
    //-----------------------------------
    void set_atom( Atom& atom, int i );
    void set_neighboring_cells( std::vector< Cell* > new_neighboring_cells );

    // Public libraries
    //-----------------------------------
    bool check_atom_in_cell( Atom& atom );

    bool operator==( Cell& cell );
    bool operator!=( Cell& cell );

private:
    std::vector< Atom > cell = {};
    Array_double position;
    Array_int label;
    std::string name = "";
    int nb_atoms = 0;

    std::vector< Cell* > neighboring_cells;

    void setup_cell( std::string &lat_name );

    void setup_position( std::string &lat_name, Array_int &new_position );

    void create_3D_simple_cubic();
    void create_3D_BCC();
    void create_3D_FCC();
    void create_3D_dimond();

    void create_3D_triangular();
    void create_3D_straight_honeycomb();
    void create_3D_staggered_honeycomb();

    void create_2D_centered_square();
    void create_2D_triangular();

    Atom create_atom( double x, double y, double z, double sx, double sy, double sz );
    void fill_cell( std::vector< Array_double > positions, std::vector< Array_double > spins );
};

#endif // CELL_H
