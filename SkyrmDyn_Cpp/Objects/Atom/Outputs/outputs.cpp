#include "Objects/Atom/atom.h"

#include <iostream>
#include <iomanip>
#include <fstream>

#include <string.h>

void Atom::write_spin( int step ) {
    std::string number = std::to_string( step );
    std::string completion = "000000000000";
    std::string tmp = completion.substr( number.size() ) + number;
    std::string filename = "./Outputs/Spins/spin_" + tmp + ".dat";
    std::ofstream write( filename, std::ios::app );
    for( int i=0; i<spin.get_dimension(); i++ ) {
        write << std::setprecision(6)
              << spin.get_component( i ) << "   ";
    }
    write << " \n";
    write.close();
};
