#ifndef PARAMETER_H
#define PARAMETER_H

#include "Maths/Objects/Array/Array_double/array_double.h"
#include "Maths/Objects/Array/Array_int/array_int.h"

#include <string>

class Parameter
{
public:
    // Constructor
    //-----------------------------------
    Parameter();

    // Getters
    //-----------------------------------
    std::string get_lattice_name();
    double get_lattice_step();
    double get_lattice_step_sigma();
    Array_int get_lattice_size();
    int get_dimension();

    std::string get_bounday_conditions();

    std::string get_initial_spin_config();
    Array_double get_initial_spin_axis();
    double get_initial_spin_ratio();

    Array_double get_initial_spin_spiral_vector();
    double get_initial_spin_spiral_phase_theta();
    double get_initial_spin_spiral_phase_phi();

    std::string get_initial_spin_skyrmion_type();
    Array_double get_initial_spin_skyrmion_position();
    double get_initial_spin_skyrmion_radius();
    int get_initial_spin_skyrmion_charge();
    double get_initial_spin_skyrmion_phase();

    double get_exchange_J();
    double get_DMI();
    std::string get_DMI_type();
    double get_anisotroy_K();
    double get_magnetic_field_H();
    double get_demag_M_s();
    double get_four_spins_F();
    double get_biquadratic_B();

    Array_double get_anisotropy_field();
    Array_double get_magnetic_field();

    double get_temperature_T();
    double get_diffusion_D();

    std::string get_LLG_equation();
    double get_damping();
    double get_tau();
    double get_llg_time();
    double get_llg_time_step();
    int get_current_llg_step();

    double get_current_time();

    std::string get_solver();

    // Public libraries
    //-----------------------------------
    void update_llg_step();

private:
    std::string lattice_name = "3D_simple_cubic";
    double lattice_step = 1;
    double lattice_step_sigma = 1.01;
    Array_int lattice_size;
    int dimension;
    std::string bounday_conditions = "none";

    std::string initial_spin_config = "ferromagnetic";
    Array_double initial_spin_axis;

    double initial_spin_ratio = 1;

    Array_double initial_spin_spiral_vector;
    double initial_spin_spiral_phase_theta = 0;
    double initial_spin_spiral_phase_phi = 0;

    std::string initial_spin_skyrmion_type = "Neel";
    Array_double initial_spin_skyrmion_position;
    double initial_spin_skyrmion_radius = 10;
    int initial_spin_skyrmion_charge = 1;
    double initial_spin_skyrmion_phase = 0;

    double exchange_J = 1;
    double DMI = 1;
    std::string DMI_type = "Bloch";
    double anisotroy_K = 1;
    double magnetic_field_H = 1;
    double demag_M_s = 1;
    double four_spins_F = 1;
    double biquadratic_B = 1;

    Array_double anisotropy_field;
    Array_double magnetic_field;

    double temperature_T = 0;
    double diffusion_D = 1;

    std::string LLG_equation = "llg";
    double damping = 0;
    double tau = 0;
    double llg_time = 100;
    double llg_time_step = 1e-4;
    int current_llg_step = 0;

    double current_time = 0;

    std::string solver = "euler";

    // Private libraries
    //-----------------------------------

    void initialize();
    int extract_dimension();
};

#endif // PARAMETER_H
