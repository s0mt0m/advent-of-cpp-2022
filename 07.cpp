#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <set>
#include <stack>
#include <string>


struct file
{
    std::string name;
    std::size_t size;

    file( std::string_view name, std::size_t size )
        : name( name ), size( size )
    {}
};

struct dir : file
{
    std::set< std::unique_ptr< file > > files;
    std::set< std::unique_ptr< dir > > dirs;

    dir( std::string_view name )
        : file( name, 0 )
    {}
};


dir parse_fs()
{
    std::ifstream input( "input/07" );

    dir root( "/" );
    std::stack< dir * > path( { &root } );
    const auto empty_path = path;

    for ( std::string _line; std::getline( input, _line ), _line != ""; )
    {
        std::string_view line( _line );

        if ( line == "$ ls" )
            continue;

        if ( line.substr( 0, 4 ) == "$ cd" )
        {
            auto dir = line.substr( 5 );

            if ( dir == ".." )
                path.pop();

            if ( dir == "/" )
                path = empty_path;

            if ( dir == ".." || dir == "/" )
                continue;

            auto &dirs = path.top()->dirs;
            auto it = std::find_if( dirs.begin(), dirs.end(),
                    [ dir ]( auto &d ) { return d->name == dir; } );
            assert( it != dirs.end() );
            path.push( it->get() );
        }

        if ( line.substr( 0, 3 ) == "dir" )
        {
            auto dir_ = std::make_unique< dir >( line.substr( 4 ) );
            path.top()->dirs.insert( std::move( dir_ ) );
        }

        if ( std::isdigit( line[ 0 ] ) )
        {
            const auto space = line.find_first_of( ' ' );
            const auto size = std::strtoll( line.data(), nullptr, 10 );

            line.remove_prefix( space + 1 );
            auto file_ = std::make_unique< file >( line, size );
            path.top()->files.insert( std::move( file_ ) );
        }
    }

    return root;
}

std::size_t fill_sizes( dir &root )
{
    for ( const auto &file : root.files )
        root.size += file->size;

    for ( auto &dir : root.dirs )
        root.size += fill_sizes( *dir );

    return root.size;
}

std::size_t count( dir &root )
{
    std::size_t result = root.size > 100000 ? 0 : root.size;

    for ( const auto &dir : root.dirs )
        result += count( *dir );

    return result;
}

std::size_t smallest( dir &root, std::size_t minimal )
{
    constexpr auto max = std::numeric_limits< std::size_t >::max();
    auto result = root.size >= minimal ? root.size : max;

    for ( const auto &dir : root.dirs )
        result = std::min( result, smallest( *dir, minimal ) );

    return result;
}


void part_1()
{
    auto root = parse_fs();
    fill_sizes( root );

    std::cout << count( root ) << std::endl;
}

void part_2()
{
    auto root = parse_fs();
    const auto needed = fill_sizes( root ) - 40'000'000;

    std::cout << smallest( root, needed ) << std::endl;
}

