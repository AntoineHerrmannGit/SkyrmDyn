#include "Objects/Lattice/lattice.h"

#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Error_messages/error_messages.h"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <string.h>


void Lattice::write_atomic_positions() {
    std::string filename = "./Outputs/Positions/position.dat";
    std::ofstream write( filename, std::ios::app );
    for( Cell cells : lattice ) {
        Array_double cell_position = cells.get_position();
        for( Atom atoms : cells.get_cell() ) {
            Array_double atomic_position = atoms.get_position();
            atomic_position.add( cell_position );
            for( int i=0; i<atomic_position.get_dimension(); i++ ) {
                write << std::setprecision(6)
                      << atomic_position.get_component( i ) << ",   ";
            }
            write << " \n";
        }
    }
    write.close();
}

void Lattice::write_atomic_spins() {
    int step = parameters.get_current_llg_step();
    for( Cell cells : lattice ) {
        for( Atom atoms : cells.get_cell() ) {
            atoms.write_spin( step );
        }
    }
}

void Lattice::write_atoms() {
    int step = parameters.get_current_llg_step();
    std::string number = std::to_string( step );
    std::string completion = "000000000000";
    std::string tmp = completion.substr( number.size() ) + number;
    std::string filename = "./Outputs/Povray_data_files/spin_" + tmp + ".dat";
    std::ofstream write( filename, std::ios::app );
    for( Cell cells : lattice ) {
        Array_double cell_position = cells.get_position();
        for( Atom atoms : cells.get_cell() ) {
            Array_double atomic_position = atoms.get_position();
            atomic_position.add( cell_position );
            write << "Spin(   ";
            for( int i=0; i<atomic_position.get_dimension(); i++ ) {
                write << std::setprecision(6)
                      << atomic_position.get_component( i ) << ",   ";
            }
            for( int i=0; i<atoms.get_spin().get_dimension(); i++ ) {
                if( i != atoms.get_spin().get_dimension() - 1 ) {
                    write << std::setprecision(6)
                          << atoms.get_spin().get_component( i ) << ",   ";
                }
                else {
                    write << std::setprecision(6)
                          << atoms.get_spin().get_component( i ) << "    ) \n";
                }
            }
        }
    }
    write.close();
}

void Lattice::write_energy() {
    std::string filename = "./Outputs/Energy/energy.dat";
    std::ofstream write( filename, std::ios::app );
    if( write ) {
        write<< std::setprecision(6) << parameters.get_current_time() << "   " << std::setprecision(6) << energy << "\n";
    }
    else {
        throw( DeclarationError( "write" ) );
    }
}

void Lattice::write_magnetization() {
    std::string filename = "./Outputs/Magnetization/magnetization.dat";
    std::ofstream write( filename, std::ios::app );
    if( write ) {
        write<< std::setprecision(6) << parameters.get_current_time() << "   ";
        for( int i=0; i<3; i++ ) {
            write<< std::setprecision(6) << magnetization.get_component( i ) << "   ";
        }
        write<< std::setprecision(6) << magnetization.norm() << " \n";
    }
    else {
        throw( DeclarationError( "write" ) );
    }
}

void Lattice::write_temperature() {
    std::string filename = "./Outputs/Temperature/temperature.dat";
    std::ofstream write( filename, std::ios::app );
    if( write ) {

    }
    else {
        throw( DeclarationError( "write" ) );
    }
}

