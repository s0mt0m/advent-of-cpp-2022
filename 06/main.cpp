#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <fstream>
#include <set>
#include <string>


template< std::size_t count >
bool check_unique( const std::array< char, count > &window )
{
    std::set< char > unique;
    auto pred = [ & ]( char c ) { return unique.insert( c ).second; };
    return std::all_of( window.begin(), window.end(), pred );
}

template< std::size_t count >
int move()
{
    std::ifstream input( "input" );
    std::string line;
    std::getline( input, line );

    std::array< char, count > window;
    for ( std::size_t i = 0; i < count - 1; ++i )
        window[ i ] = line[ i ];

    for ( std::size_t i = count - 1; i < line.size(); ++i )
    {
        window[ i % count ] = line[ i ];
        if ( check_unique( window ) )
            return i + 1;
    }

    assert( false );
}

void part_1()
{
    std::cout << move< 4 >() << std::endl;
}

void part_2()
{
    std::cout << move< 14 >() << std::endl;
}

int main()
{
    part_1();
    part_2();
}

