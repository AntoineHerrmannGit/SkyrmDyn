#include "File_management/file_management.h"

#include "Inputs/Readers/system_reader.h"

#include "Error_messages/error_messages.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <stdio.h>

#include <fstream>

std::vector<std::string> get_directories(const std::string& directory)
{
    std::vector<std::string> list_of_directories;
    for(auto& entity : std::filesystem::recursive_directory_iterator(directory))
        if (entity.is_directory())
            list_of_directories.push_back(entity.path().string());
    return list_of_directories;
}

void clear_output_directories() {
    std::vector<std::string> list_of_directories = get_directories( "./Outputs" );
    if( (int) list_of_directories.size() != 0 ){
        for( std::string directory : list_of_directories ) {
            for (auto& file : std::filesystem::directory_iterator( directory )) {
                    std::filesystem::remove_all( file );
            }
        }
    }
}

void clear_directory( std::string directory ) {
    std::string path = "./Outputs/" + directory + "/";
    for (auto& file : std::filesystem::directory_iterator( path )) {
            std::filesystem::remove_all( file );
    }
}

void delete_file( std::string directory, std::string filename ) {
    if( std::filesystem::remove( directory + filename ) != 0 ) {
        throw( OperationError( "removing", filename ) );
    }
}

void move_file( std::string filename, std::string initial_directory, std::string target_directory ) {
    std::filesystem::copy_file( initial_directory + filename, target_directory + filename );
}

void replace_line_in_file( std::string old_line, std::string new_line, std::string filename ) {
    std::ifstream read( filename );
    std::string filecopy = filename.substr( 0, filename.size()-4 ) + "_copy" + filename.substr( filename.size()-4, filename.size() );
    std::ofstream write( filecopy );

    std::string line;
    if( read && write ) {
        // Read the file line by line
        while( std::getline( read, line ) ) {
            // If the old line is found
            if( line.find( old_line ) != std::string::npos ) {
                // Rewrite the file line by line until the one of interest
                write << new_line + "\n";
            }
            else {
                write << line + "\n";
            }
        }
    }
    else {
        throw( DeclarationError( "\"read\" and/or \"write\"" ) );
    }

    read.close();
    write.close();

    std::remove( filename.c_str() );
    std::rename( filecopy.c_str(), filename.c_str() );
}

void make_archive() {
    int c = 0;
    for (const auto & entry : std::filesystem::directory_iterator( "./Archive" ) ) {
        c++;
    }
    std::string new_archive = "./Archive/Archive_" + std::to_string(c);
    std::filesystem::copy( "./Outputs", new_archive, std::filesystem::copy_options::recursive );
}







