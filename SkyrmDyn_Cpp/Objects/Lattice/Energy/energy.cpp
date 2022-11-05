#include "Objects/Lattice/lattice.h"

#include "Objects/Atom/atom.h"
#include "Objects/Parameter/parameter.h"

#include "Hamiltonian/Interactions/anisotropy.h"
#include "Hamiltonian/Interactions/biquadratic.h"
#include "Hamiltonian/Interactions/dipole.h"
#include "Hamiltonian/Interactions/dmi.h"
#include "Hamiltonian/Interactions/four_spins.h"
#include "Hamiltonian/Interactions/heisenberg.h"
#include "Hamiltonian/Interactions/zeeman.h"

double Lattice::total_anisotropy_energy() {
    double tot_a_e = 0;
    for( Cell& cell : lattice ) {
        for( Atom& atom : cell.get_cell() ) {
            tot_a_e += anisotropy_energy( atom, parameters );
        }
    }
    return tot_a_e;
}
double Lattice::total_biquadratic_energy() {
    double tot_b_e = 0;
    int i = 0;
    // run through all atoms
    for( Cell& cell_i : lattice ) {
        for( Atom& atom_i : cell_i.get_cell() ) {
            // run through all atoms which have not been counted already
            int j = 0;
            for( Cell cell_j : lattice ) {
                for( Atom atom_j : cell_j.get_cell() ) {
                    if( j > i ) {
                        tot_b_e += biquadratic_energy( atom_i, atom_j, parameters );
                    }
                    j++;
                }
            }
            i++;
        }
    }
    return tot_b_e;
}
double Lattice::total_dipole_energy() {
    double tot_d_e = 0;
    int i = 0;
    // run through all atoms
    for( Cell& cell_i : lattice ) {
        for( Atom& atom_i : cell_i.get_cell() ) {
            // run through all atoms which have not been counted already
            int j = 0;
            for( Cell& cell_j : lattice ) {
                for( Atom& atom_j : cell_j.get_cell() ) {
                    if( j > i ) {
                        tot_d_e += dipole_energy( atom_i, atom_j, parameters );
                    }
                    j++;
                }
            }
            i++;
        }
    }
    return tot_d_e;
}
double Lattice::total_dmi_energy() {
    double tot_dmi_e = 0;
    int i = 0;
    // run through all atoms
    for( Cell& cell_i : lattice ) {
        for( Atom& atom_i : cell_i.get_cell() ) {
            // run through all atoms which have not been counted already
            int j = 0;
            for( Cell& cell_j : lattice ) {
                for( Atom& atom_j : cell_j.get_cell() ) {
                    if( j > i ) {
                        tot_dmi_e += dmi_energy( atom_i, atom_j, parameters );
                    }
                    j++;
                }
            }
            i++;
        }
    }
    return tot_dmi_e;
}
double Lattice::total_four_spins_energy() {
    double tot_fs_e = 0;
    return tot_fs_e;
}
double Lattice::total_heisenberg_energy() {
    double tot_h_e = 0;
    int i = 0;
    // run through all atoms
    for( Cell& cell_i : lattice ) {
        for( Atom& atom_i : cell_i.get_cell() ) {
            // run through all atoms which have not been counted already
            int j = 0;
            for( Cell& cell_j : lattice ) {
                for( Atom& atom_j : cell_j.get_cell() ) {
                    if( j > i ) {
                        tot_h_e += heisenberg_energy( atom_i, atom_j, parameters );
                    }
                    j++;
                }
            }
            i++;
        }
    }
    return tot_h_e;
}
double Lattice::total_zeeman_energy() {
    double tot_z_e = 0;
    for( Cell& cell : lattice ) {
        for( Atom& atom : cell.get_cell() ) {
            tot_z_e += anisotropy_energy( atom, parameters );
        }
    }
    return tot_z_e;
}
