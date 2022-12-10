#include <cassert>
#include <iostream>
#include <fstream>
#include <string>


int get( int tool )
{
    switch ( tool )
    {
        case 'A': case 'X': return 0;
        case 'B': case 'Y': return 1;
        case 'C': case 'Z': return 2;
    }

    assert( false );
}

template< typename function_t >
int64_t calculate( function_t round )
{
    std::ifstream input( "input/02" );
    int64_t score = 0;

    for ( std::string line; std::getline( input, line ), line != ""; )
    {
        int first  = get( line[ 0 ] );
        int second = get( line[ 2 ] );

        score += round( first, second );
    }

    return score;
}

void part_1()
{
    auto round = []( int opponent, int player )
    {
        return 3 * ( ( player - opponent + 4 ) % 3 )
            + player + 1;
    };

    std::cout << calculate( round ) << std::endl;
}

void part_2()
{
    auto round = []( int opponent, int result )
    {
        return ( opponent + result + 2 ) % 3 + 1
            + 3 * result;
    };

    std::cout << calculate( round ) << std::endl;
}

