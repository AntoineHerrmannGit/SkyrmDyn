#include "illg.h"
#include "Objects/Lattice/lattice.h"

#include "Constants/constants.h"

#include "Hamiltonian/Fields/Effective_fields/effective_magnetic_field.h"
#include "Hamiltonian/Fields/Temperature/temperature_field.h"

#include "Hamiltonian/Interactions/anisotropy.h"

#include "Maths/Objects/Matrix/Real_matrix/real_matrix.h"
#include "Maths/Functions/distribution_functions.h"

#include "Maths/Operators/vector_operators.h"
#include "Maths/Objects/Tensor/Vector_tensor/vector_tensors.h"

#include "Objects/Parameter/parameter.h"
#include "Objects/Atom/atom.h"

Atom make_euler_illg_step( Atom& atom, Array_double& local_magnetic_field, Parameter& para ) {
    Array_double spin = atom.get_spin();
    Array_double memory_spin = atom.get_spin_copy();

    Array_double second_term = build_illg_second_term( atom, local_magnetic_field, para );

    Real_matrix coupling_matrix = build_illg_coupling_matrix( atom, para );
    coupling_matrix.inverse();

    Array_double evolution = coupling_matrix.multiply_right_by_array_double( second_term );

    spin.set_array( evolution );
    spin.normalize();

    atom.set_spin( spin );
    atom.set_memory_spin( memory_spin );
    return atom;
}

Real_matrix build_illg_coupling_matrix( Atom& atom,  Parameter& para ) {
    double damping = para.get_damping();
    double tau = para.get_tau();
    double llg_time_step = para.get_llg_time_step();
    Array_double spin = atom.get_spin();
    Real_matrix coupling_matrix(3);
    for( int i=0; i<3; i++ ) {
        for( int j=0; j<3; j++ ) {
            int k = Levi_Civita_get_k( i, j );
            double element = delta( i, j ) + damping * ( 1 + tau / llg_time_step ) * Levi_Civita( i, j, k ) * spin.get_component(k);
            // positive sign comes from the negative sign in front of the spin coordinates in the coupling matrix
            coupling_matrix.set_component( i, j, element );
        }
    }
    return coupling_matrix;
}

Array_double build_illg_second_term( Atom& atom, Array_double& magnetic_field, Parameter& para ) {
    double gamma = e/(2*m_e);
    double damping = para.get_damping();
    double tau = para.get_tau();
    double llg_time_step = para.get_llg_time_step();

    Array_double spin = atom.get_spin();
    Array_double memory_spin = atom.get_memory_spin();

    Array_double first_term = cross( spin, magnetic_field );
    first_term.multiply_by_scalar( -llg_time_step * gamma );
    first_term.add( spin );

    Array_double second_term = cross( spin, memory_spin );
    first_term.multiply_by_scalar( damping * tau / llg_time_step );

    second_term.add( first_term );

    return second_term;
}

void Lattice::euler_illg_step() {
    std::vector< Cell > new_lattice( lattice );

    int i=0;
    for( Cell cells : lattice ) {
        int j=0;
        for( Atom& atom : cells.get_cell() ) {
            Array_double local_magnetic_field;
            if( (int) atom.get_nearest_neighbors().size() != 0 ) {
                for( Atom*atoms : atom.get_nearest_neighbors() ) {
                    Array_double tmp_field = build_effective_2_body_magnetic_field( atom, atoms, parameters );
                    local_magnetic_field.add( tmp_field );
                }
            }
            else {
                local_magnetic_field = parameters.get_magnetic_field();
                local_magnetic_field.add( anisotropy_field( atom, parameters ) );
                local_magnetic_field.add( temperature_field( parameters.get_temperature_T(), parameters.get_diffusion_D() ) );
            }
            Atom new_atom = make_euler_illg_step( atom, local_magnetic_field, parameters );
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
