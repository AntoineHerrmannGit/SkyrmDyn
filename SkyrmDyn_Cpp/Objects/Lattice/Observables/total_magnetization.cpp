#include "Objects/Lattice/lattice.h"

#include "Constants/constants.h"

#include "Maths/Objects/Array/Array_double/array_double.h"

Array_double Lattice::total_magnetization() {
    Array_double tot_mag;
    int nb_atoms = 0;
    for( Cell& cell : lattice ) {
        for( Atom& atom : cell.get_cell() ) {
            tot_mag.add( atom.get_spin() );
            nb_atoms++;
        }
    }
    tot_mag.multiply_by_scalar( g*mu_B/nb_atoms );
    return tot_mag;
}
