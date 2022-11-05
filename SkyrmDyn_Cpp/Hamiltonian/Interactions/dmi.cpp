#include "dmi.h"

#include "Error_messages/error_messages.h"

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Maths/Operators/vector_operators.h"

#include "Objects/Parameter/parameter.h"

#include "Symmetries/Local_symmetries/local_symmetries.h"

double dmi_energy( Atom& atom1, Atom& atom2, Parameter para ) {
    double D = para.get_DMI();
    Array_double dmi = dm_vector( atom1, atom2, para ); // Calculate the DM vector from Lifschitz invariant
    dmi.multiply_by_scalar(-D);

    Array_double spin1 = atom1.get_spin_copy();
    Array_double spin2 = atom2.get_spin_copy();

    Array_double pseudo_spin = cross( spin1, spin2 );
    double energy = dot( dmi, pseudo_spin );

    return energy;
}

Array_double dmi_field( Atom& atom1, Atom& atom2, Parameter& para ) {
    double D = para.get_DMI();
    Array_double dmi = dm_vector( atom1, atom2, para ); // Calculate the DM vector from Lifschitz invariant
    dmi.multiply_by_scalar( -D );

    Array_double spin2 = atom2.get_spin_copy();

    Array_double field = cross( spin2, dmi );

    return field;
}

Array_double dm_vector( Atom& atom1, Atom& atom2, Parameter& para ) {

    /*
    Based on reference :
     * TORU MORIYA, "Anisotropic Superexchange Interaction and Weak Ferromagnetism",
       PHYSICAL REVIEW VOLUME 120, NUMBER 1, OCTOBER 1, 1960
     * Gen Yin, Yufan Li, Lingyao Kong, Roger K. Lake, Chia-Ling Chien, and Jiadong Zang,
       "Topological Charge Analysis of Ultrafast Single Skyrmion Creation",
       Phys. Rev. B 93, 174403
    */

    Array_double relative = atom1.relative_position( atom2 );
    Array_double vect;

    // Inversion -> DMI = 0
    bool inversion = check_inversion_symmetry( atom1, atom2 );
    if( inversion == false ) {
        // Mirror excluding atoms -> DMI _|_ or // mirror
        if( check_mirror_symmetry( atom1, atom2 ) ) {
            if( para.get_DMI_type() == "Bloch" ) {
                vect = relative;
            }
            else if( para.get_DMI_type() == "Neel" ) {
                std::vector< Array_double > symmetry_plans = get_planar_symmetry_plan( atom1, atom2 );
                if( (int) symmetry_plans.size() == 1 ) {
                    vect = symmetry_plans[0];
                }
                else {
                    return vect;
                }
            }
            else {
                throw( AssignationError( "DMI_type" ) );
            }
        }
        // Mirror including atoms -> DMI _|_ mirror
        else if( check_planar_symmetry( atom1, atom2 ) ) {
            std::vector< Array_double > plans = get_planar_symmetry_plan( atom1, atom2 );
            for( Array_double normal : plans ) {
                vect += normal;
            }
        }
        // Rotations -> DMI // rotation axis
        else {
            for( int i=2; i<=6; i++ ) {
                if( check_rotation_symmetry( atom1, atom2, atom1.relative_position( atom2 ), i ) ) {
                    vect = atom1.relative_position( atom2 );
                }
            }
        }
    }
    else {
        return vect;
    }

    if( vect.norm() != 0 ) {
        vect.normalize();
    }

    return vect;
}
