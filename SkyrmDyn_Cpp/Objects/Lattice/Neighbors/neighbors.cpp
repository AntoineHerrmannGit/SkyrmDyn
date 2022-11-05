#include "Objects/Lattice/lattice.h"

#include "Error_messages/error_messages.h"

#include "Objects/Lattice/Boundary_conditions/boundary_conditions.h"

#include <vector>
#include <string>

void Lattice::setup_neighbors() {
    // Setup the nearest neighbors of each atom
    attribute_nearest_neighbors();

    // Setup the neighbors list for each atom
    for( Cell& cells : lattice ) {
        std::vector < Atom >& current_cell = cells.get_cell();
        for( Atom& atoms : current_cell ) {
            // Zeroth rank neighbor is the atom itself
            std::vector< Atom* > tmp_list;
            tmp_list.push_back( &atoms );
            atoms.get_neighbors_list().push_back( tmp_list );
            // First rank of neighbors are the nearest neighbors
            tmp_list = atoms.get_nearest_neighbors();
            atoms.get_neighbors_list().push_back( tmp_list );

            // Find the neighbors from order of links that
            // relates the atom to the atom of reference

            // For all ranks, until all atoms are considered
            int counter = 1 + atoms.get_nearest_neighbors().size();
            int neighbor_rank = 1;
            while( counter < nb_atoms ) {
                // Consider the last crown of neighbors
                std::vector< Atom* > new_tmp_list;
                for( Atom* atom : atoms.get_neighbors( neighbor_rank ) ) {
                    // Gather all possible candidates
                    for( Atom* neighboring_atom : atom->get_nearest_neighbors() ) {
                        new_tmp_list.push_back( neighboring_atom );
                    }
                }

                // Get rid of double-counts
                std::vector< Atom* > tmp;
                for( int i=0; i<(int)new_tmp_list.size(); i++ ) {
                    bool uniqueness = true;
                    for( int j=i+1; j<(int)new_tmp_list.size(); j++ ) {
                        if( new_tmp_list[i] == new_tmp_list[j] ) {
                            uniqueness = false;
                            break;
                        }
                    }
                    if( uniqueness ) {
                        tmp.push_back( new_tmp_list[i] );
                    }
                }
                new_tmp_list = tmp;
                tmp.clear();

                // Get all already referenced atoms
                // in the deeper crowns of neighbors
                std::vector< Atom* > referenced_neighbors;
                int min_rank = std::max( 0, neighbor_rank - 1 );
                for( int i=min_rank; i<=neighbor_rank; i++ ) {
                    for( Atom* referenced_atom : atoms.get_neighbors( i ) ) {
                        referenced_neighbors.push_back( referenced_atom );
                    }
                }

                // Get rid of double-counts
                for( int i=0; i<(int)referenced_neighbors.size(); i++ ) {
                    bool uniqueness = true;
                    for( int j=i+1; j<(int)referenced_neighbors.size(); j++ ) {
                        if( referenced_neighbors[i] == referenced_neighbors[j] ) {
                            uniqueness = false;
                            break;
                        }
                    }
                    if( uniqueness ) {
                        tmp.push_back( referenced_neighbors[i] );
                    }
                }
                referenced_neighbors = tmp;
                tmp.clear();

                // Compare the two lists and put all atoms
                // NOT in common in a new list
                std::vector< Atom* > new_neighbors;
                for( Atom* atom : new_tmp_list ) {
                    bool uniqueness = true;
                    for( Atom* candidate : referenced_neighbors ) {
                        if( atom == candidate ) {
                            uniqueness = false;
                            break;
                        }
                    }
                    if( uniqueness ) {
                        new_neighbors.push_back( atom );
                    }
                }

                // Get rid of double-counts
                for( int i=0; i<(int)new_neighbors.size(); i++ ) {
                    bool uniqueness = true;
                    for( int j=i+1; j<(int)new_neighbors.size(); j++ ) {
                        if( new_neighbors[i] == new_neighbors[j] ) {
                            uniqueness = false;
                            break;
                        }
                    }
                    if( uniqueness ) {
                        tmp.push_back( new_neighbors[i] );
                    }
                }
                new_neighbors = tmp;
                tmp.clear();

                // Reference the new atoms
                neighbor_rank ++;
                atoms.set_neighbor( new_neighbors );
                counter += (int) new_neighbors.size();
            }
        }
    }
}

void Lattice::setup_nearest_neighbors( Atom& atom ) {
    Cell& cell = *atom.get_mother_cell();
    std::vector< Cell* > neighboring_cells = find_neighboring_cells( cell );
    std::vector< Atom* > neighbors_list;
    for( Cell* cells : neighboring_cells ) {
        std::vector < Atom >& current_cell = cells->get_cell();
        for( Atom& atoms : current_cell ) {
            if( parameters.get_bounday_conditions() == "none" ) {
                if( atom.distance( atoms ) <= parameters.get_lattice_step_sigma() * parameters.get_lattice_step() ) {
                    neighbors_list.push_back( &atoms );
                }
            }
            else if( parameters.get_bounday_conditions() == "tor" ) {

            }
            else if( parameters.get_bounday_conditions() == "sphere" ) {

            }
            else if( parameters.get_bounday_conditions() == "linear" ) {

            }
            else {
                throw( AssignationError( "boundary condition" ) );
            }
        }
    }
    atom.set_nearest_neighbors( neighbors_list );
}

void Lattice::attribute_nearest_neighbors() {
    std::vector< Atom* > neighbors_list;
    for( Cell& cells : lattice ) {
        for( Atom& atoms : cells.get_cell() ) {
            setup_nearest_neighbors( atoms );
        }
    }
}





