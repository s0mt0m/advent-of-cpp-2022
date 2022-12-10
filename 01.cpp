#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>


int64_t read_number( std::ifstream &stream )
{
    int64_t number = 0;

    for ( std::string line; std::getline( stream, line ), line != ""; )
        number += std::stoll( line );

    return number;
}

template< std::size_t size >
int64_t max_sum()
{
    std::ifstream input( "input/01" );

    std::array< int64_t, size + 1 > maxes;
    maxes.fill( std::numeric_limits< int64_t >::min() );

    while ( input )
    {
        maxes[ 0 ] = read_number( input );
        std::sort( maxes.begin(), maxes.end() );
    }
    
    return std::accumulate( maxes.begin() + 1, maxes.end(), 0 );
}

void part_1()
{
    std::cout << max_sum< 1 >() << std::endl;
}

void part_2()
{
    std::cout << max_sum< 3 >() << std::endl;
}

