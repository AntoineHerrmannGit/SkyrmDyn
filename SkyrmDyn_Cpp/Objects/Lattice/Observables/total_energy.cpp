#include "Objects/Lattice/lattice.h"

#include "Hamiltonian/Interactions/anisotropy.h"
#include "Hamiltonian/Interactions/biquadratic.h"
#include "Hamiltonian/Interactions/dipole.h"
#include "Hamiltonian/Interactions/dmi.h"
#include "Hamiltonian/Interactions/four_spins.h"
#include "Hamiltonian/Interactions/heisenberg.h"
#include "Hamiltonian/Interactions/zeeman.h"

double Lattice::compute_total_energy() {
    double tot_e = total_anisotropy_energy() +
                   total_biquadratic_energy() +
                   total_dipole_energy() +
                   total_dmi_energy() +
                   total_four_spins_energy() +
                   total_heisenberg_energy() +
                   total_zeeman_energy();
    return tot_e;
}

double Lattice::total_energy() {
    double tot_e = 0;
    // run through all atoms
    for( Cell& cell_i : lattice ) {
        for( Atom& atom_i : cell_i.get_cell() ) {
            // run through all pairs of atoms
            for( Cell& cell_j : lattice ) {
                for( Atom& atom_j : cell_j.get_cell() ) {
                    // Avoid self interactions
                    if( atom_i != atom_j ) {
                        tot_e += biquadratic_energy( atom_i, atom_j, parameters );
                        tot_e += dipole_energy( atom_i, atom_j, parameters );
                        tot_e += heisenberg_energy( atom_i, atom_j, parameters );
                        tot_e += dmi_energy( atom_i, atom_j, parameters );
                    }
                }
            }
            tot_e += zeeman_energy( atom_i, parameters );
            tot_e += anisotropy_energy( atom_i, parameters );
        }
    }
    return tot_e;
}

