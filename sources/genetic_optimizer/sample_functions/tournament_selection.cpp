#include "tournament_selection.h"

#include "generation.h"
#include "random.h"

namespace stsc
{
	namespace genetic_optimizer
	{
		namespace sample_functions
		{
			namespace details
			{
				turnament_selection_helper::turnament_selection_helper( const size_t size )
				{
					genes.reserve( size );
				}
				void turnament_selection_helper::operator () ( const stsc::genetic_optimizer::gene_storage& g )
				{
					genes.push_back( g );
				}
				selection_function_prototype::mating_pool turnament_selection_helper::generate( const size_t size )
				{
					typedef std::set< size_t > turnament_grid;
					turnament_grid tg;
					selection_function_prototype::mating_pool mp;
					mp.reserve( size );
					while ( mp.size() < size )
					{
						size_t first_partner = stsc::genetic_optimizer::details::rand( size - 1 );
						size_t second_partner = 0;
						do
						{
							second_partner = stsc::genetic_optimizer::details::rand( size - 1 );
						} while ( second_partner == first_partner );
						if ( tg.insert( ( first_partner + 1 ) * ( second_partner + 1 ) ).second )
							mp.push_back( genes.at( first_partner ).fitness > genes.at( second_partner ).fitness ?
							genes.at( first_partner ).gene: genes.at( second_partner ).gene );
					}
					return mp;
				}
			}
			selection_function_prototype::mating_pool turnament_selection::calculate( const stsc::genetic_optimizer::generation& g ) const
			{
				details::turnament_selection_helper helper( g.size() );
				g.for_each( helper, g.size() );
				return helper.generate( g.size() );
			}
		}
	}
}
