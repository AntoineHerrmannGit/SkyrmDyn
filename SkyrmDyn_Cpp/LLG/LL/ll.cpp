#include "LLG/LL/ll.h"
#include "Objects/Lattice/lattice.h"

#include "Constants/constants.h"

#include "Error_messages/error_messages.h"

#include "Hamiltonian/Fields/Effective_fields/effective_magnetic_field.h"
#include "Hamiltonian/Fields/Temperature/temperature_field.h"

#include "Hamiltonian/Interactions/anisotropy.h"

#include "Maths/Operators/vector_operators.h"

#include "Objects/Atom/atom.h"
#include "Objects/Cell/cell.h"

void Lattice::euler_ll_step() {
    std::vector< Cell > new_lattice( lattice );
    int i=0;
    for( Cell cells : lattice ) {
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
                local_magnetic_field.add( anisotropy_field( atom, parameters ) );
                local_magnetic_field.add( temperature_field( parameters.get_temperature_T(), parameters.get_diffusion_D() ) );
            }

            Atom new_atom;
            if( parameters.get_solver() == "euler" ) {
                new_atom = make_euler_ll_step( atom, local_magnetic_field, parameters );
            }
            else if( parameters.get_solver() == "rk_4" ) {
                new_atom = make_rk4_ll_step( atom, local_magnetic_field, parameters );
            }
            else {
                throw( AssignationError( "solver" ) );
            }
            new_lattice[i].set_atom( new_atom, j );
            j++;
        }
        i++;
    }
    lattice = new_lattice;
    energy = total_energy();
    magnetization = total_magnetization();

    parameters.update_llg_step();

    write_atomic_spins();
    write_atoms();
    write_magnetization();
    write_energy();
}

Atom make_euler_ll_step( Atom& atom, Array_double &magnetic_field, Parameter& para ) {
    double gamma = e/(2*m_e);
    double damping = para.get_damping();
    double llg_time_step = para.get_llg_time_step();

    Array_double spin = atom.get_spin();

    Array_double first_term = cross( spin, magnetic_field );
    first_term.multiply_by_scalar( -llg_time_step*gamma );

    Array_double second_term = cross( spin, cross( spin, magnetic_field ) );
    second_term.multiply_by_scalar( -llg_time_step*damping );

    spin.add( first_term );
    spin.add( second_term );
    spin.normalize();
    atom.set_spin( spin );
    return atom;
}




