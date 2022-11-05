#include "Objects/Lattice/lattice.h"

#include "Objects/Atom/atom.h"
#include "Objects/Cell/cell.h"
#include "Objects/Parameter/parameter.h"

#include "Constants/constants.h"

#include "Error_messages/error_messages.h"

#include <math.h>

void Lattice::setup_skyrmion_charge_1() {

    /*
     Based on reference :
        * Siemens et al., 2016 New J. Phys., 18, 045021
        * A. Kubetzka, O. Pietzsch, M. Bode, and R. Wiesendanger, Phys. Rev. B 67, 020401(R)
    */

    double w = sqrt( parameters.get_exchange_J() / ( parameters.get_anisotroy_K() + 0.5 * parameters.get_magnetic_field_H() ) );
    double c = 0.5 * w * asin( sqrt( 2 * parameters.get_anisotroy_K() / parameters.get_magnetic_field_H() ) );
    double nu = 0;
    if( parameters.get_initial_spin_skyrmion_type() == "Neel" ) {
        nu = 0;
    }
    else if( parameters.get_initial_spin_skyrmion_type() == "Bloch" ) {
        nu = 0.5 * pi;
    }
    else {
        throw( AssignationError( " skyrmion type : nu " ) );
    }

    for( Cell& cells : lattice ) {
        for( Atom& atom : cells.get_cell() ) {
            Array_double relative = parameters.get_initial_spin_skyrmion_position();
            relative.substract( atom.get_position() );
            double r = relative.norm();

            double theta = asin( tanh( ( r + c ) / w ) ) + asin( tanh( ( r - c ) / w ) ) + pi;
            double phi = acos( relative.get_component(0) ) + nu;

            Array_double position = atom.get_position();
            Array_double direction;
            direction.set_component( 0, sin( theta ) * cos( phi ) );
            direction.set_component( 1, sin( theta ) * sin(phi ) );
            direction.set_component( 2, cos( theta ) );
            direction.normalize();
            atom.set_spin( direction );
        }
    }
}

void Lattice::setup_skyrmion_large_charge() {

}

