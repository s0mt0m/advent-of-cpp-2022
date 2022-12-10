#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <fstream>
#include <set>
#include <string>


bool check_unique( std::string_view window )
{
    std::set< char > unique;
    auto pred = [ & ]( char c ) { return unique.insert( c ).second; };
    return std::all_of( window.begin(), window.end(), pred );
}

int move( std::size_t count )
{
    std::ifstream input( "input/06" );
    std::string line;
    std::getline( input, line );

    for ( std::size_t i = count - 1; i < line.size(); ++i )
        if ( check_unique( { line.data() + i - count + 1, count } ) )
            return i + 1;

    assert( false );
}

void part_1()
{
    std::cout << move( 4 ) << std::endl;
}

void part_2()
{
    std::cout << move( 14 ) << std::endl;
}

