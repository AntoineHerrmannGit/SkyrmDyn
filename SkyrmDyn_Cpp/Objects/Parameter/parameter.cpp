#include "parameter.h"

#include "Maths/Objects/Array/Array_int/array_int.h"
#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Inputs/Readers/inputs_reader.h"

#include <string>


// Constructor
//-----------------------------------
Parameter::Parameter()
{
    initialize();
}

// Getters
//-----------------------------------
std::string Parameter::get_lattice_name() {
    return lattice_name;
}
double Parameter::get_lattice_step() {
    return lattice_step;
}
double Parameter::get_lattice_step_sigma() {
    return lattice_step_sigma;
}
Array_int Parameter::get_lattice_size() {
    return lattice_size;
}
int Parameter::get_dimension() {
    return dimension;
}

std::string Parameter::get_bounday_conditions() {
    return bounday_conditions;
}

std::string Parameter::get_initial_spin_config() {
    return initial_spin_config;
}
Array_double Parameter::get_initial_spin_axis() {
    return initial_spin_axis;
}
double Parameter::get_initial_spin_ratio() {
    return initial_spin_ratio;
}

Array_double Parameter::get_initial_spin_spiral_vector() {
    return initial_spin_spiral_vector;
}
double Parameter::get_initial_spin_spiral_phase_theta() {
    return initial_spin_spiral_phase_theta;
}
double Parameter::get_initial_spin_spiral_phase_phi() {
    return initial_spin_spiral_phase_phi;
}

std::string Parameter::get_initial_spin_skyrmion_type() {
    return initial_spin_skyrmion_type;
}
Array_double Parameter::get_initial_spin_skyrmion_position() {
    return initial_spin_skyrmion_position;
}
double Parameter::get_initial_spin_skyrmion_radius() {
    return initial_spin_skyrmion_radius;
}
int Parameter::get_initial_spin_skyrmion_charge() {
    return initial_spin_skyrmion_charge;
}
double Parameter::get_initial_spin_skyrmion_phase() {
    return initial_spin_skyrmion_phase;
}

double Parameter::get_exchange_J() {
    return exchange_J;
}
double Parameter::get_DMI() {
    return DMI;
}
std::string Parameter::get_DMI_type() {
    return DMI_type;
}
double Parameter::get_anisotroy_K() {
    return anisotroy_K;
}
double Parameter::get_magnetic_field_H() {
    return magnetic_field_H;
}
double Parameter::get_demag_M_s() {
    return demag_M_s;
}
double Parameter::get_four_spins_F() {
    return four_spins_F;
}
double Parameter::get_biquadratic_B() {
    return biquadratic_B;
}

Array_double Parameter::get_anisotropy_field() {
    return anisotropy_field;
}
Array_double Parameter::get_magnetic_field() {
    return magnetic_field;
}

double Parameter::get_temperature_T() {
    return temperature_T;
}

double Parameter::get_diffusion_D() {
    return diffusion_D;
}

std::string Parameter::get_LLG_equation() {
    return LLG_equation;
}
double Parameter::get_damping() {
    return damping;
}
double Parameter::get_tau() {
    return tau;
}
double Parameter::get_llg_time() {
    return llg_time;
}
double Parameter::get_llg_time_step() {
    return llg_time_step;
}
int Parameter::get_current_llg_step() {
    return current_llg_step;
}

double Parameter::get_current_time() {
    return current_time;
}

std::string Parameter::get_solver() {
    return solver;
}

// Public libraries
//-----------------------------------
void Parameter::update_llg_step() {
    current_llg_step++;
    current_time = current_llg_step * llg_time_step;
}


// Private libraries
//-----------------------------------
void Parameter::initialize() {
    lattice_name = get_string( std::string("lattice_name") );
    lattice_step = get_double( std::string("lattice_step") );
    lattice_step_sigma = get_double( std::string("lattice_step_sigma") );
    lattice_step_sigma += 1;
    lattice_size = get_array_int( std::string("lattice_size") );
    dimension = extract_dimension();

    bounday_conditions = get_string( std::string("bounday_conditions") );

    initial_spin_config = get_string( std::string("initial_spin_config") );
    initial_spin_axis = get_array_double( std::string("initial_spin_axis") );

    initial_spin_ratio = get_double( std::string("initial_spin_ratio") );

    initial_spin_spiral_vector = get_array_double( std::string("initial_spin_spiral_vector") );
    initial_spin_spiral_phase_theta = get_double( std::string("initial_spin_spiral_phase_theta") );
    initial_spin_spiral_phase_phi = get_double( std::string("initial_spin_spiral_phase_phi") );

    initial_spin_skyrmion_type = get_string( std::string("initial_spin_skyrmion_type") );
    initial_spin_skyrmion_position = get_array_double( std::string("initial_spin_skyrmion_position") );
    initial_spin_skyrmion_radius = get_double( std::string("initial_spin_skyrmion_radius") );
    initial_spin_skyrmion_charge = get_int( std::string("initial_spin_skyrmion_charge") );
    initial_spin_skyrmion_phase = get_double( std::string("initial_spin_skyrmion_phase") );

    exchange_J = get_double( std::string("exchange_J") );
    DMI = get_double( std::string("DMI") );
    DMI_type = get_string( std::string("DMI_type") );
    anisotroy_K = get_double( std::string("anisotroy_K") );
    magnetic_field_H = get_double( std::string("magnetic_field_H") );
    demag_M_s = get_double( std::string("demag_M_s") );
    four_spins_F = get_double( std::string("four_spins_F") );
    biquadratic_B = get_double( std::string("biquadratic_B") );

    Array_double tmp = get_array_double( std::string("anisotropy_field") );
    tmp.multiply_by_scalar(anisotroy_K);
    anisotropy_field = tmp;
    tmp = get_array_double( std::string("magnetic_field") );
    tmp.multiply_by_scalar(magnetic_field_H);
    magnetic_field = tmp;

    temperature_T = get_double( std::string("temperature_T") );
    diffusion_D = get_double( std::string("diffusion_D") );

    LLG_equation = get_string( std::string("LLG_equation") );
    damping = get_double( std::string("damping") );
    tau = get_double( std::string("tau") );
    llg_time = get_double( std::string("llg_time") );
    llg_time_step = get_double( std::string("llg_time_step") );

    current_time = 0;

    solver = get_string( std::string("solver") );
}

int Parameter::extract_dimension() {
    std::string dim = lattice_name.substr(0,1);
    int res = std::stoi( dim );
    return res;
}



