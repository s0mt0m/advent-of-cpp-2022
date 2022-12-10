#include <array>
#include <cassert>
#include <iostream>
#include <fstream>
#include <set>
#include <string>


struct vec2
{
    int x = 0, y = 0;

    vec2 operator +( vec2 o ) const { return { x + o.x, y + o.y }; }
    vec2 &operator +=( vec2 o ) { *this = *this + o; return *this; }
    vec2 operator *( int c ) const { return { c * x, c * y }; }
    vec2 operator -() const { return { -x, -y }; }
    vec2 operator -( vec2 o ) const { return *this + ( -o ); }
    bool operator <( vec2 o ) const
    {
        return x < o.x || ( x == o.x && y < o.y );
    }
};

vec2 get_dir( char dir )
{
    if ( dir == 'R' ) return {  1,  0 };
    if ( dir == 'L' ) return { -1,  0 };
    if ( dir == 'D' ) return {  0, -1 };
    if ( dir == 'U' ) return {  0,  1 };

    assert( false );
}

void move( vec2 &src, vec2 dest )
{
    const auto sgn = []( int x ) { return x == 0 ? 0 : x > 0 ? 1 : -1; };

    for ( vec2 change = dest - src; std::abs( change.x ) > 1
            || std::abs( change.y ) > 1; change = dest - src )
        src += { sgn( change.x ), sgn( change.y ) };
}

template< std::size_t length >
int simulate_string()
{
    std::ifstream input( "input/09" );

    std::set< vec2 > visited;
    std::array< vec2, length > rope;

    for ( std::string line; std::getline( input, line ), line != ""; )
    {
        const auto dpos = get_dir( line[ 0 ] );
        const auto count = std::strtol( line.data() + 2, nullptr, 10 );

        for ( int i = 0; i < count; ++i )
        {
            rope.front() += dpos;
            for ( std::size_t pos = 0; pos < length - 1; ++pos )
                move( rope[ pos + 1 ], rope[ pos ] );

            visited.insert( rope.back() );
        }
    }

    return visited.size();
}

void part_1()
{
    std::cout << simulate_string< 2 >() << std::endl;
}

void part_2()
{
    std::cout << simulate_string< 10 >() << std::endl;
}

