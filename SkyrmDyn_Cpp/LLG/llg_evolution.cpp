#include "Objects/Lattice/lattice.h"

#include "Error_messages/error_messages.h"


void Lattice::euler_llg_evolution() {
    if( parameters.get_LLG_equation() == "illg" ) {
        euler_illg_step();
    }
    else if( parameters.get_LLG_equation() == "llg" ) {
        euler_llg_step();
    }
    else if( parameters.get_LLG_equation() == "ll" ) {
        euler_ll_step();
    }
    else {
        throw( AssignationError( "llg_equation" ) );
    }
}



