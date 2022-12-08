#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct forest_t : std::vector< std::vector< int > >
{
    using std::vector< std::vector< int > >::vector;

    int height() const { return size(); }
    int width() const { return front().size(); }
};


bool is_valid( const forest_t &forest, int x, int y )
{
    return 0 <= y && y < forest.height()
        && 0 <= x && x < forest.width();
}

// Returns pair which consists of number of visible trees
// and a bool whether we found the border of forest.
std::pair< std::size_t, bool > count( const forest_t &forest,
                                      int x, int y, int dx, int dy )
{
    const auto original = forest[ y ][ x ];
    std::size_t count = 0;
    bool valid = true;

    do
    {
        count++;
        x += dx;
        y += dy;
    } while ( ( valid = is_valid( forest, x, y ) )
              && forest[ y ][ x ] < original );

    return std::pair( count - ( valid ? 0 : 1 ), !valid );
}

std::size_t scenic( const forest_t &forest, int x, int y )
{
    return count( forest, x, y,  0,  1 ).first
         * count( forest, x, y,  0, -1 ).first
         * count( forest, x, y,  1,  0 ).first
         * count( forest, x, y, -1,  0 ).first;
}

bool is_visible( const forest_t &forest, int x, int y )
{
   return count( forest, x, y,  0,  1 ).second
       || count( forest, x, y,  0, -1 ).second
       || count( forest, x, y,  1,  0 ).second
       || count( forest, x, y, -1,  0 ).second;
}


template< typename function_t >
auto explore_forest( const function_t &rate )
{
    std::ifstream input( "input" );

    forest_t forest;
    std::size_t score = 0;

    for ( std::string line; std::getline( input, line ), line != ""; )
        forest.emplace_back( line.begin(), line.end() );

    for ( auto &row : forest )  
        for ( int &cell : row )
            cell -= '0';

    for ( int i = 0; i < forest.width(); ++i )
        for ( int j = 0; j < forest.height(); ++j )
            rate( forest, i, j, score );

    return score;
}

void part_1()
{
    auto visible = []( const forest_t &forest, int x,
                   int y, std::size_t &score )
    {
        if ( is_visible( forest, x, y ) )
            ++score;
    };

    std::cout << explore_forest( visible ) << std::endl;
}

void part_2()
{
    auto high = []( const forest_t &forest, int x,
                   int y, std::size_t &score )
    {
        score = std::max( score, scenic( forest, x, y ) );
    };

    std::cout << explore_forest( high ) << std::endl;
}

int main()
{
    part_1();
    part_2();
}

