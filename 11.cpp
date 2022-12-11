#include <array>
#include <cassert>
#include <functional>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>


struct worry_operation
{
    const std::array< int64_t, 2 > nums;
    const char op;

    worry_operation( int64_t first, int64_t second, char op )
        : nums{ first, second }, op( op ) {}

    int64_t operator ()( int64_t old ) const
    {
        const auto first  = nums[ 0 ] == -1 ? old : nums[ 0 ];
        const auto second = nums[ 1 ] == -1 ? old : nums[ 1 ];
        const bool add = op == '+';

        return add ? first + second : first * second;
    }
};

struct monkey
{
    std::vector< int64_t > items;
    const worry_operation change_worry_level;

    const int64_t divisor;
    const std::array< int64_t, 2 > successors;
};


std::vector< int64_t > parse_items( std::string_view line )
{
    std::vector< int64_t > items;

    for ( line.remove_prefix( 18 ); !line.empty(); )
    {
        items.push_back( std::strtol( line.data(), nullptr, 10 ) );
        const auto pos = line.find( ' ' );
        line.remove_prefix( pos == line.npos ? line.size() : pos + 1 );
    }

    return items;
}

int64_t parse_last_number( std::string_view line )
{
    const auto pos = line.find_last_of( ' ' );
    assert( pos != line.npos );
    return std::strtol( line.data() + pos, nullptr, 10 );
}

worry_operation parse_operation( std::string_view line )
{
    const auto equals = line.find_first_of( '=' );
    const auto op_pos = line.find_first_of( "+*" );

    const auto first = line.substr( equals + 2, op_pos - equals - 3 );
    const auto second = line.substr( op_pos + 2 );

    const auto get = []( auto s ) { return s == "old" ? -1
            : std::strtol( s.data(), nullptr, 10 ); };

    return { get( first ), get( second ), line[ op_pos ] };
}

monkey parse_monkey( std::ifstream &input )
{
    std::string line;

    const auto parse = [ & ]( const auto &parse )
    {
        std::getline( input, line );
        return parse( line );
    };

    std::getline( input, line ); // ignore first line

    auto items             = parse( parse_items );
    auto worry_level       = parse( parse_operation );
    const int64_t divisor  = parse( parse_last_number );
    const int64_t if_true  = parse( parse_last_number );
    const int64_t if_false = parse( parse_last_number );

    std::getline( input, line ); // read delimiter line

    return { std::move( items ), std::move( worry_level ),
             divisor, { if_false, if_true } };
}

int64_t simulate( int64_t rounds, int64_t worry_reduce )
{
    std::ifstream input( "input/11" );

    std::vector< monkey > monkeys;

    while ( input )
        monkeys.push_back( parse_monkey( input ) );

    std::vector< int64_t > throws( monkeys.size() );

    int64_t lcm = std::transform_reduce( monkeys.begin(), monkeys.end(),
            1, std::multiplies(), []( auto &m ) { return m.divisor; } );

    for ( int64_t i = 0; i < rounds; ++i )
    {
        for ( std::size_t j = 0; j < monkeys.size(); ++j )
        {
            auto &monkey = monkeys[ j ];
            for ( int64_t item : monkey.items )
            {
                item = monkey.change_worry_level( item );
                item = ( item / worry_reduce ) % lcm;

                const auto divides = item % monkey.divisor == 0;
                const auto next = monkey.successors[ divides ];
                monkeys[ next ].items.push_back( item );

                ++throws[ j ];
            }

            monkey.items.clear();
        }
    }

    std::nth_element( throws.begin(), throws.begin() + 2, throws.end() );
    return throws.back() * throws[ throws.size() - 2 ];
}

void part_1()
{
    std::cout << simulate( 20, 3 ) << std::endl;
}

void part_2()
{
    std::cout << simulate( 10000, 1 ) << std::endl;
}

