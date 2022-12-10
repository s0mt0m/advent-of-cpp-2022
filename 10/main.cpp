#include <string>
#include <iostream>
#include <fstream>


template< typename function_t >
void evaluate( const function_t &check )
{
    std::ifstream input( "input" );

    int64_t cycle = 1;
    int64_t value = 1;

    auto check_cycles = [ & ]( std::size_t count )
    {
        for ( std::size_t i = 0; i < count; ++i )
            check( cycle++, value );
    };

    for ( std::string line; std::getline( input, line ), line != ""; )
    {
        if ( line == "noop" )
            check_cycles( 1 );
        else
        {
            check_cycles( 2 );
            value += std::strtol( line.data() + 5, nullptr, 10 );
        }
    }
}

void part_1()
{
    int64_t score = 0;
    auto check_strength = [ & ]( int64_t cycle, int64_t value )
    {
        if ( ( cycle + 20 ) % 40 == 0 )
            score += value * cycle;
    };

    evaluate( check_strength );

    std::cout << score << std::endl;
}

void part_2()
{
    std::string display;
    auto draw_pixel = [ & ]( int64_t cycle, int64_t value )
    {
        const auto pos = cycle % 40 == 0 ? 40 : cycle % 40;
        const bool draw = value <= pos && pos < value + 3;
        display += draw ? '#' : '.';
    };

    evaluate( draw_pixel );

    std::string_view answer( display );
    for ( std::size_t i = 0; i < 240; i += 40 )
        std::cout << answer.substr( i, 40 ) << std::endl;
}

int main()
{
    part_1();
    part_2();
}

