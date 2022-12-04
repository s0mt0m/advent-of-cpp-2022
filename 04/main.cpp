#include <cassert>
#include <iostream>
#include <fstream>
#include <string>


template< typename predicate_t >
int overlaps( predicate_t condition )
{
    std::ifstream input( "input" );
    int score = 0;

    for ( std::string line; std::getline( input, line ), line != ""; )
    {
        int xl, xr, yl, yr;
        int count = sscanf( line.data(), "%d-%d,%d-%d", &xl, &xr, &yl, &yr );
        assert( count == 4 );

        if ( condition( xl, xr, yl, yr ) )
            score += 1;
    }

    return score;
}

void part_1()
{
    auto inside = []( int xl, int xr, int yl, int yr )
    {
        return ( xl <= yl && yr <= xr ) || ( yl <= xl && xr <= yr );
    };

    std::cout << overlaps( inside ) << std::endl;
}

void part_2()
{
    auto overlap = []( int xl, int xr, int yl, int yr )
    {
        return std::min( xr, yr ) - std::max( xl, yl ) + 1 > 0;
    };

    std::cout << overlaps( overlap ) << std::endl;
}

int main()
{
    part_1();
    part_2();
}

