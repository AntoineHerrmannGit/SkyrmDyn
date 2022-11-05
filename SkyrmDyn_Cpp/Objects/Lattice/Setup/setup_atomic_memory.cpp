#include "Objects/Lattice/lattice.h"

#include "Hamiltonian/Fields/Effective_fields/effective_magnetic_field.h"

#include "LLG/LLG/llg.h"

#include "Maths/Objects/Matrix/Real_matrix/real_matrix.h"

#include "Objects/Cell/cell.h"
#include "Objects/Atom/atom.h"

void Lattice::setup_atomic_memory() {
    if( parameters.get_LLG_equation() == "illg" ) {
        int i=0;
        for( Cell& cells : lattice ) {
            int j=0;
            for( Atom& atom : cells.get_cell() ) {
                Array_double local_magnetic_field;
                if( (int) atom.get_nearest_neighbors().size() != 0 ) {
                    for( Atom* atoms : atom.get_nearest_neighbors() ) {
                        Array_double tmp_field = build_effective_2_body_magnetic_field( atom, atoms, parameters );
                        local_magnetic_field.add( tmp_field );
                    }
                }
                else {
                    local_magnetic_field = parameters.get_magnetic_field();
                }
                Atom new_atom = make_euler_llg_step_backward( atom, local_magnetic_field, parameters );
                lattice[i].set_atom( new_atom, j );
                j++;
            }
            i++;
        }
    }
    else {
        for( Cell& cells : lattice ) {
            for( Atom& atom : cells.get_cell() ) {
                atom.set_memory_spin( atom.get_spin_copy() );
            }
        }
    }
}




