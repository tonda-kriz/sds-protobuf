/***************************************************************************\
* Name              : file io                                               *
* Description       : basic file io                                         *
* Author            : antonin.kriz@gmail.com                                *
* ------------------------------------------------------------------------- *
* This is free software; you can redistribute it and/or modify it under the *
* terms of the MIT license. A copy of the license can be found in the file  *
* "LICENSE" at the root of this distribution.                               *
\***************************************************************************/

#include "file.h"
#include <cstdio>
#include <system_error>

auto load_file( const std::filesystem::path & file_path ) -> std::string
{
    const auto file_size = std::filesystem::file_size( file_path );
    auto file_content    = std::string( file_size, '\0' );

    if( auto * p_file = fopen( file_path.c_str( ), "rb" ); p_file )
    {
        const auto read = fread( file_content.data( ), 1, file_content.size( ), p_file );
        fclose( p_file );
        file_content.resize( read );
        return file_content;
    }
    perror( file_path.c_str( ) );
    throw std::system_error( std::make_error_code( std::errc( errno ) ) );
}

void save_file( const std::filesystem::path & file_path, std::string_view file_content )
{
    if( auto * p_file = fopen( file_path.c_str( ), "wb" ); p_file )
    {
        const auto written = fwrite( file_content.data( ), 1, file_content.size( ), p_file );
        fclose( p_file );
        if( written == file_content.size( ) )
        {
            return;
        }
    }
    perror( file_path.c_str( ) );
    throw std::system_error( std::make_error_code( std::errc( errno ) ) );
}