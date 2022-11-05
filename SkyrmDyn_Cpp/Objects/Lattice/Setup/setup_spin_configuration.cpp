#include "Objects/Lattice/lattice.h"

#include "Objects/Atom/atom.h"
#include "Objects/Cell/cell.h"
#include "Objects/Parameter/parameter.h"

#include "Constants/constants.h"

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Maths/Random/random.h"
#include "Maths/Operators/vector_operators.h"

#include "Error_messages/error_messages.h"

#include <math.h>

void Lattice::setup_initial_spin_config() {
    std::string initial_spin_config = parameters.get_initial_spin_config();
    if( initial_spin_config == "ferromagnetic" ) {
        setup_ferromagnetic();
    }
    else if( initial_spin_config == "ferrimagnetic" ) {
        setup_ferrimagnetic();
    }
    else if( initial_spin_config == "antiferromagnetic" ) {
        setup_antiferromagnetic();
    }
    else if( initial_spin_config == "spin_spiral" ) {
        setup_spin_spiral();
    }
    else if( initial_spin_config == "skyrmion" ) {
        setup_spin_skyrmion();
    }
    else if( initial_spin_config == "random" ) {
        setup_random();
    }
    else {
        throw( AssignationError( "initial_spin_config" ) );
    }
}



void Lattice::setup_ferromagnetic() {
    for( Cell& cells : lattice ) {
        for( Atom& atom : cells.get_cell() ) {
            Array_double spin_axis = parameters.get_initial_spin_axis();
            spin_axis.normalize();
            atom.set_spin( spin_axis );
        }
    }
}

void Lattice::setup_ferrimagnetic() {
    double ratio = parameters.get_initial_spin_ratio();
    int i=1;
    for( Cell& cells : lattice ) {
        for( Atom& atom : cells.get_cell() ) {
            Array_double spin_axis = parameters.get_initial_spin_axis();
            spin_axis.normalize();
            spin_axis *= i*ratio;
            atom.set_spin( spin_axis );
            i = -i;
        }
    }
}

void Lattice::setup_antiferromagnetic() {
    Array_double spin_axis = parameters.get_initial_spin_axis();
    spin_axis.normalize();
    for( Cell& cells : lattice ) {
        for( Atom& atom : cells.get_cell() ) {
            spin_axis.multiply_by_scalar( -1 );
            atom.set_spin( spin_axis );
        }
    }
}

void Lattice::setup_spin_spiral() {
    Array_double q = parameters.get_initial_spin_spiral_vector();
    double theta = parameters.get_initial_spin_spiral_phase_theta();
    double phi = parameters.get_initial_spin_spiral_phase_phi();

    for( Cell& cells : lattice ) {
        for( Atom& atom : cells.get_cell() ) {
            Array_double position = atom.get_position();
            Array_double direction;
            direction.set_component( 0, sin( dot( q, position ) + theta ) * cos( dot( q, position ) + phi ) );
            direction.set_component( 1, sin( dot( q, position ) + theta ) * sin( dot( q, position ) + phi ) );
            direction.set_component( 2, cos( dot( q, position ) + theta ) );
            direction.normalize();
            atom.set_spin( direction );
        }
    }
}

void Lattice::setup_spin_skyrmion() {
    if( parameters.get_initial_spin_skyrmion_charge() == 1 ) {
        setup_skyrmion_charge_1();
    }
    else if( parameters.get_initial_spin_skyrmion_charge() >=2 ) {

    }
    else {
        throw( AssignationError( "initial_spin_skyrmion_charge" ) );
    }
}

void Lattice::setup_random() {
    for( Cell& cells : lattice ) {
        for( Atom& atom : cells.get_cell() ) {
            Array_double direction = random_vector();
            atom.set_spin( direction );
        }
    }
}





