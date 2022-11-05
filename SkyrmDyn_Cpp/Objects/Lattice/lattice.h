#ifndef LATTICE_H
#define LATTICE_H

#include "Objects/Atom/atom.h"
#include "Objects/Cell/cell.h"
#include "Objects/Parameter/parameter.h"

#include "Maths/Objects/Array/Array_int/array_int.h"

#include <vector>
#include <string>

class Lattice
{
public:
    // Constructor
    //-----------------------------------
    Lattice();

    // Getters
    //-----------------------------------
    std::vector< Cell >& get_lattice();
    std::vector< Cell > get_lattice_copy();

    Cell& get_cell( int &x, int &y, int &z );
    Cell get_cell_copy( int &x, int &y, int &z );

    Array_double get_lattice_length();

    int get_dimension();

    Parameter& get_parameter();
    Parameter get_parameter_copy();

    double get_energy();

    Array_double& get_magnetization();
    Array_double get_magnetization_copy();

    double get_topological_charge();

    double& get_temperature();
    double get_temperature_copy();

    // Public libraries
    //-----------------------------------
    Cell& find_cell( Atom& atom );
    std::vector< Cell* > find_neighboring_cells( Cell& cell );
    void attribute_local_environment();
    void setup_nearest_neighbors( Atom& atom );

    void write_atomic_positions();
    void write_atomic_spins();
    void write_atoms();
    void write_energy();
    void write_magnetization();
    void write_temperature();

    Array_double total_magnetization();

    double total_anisotropy_energy();
    double total_biquadratic_energy();
    double total_dipole_energy();
    double total_dmi_energy();
    double total_four_spins_energy();
    double total_heisenberg_energy();
    double total_zeeman_energy();

    double total_energy();
    double compute_total_energy();

    void euler_llg_evolution();

    double total_topological_charge();


private:
    std::vector< Cell > lattice;
    Parameter parameters;
    Array_double lattice_length;

    double energy = 0;
    Array_double magnetization;
    double topological_charge = 0;
    double temperature = 0;
    int nb_atoms = 0;

    void setup_lattice_configuration();
    void setup_initial_spin_config();

    void setup_ferromagnetic();
    void setup_ferrimagnetic();
    void setup_antiferromagnetic();
    void setup_spin_spiral();
    void setup_spin_skyrmion();
    void setup_random();

    void setup_skyrmion_charge_1();
    void setup_skyrmion_large_charge();

    void attribute_nearest_neighbors();

    void euler_illg_step();
    void euler_llg_step();
    void euler_ll_step();

    void setup_atomic_memory();
    void setup_neighbors();

    Atom apply_tor_boundary_conditions( Atom& atom1, Atom& atom2 );
    Atom apply_sphere_boundary_conditions( Atom& atom1, Atom& atom2 );
    Atom apply_linear_boundary_conditions( Atom& atom1, Atom& atom2 );
};

#endif // LATTICE_H
