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
int64_t max_sum( std::string filepath )
{
    std::ifstream input( filepath );

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
    std::cout << max_sum< 1 >( "input" ) << std::endl;
}

void part_2()
{
    std::cout << max_sum< 3 >( "input" ) << std::endl;
}

int main()
{
    part_1();
    part_2();
}

