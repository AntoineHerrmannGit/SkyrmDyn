#include "local_symmetries.h"

#include "Maths/Objects/Array/Array_double/array_double.h"
#include "Maths/Operators/vector_operators.h"

#include "Objects/Atom/atom.h"

#include "Constants/constants.h"

#include <vector>

bool check_rotation_symmetry( Atom& atom1, Atom& atom2, Array_double axis, int n ) {
    Array_double rotation_axis = atom1.relative_position( atom2 );

    std::vector< Atom > neighbor_cloud = create_neighbors_cloud( atom1, atom2 );
    Array_double rel = atom1.relative_position( atom2 );

    // Make the rotation and create a new cloud
    double angle = 2*pi / n;
    std::vector< Atom > new_neighbor_cloud( neighbor_cloud );
    for( Atom atom : new_neighbor_cloud ) {
        Array_double pos = atom.get_position_copy();
        rotate( pos, axis, angle );
        atom.set_position( pos );
    }

    // Identify the pairs one by one
    for( Atom atom : neighbor_cloud ) {
        for( Atom atom_test : new_neighbor_cloud ) {
            Array_double pos = atom.get_position_copy();
            Array_double pos_test = atom_test.get_position_copy();
            if( pos.is_not_equal( pos_test ) ) {
                return false;
            }
        }
    }
    return true;
}

bool check_mirror_symmetry( Atom& atom1, Atom& atom2 ) {
    std::vector< Atom > neighbor_cloud = create_neighbors_cloud( atom1, atom2 );
    Array_double rel = atom1.relative_position( atom2 );

    // Apply mirror symmetry
    std::vector< Atom > new_neighbor_cloud( neighbor_cloud );
    for( Atom atom : new_neighbor_cloud ) {
        Array_double pos = atom.get_position_copy();
        double side = dot( pos, rel );
        if( side < 0 ) {
            rel.multiply_by_scalar( 2 );
            pos.add( rel );
            atom.set_position( pos );
        }
        else if( side > 0 ) {
            rel.multiply_by_scalar( 2 );
            pos.substract( rel );
            atom.set_position( pos );
        }
    }

    // Identify the pairs one by one
    for( Atom atom : neighbor_cloud ) {
        for( Atom atom_test : new_neighbor_cloud ) {
            Array_double pos = atom.get_position_copy();
            Array_double pos_test = atom_test.get_position_copy();
            if( pos.is_not_equal( pos_test ) ) {
                return false;
            }
        }
    }
    return true;
}

bool check_planar_symmetry( Atom& atom1, Atom& atom2 ) {
    std::vector< Array_double > symmetry_planes = get_planar_symmetry_plan( atom1, atom2 );
    if( (int) symmetry_planes.size() != 0 ) {
        return true;
    }
    else {
        return false;
    }
}

bool check_inversion_symmetry( Atom& atom1, Atom& atom2 ) {
    Array_double rotation_axis = atom1.relative_position( atom2 );

    std::vector< Atom > neighbor_cloud = create_neighbors_cloud( atom1, atom2 );
    Array_double rel = atom1.relative_position( atom2 );

    // Apply inversion symmetry
    std::vector< Atom > new_neighbor_cloud( neighbor_cloud );
    for( Atom atom : new_neighbor_cloud ) {
        Array_double pos = atom.get_position_copy();
        pos.multiply_by_scalar( -1 );
        atom.set_position( pos );
    }

    // Identify the pairs one by one
    for( Atom atom : neighbor_cloud ) {
        for( Atom atom_test : new_neighbor_cloud ) {
            Array_double pos = atom.get_position_copy();
            Array_double pos_test = atom_test.get_position_copy();
            if( pos.is_not_equal( pos_test ) ) {
                return false;
            }
        }
    }
    return true;
}

