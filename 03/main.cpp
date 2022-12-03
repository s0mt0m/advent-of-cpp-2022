#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>


char in_all( const std::vector< std::string_view > &words )
{
    auto first = words.front();

    for ( char c : first )
        if ( std::all_of( words.begin() + 1, words.end(),
                [ c ]( auto s ) { return s.find( c ) != s.npos; } ) )
            return c;

    assert( false );
}

int points( unsigned char c )
{
    assert( std::isalpha( c ) );
    return 1 + ( std::isupper( c ) ? c - 'A' + 26 : c - 'a' );
}

template< std::size_t line_count, std::size_t word_count >
int64_t priority()
{
    static_assert( line_count > 0 );
    static_assert( word_count > 0 );

    std::ifstream input( "input" );
    int64_t priority = 0;

    while ( true )
    {
        std::array< std::string, line_count > lines;
        for ( auto &line : lines )
            std::getline( input, line );

        if ( lines.front().empty() )
            break;

        std::vector< std::string_view > words;
        for ( auto &line : lines )
            for ( std::size_t i = 0; i < word_count; ++i )
                words.emplace_back( line );

        priority += points( in_all( words ) );
    }

    return priority;
}

void part_1()
{
    std::cout << priority< 1, 2 >() << std::endl;
}

void part_2()
{
    std::cout << priority< 3, 1 >() << std::endl;
}

int main()
{
    part_1();
    part_2();
}

