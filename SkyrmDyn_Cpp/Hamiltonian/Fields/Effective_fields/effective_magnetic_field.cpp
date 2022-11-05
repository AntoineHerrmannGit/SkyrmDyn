#include "effective_magnetic_field.h"

#include "Maths/Objects/Array/Array_double/array_double.h"
#include "Maths/Operators/vector_operators.h"

#include "Objects/Atom/atom.h"

#include "Hamiltonian/Interactions/anisotropy.h"
#include "Hamiltonian/Interactions/biquadratic.h"
#include "Hamiltonian/Interactions/dipole.h"
#include "Hamiltonian/Interactions/dmi.h"
#include "Hamiltonian/Interactions/four_spins.h"
#include "Hamiltonian/Interactions/heisenberg.h"

#include "Hamiltonian/Fields/Temperature/temperature_field.h"

#include <math.h>

Array_double build_effective_magnetic_field() {
    throw( "error" );
}

Array_double build_effective_2_body_magnetic_field( Atom& atom1, Atom* atom2, Parameter& para ) {
    Atom new_atom2 = *atom2;
    Array_double anisotropy = anisotropy_field( atom1, para );
    Array_double biquadratic = biquadratic_field( atom1, new_atom2, para );
    Array_double DMI = dmi_field( atom1, new_atom2, para );
    Array_double dipole = dipole_field( atom1, new_atom2, para );
    Array_double heisenberg = heisenberg_eff_mag_field( atom1, new_atom2, para );

    double T = para.get_temperature_T();
    double D = para.get_diffusion_D();
    Array_double temperature = temperature_field( T, D );

    Array_double effective_field = para.get_magnetic_field();

    effective_field.add( anisotropy );
    effective_field.add( biquadratic );
    effective_field.add( DMI );
    effective_field.add( dipole );
    effective_field.add( heisenberg );
    effective_field.add( temperature );

    /*
    magnetic_field.add( four_spins );
    */

    return effective_field;
}

Array_double build_effective_4_body_magnetic_field( Atom& atom1, Atom& atom2, Atom& atom3, Atom& atom4, Parameter& para ) {
    Array_double effective_field = four_spin_field( atom1, atom2, atom3, atom4, para );

    return effective_field;
}


