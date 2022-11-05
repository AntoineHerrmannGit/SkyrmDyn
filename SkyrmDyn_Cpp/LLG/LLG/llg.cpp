#include "llg.h"
#include "Objects/Lattice/lattice.h"

#include "Constants/constants.h"

#include "Error_messages/error_messages.h"

#include "Hamiltonian/Fields/Effective_fields/effective_magnetic_field.h"
#include "Hamiltonian/Fields/Temperature/temperature_field.h"

#include "Hamiltonian/Interactions/anisotropy.h"

#include "Maths/Objects/Array/Array_double/array_double.h"
#include "Maths/Objects/Matrix/Real_matrix/real_matrix.h"
#include "Maths/Functions/distribution_functions.h"

#include "Maths/Operators/vector_operators.h"
#include "Maths/Objects/Tensor/Vector_tensor/vector_tensors.h"

#include "Objects/Atom/atom.h"
#include "Objects/Cell/cell.h"

void Lattice::euler_llg_step() {
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
                new_atom = make_euler_llg_step( atom, local_magnetic_field, parameters );
            }
            else if( parameters.get_solver() == "rk_4" ) {
                new_atom = make_rk4_llg_step( atom, local_magnetic_field, parameters );
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


Atom make_euler_llg_step( Atom& atom, Array_double &magnetic_field, Parameter& para ) {
    Array_double spin = atom.get_spin();

    Array_double second_term = build_llg_second_term( atom, magnetic_field, para );

    Real_matrix coupling_matrix = build_llg_coupling_matrix( atom, para );
    coupling_matrix.inverse();

    Array_double evolution = coupling_matrix.multiply_right_by_array_double( second_term );

    spin.set_array( evolution );
    spin.normalize();
    atom.set_spin( spin );
    return atom;
}

Real_matrix build_llg_coupling_matrix( Atom& atom, Parameter& para ) {
    double damping = para.get_damping();
    Array_double spin = atom.get_spin();
    Real_matrix coupling_matrix(3);
    for( int i=0; i<3; i++ ) {
        for( int j=0; j<3; j++ ) {
            int k = Levi_Civita_get_k( i, j );
            double element = delta( i, j ) + damping * Levi_Civita( i, j, k ) * spin.get_component(k);
            // positive sign comes from the negative sign in front of the spin coordinates in the coupling matrix
            coupling_matrix.set_component( i, j, element );
        }
    }
    return coupling_matrix;
}

Array_double build_llg_second_term( Atom& atom, Array_double& magnetic_field, Parameter& para ) {
    double gamma = e/(2*m_e);
    double llg_time_step = para.get_llg_time_step();

    Array_double spin = atom.get_spin();

    Array_double second_term = cross( spin, magnetic_field );
    second_term.multiply_by_scalar( -llg_time_step * gamma );
    second_term.add( spin );
    return second_term;
}


Atom make_euler_llg_step_backward( Atom& atom, Array_double &magnetic_field, Parameter& para ) {
    Array_double spin = atom.get_spin_copy();

    Array_double second_term = build_llg_backward_second_term( atom, magnetic_field, para );

    Real_matrix coupling_matrix = build_llg_backward_coupling_matrix( atom, para );
    coupling_matrix.inverse();

    Array_double evolution = coupling_matrix.multiply_right_by_array_double( second_term );

    spin.set_array( evolution );
    spin.normalize();
    atom.set_memory_spin( spin );
    return atom;
}

Real_matrix build_llg_backward_coupling_matrix( Atom& atom, Parameter& para ) {
    double damping = para.get_damping();
    Array_double spin = atom.get_spin();
    Real_matrix coupling_matrix(3);
    for( int i=0; i<3; i++ ) {
        for( int j=0; j<3; j++ ) {
            int k = Levi_Civita_get_k( i, j );
            double element = delta( i, j ) - damping * Levi_Civita( i, j, k ) * spin.get_component(k);
            coupling_matrix.set_component( i, j, element );
        }
    }
    return coupling_matrix;
}

Array_double build_llg_backward_second_term( Atom& atom, Array_double& magnetic_field, Parameter& para ) {
    double gamma = e/(2*m_e);
    double llg_time_step = para.get_llg_time_step();

    Array_double spin = atom.get_spin();

    Array_double second_term = cross( spin, magnetic_field );
    second_term.multiply_by_scalar( llg_time_step * gamma );
    second_term.add( spin );
    return second_term;
}