std::vector< Atom > create_neighbors_cloud( Atom& atom1, Atom& atom2 ) {
    std::vector< Atom* > cloud_1 = atom1.get_nearest_neighbors();
    std::vector< Atom* > cloud_2 = atom2.get_nearest_neighbors();

    std::vector< Atom > neighbor_cloud;

    // Isolate the cloud of neighboring atoms
    for( Atom* atom : cloud_1 ) {
        if( atom != &atom2 ) {
            Atom tmp = *atom;
            Atom copy = tmp;
            neighbor_cloud.push_back( copy );
        }
    }
    for( Atom* atom : cloud_2 ) {
        if( atom != &atom1 ) {
            Atom tmp = *atom;
            Atom copy = tmp;
            neighbor_cloud.push_back( copy );
        }
    }

    Array_double mid_point = atom1.get_position_copy();
    Array_double rel = atom1.relative_position( atom2 );
    rel *= 0.5;
    mid_point += rel;

    // Re-center the system at the mid point between the two atoms
    for( Atom atom : neighbor_cloud ) {
        Array_double pos = atom.get_position_copy();
        Array_double tmp = mid_point;
        tmp -= pos;
        atom.set_position( tmp );
    }
    return neighbor_cloud;
}

std::vector< Atom > create_virtual_neighbors_cloud( Atom& atom1, Atom& atom2 ) {
    std::vector< Atom > neighbor_cloud = create_neighbors_cloud( atom1, atom2 );
    std::vector< Atom > virtual_neighbor_cloud;
    for( int i=0; i < (int) neighbor_cloud.size()-1; i++ ) {
        Array_double rel1 = neighbor_cloud[i].get_position_copy();
        Array_double rel2 = neighbor_cloud[i+1].get_position_copy();
        rel1.add( rel2 );
        rel1.multiply_by_scalar( 0.5 );
        Atom neighbor_copy = neighbor_cloud[i];
        neighbor_copy.set_position( rel1 );
        virtual_neighbor_cloud.push_back( neighbor_copy );
    }
    Array_double rel1 = neighbor_cloud[ (int) neighbor_cloud.size() - 1 ].get_position();
    Array_double rel2 = neighbor_cloud[0].get_position_copy();
    rel1 += rel2;
    rel1 *= 0.5;
    Atom neighbor_copy = neighbor_cloud[ (int) neighbor_cloud.size() - 1 ];
    neighbor_copy.set_position( rel1 );
    virtual_neighbor_cloud.push_back( neighbor_copy );
    return virtual_neighbor_cloud;
}

std::vector< Array_double > get_planar_symmetry_plan( Atom& atom1, Atom& atom2 ) {
    std::vector< Atom > neighbor_cloud = create_neighbors_cloud( atom1, atom2 );
    std::vector< Atom > virtual_neighbor_cloud = create_virtual_neighbors_cloud( atom1, atom2 );
    for( int i=0; i < (int) virtual_neighbor_cloud.size(); i++  ) {
        neighbor_cloud.push_back( virtual_neighbor_cloud[i] );
    }

    Array_double rel = atom1.relative_position( atom2 );
    std::vector< Array_double > plans;
    for( Atom atom_test : neighbor_cloud ) {
        // Apply planar symmetry
        for( Atom atom : neighbor_cloud ) {
            Array_double pos = atom.get_position_copy();
            double side = dot( pos, rel );
            if( side < 0 ) {
                rel.multiply_by_scalar( 2 );
            }
            else if( side > 0 ) {
                rel.multiply_by_scalar( -2 );
            }
            pos.add( rel );
            atom.set_position( pos );
        }

        // Identify the pairs one by one
        bool symmetry_plane_check = true;
        std::vector< Atom > new_neighbor_cloud( neighbor_cloud );
        for( Atom atom : neighbor_cloud ) {
            for( Atom atom_test : new_neighbor_cloud ) {
                Array_double pos = atom.get_position_copy();
                Array_double pos_test = atom_test.get_position_copy();
                if( pos.is_not_equal( pos_test ) ) {
                    symmetry_plane_check = false;
                    break;
                }
            }
        }

        if( symmetry_plane_check ) {
            Array_double tmp_pos = atom_test.get_position_copy();
            Array_double normal_vector = cross( rel, tmp_pos );
            normal_vector.normalize();
            plans.push_back( normal_vector );
        }
    }
    return plans;
}



