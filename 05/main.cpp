#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


auto parse_crates( std::ifstream &input )
{
    std::vector< std::string > lines;
    std::size_t columns = 0;

    for ( std::string line; std::getline( input, line ),
            std::strncmp( line.data(), " 1", 2 ) != 0; )
    {
        columns = std::max( columns, ( line.length() + 1 ) / 4 );
        lines.push_back( line );
    }

    std::vector< std::vector< char > > crates( columns );

    for ( auto it = lines.rbegin(); it != lines.rend(); ++it )
    {
        std::string_view line( *it );

        for ( std::size_t i = 0; i < columns; ++i, line.remove_prefix( 4 ) )
            if ( !line.empty() && line[ 1 ] != ' ' )
                crates[ i ].push_back( line[ 1 ] );
    }

    return crates;
}

std::string move( bool take_one )
{
    std::ifstream input( "input" );

    auto crates = parse_crates( input );

    input.get(); // skip the blank line

    for ( std::string line; std::getline( input, line ), line != ""; )
    {
        int count, from, to;
        int read = std::sscanf( line.data(), "move %d from %d to %d",
                                &count, &from, &to );
        assert( read == 3 );

        auto &src  = crates[ from - 1 ];
        auto &dest = crates[ to   - 1 ];

        if ( take_one )
            std::reverse( src.end() - count, src.end() );

        dest.insert( dest.end(), src.end() - count, src.end() );
        src.resize( src.size() - count );
    }

    std::string result;
    for ( auto column : crates )
        result.push_back( column.back() );

    return result;
}

void part_1()
{
    std::cout << move( true ) << std::endl;
}

void part_2()
{
    std::cout << move( false ) << std::endl;
}

int main()
{
    part_1();
    part_2();
}

