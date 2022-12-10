#include <iostream>

void part_1();
void part_2();


int main( int argc, char **argv )
{
    if ( argc != 2 )
    {
        std::cerr << "Usage: '" << argv[ 0 ] << " PART" << std::endl;
        return 1;
    }

    const int part = argv[ 1 ][ 0 ] - '0';
    part == 2 ? part_2() : part_1();
}

