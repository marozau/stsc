#ifndef _STSC_TESTS_GENETIC_OPTIMIZER_FUNCTIONS_H_
#define _STSC_TESTS_GENETIC_OPTIMIZER_FUNCTIONS_H_

#include <algorithm>
#include <set>

#include <population.h>
#include <random.h>
#include <limits>

namespace stsc
{
	namespace tests_
	{
		namespace genetic_optimizer
		{
			class turnament_selection : public stsc::genetic_optimizer::selection_function_prototype
			{
				typedef stsc::genetic_optimizer::generation container_type;

			public:
				virtual mating_pool calculate( const container_type& g ) const
				{
					typedef std::set< size_t > turnament_grid;
					turnament_grid tg;
					std::vector< container_type::value_type > base_mp;
					for( container_type::const_iterator it = g.begin(); it != g.end(); ++it )
						base_mp.push_back( *it );

					mating_pool mp;
					mp.reserve( g.size() );
					while ( mp.size() < g.size() )
					{
						size_t first_partner = stsc::genetic_optimizer::details::rand( g.size() - 1 );
						size_t second_partner = 0;
						do
						{
							second_partner = stsc::genetic_optimizer::details::rand( g.size() - 1 );
						} while ( second_partner == first_partner );
						if ( tg.insert( ( first_partner + 1 ) * ( second_partner + 1 ) ).second )
							mp.push_back( base_mp.at( first_partner ).fitness > base_mp.at( second_partner ).fitness ?
							base_mp.at( first_partner ).gene : base_mp.at( second_partner ).gene );
					}
					return mp;
				}
			};
			class test_zero_stop : public stsc::genetic_optimizer::stop_function_prototype
			{
				// todo: test on convergance!!!!
				typedef stsc::genetic_optimizer::generation container_type;

			public:
				virtual const bool calculate( const container_type& g ) const
				{
					static const double stop_flag = -1;
					for (  container_type::const_iterator it = g.begin(); it != g.end(); ++it )
						if ( it->fitness == stop_flag )
							return true;
					return false;
				}
			};
			class test_fitness : public stsc::genetic_optimizer::fitness_function_prototype
			{
				typedef stsc::genetic_optimizer::generation container_type;

			public:
				typedef std::vector< double > equation_type;
				equation_type equation_;
				const double result_;

			public:
				explicit test_fitness( const equation_type& equation, const double result )
					: equation_( equation )
					, result_( result )
				{
				}
				virtual void calculate( container_type& g ) const
				{
					static const double stop_flag = -1;
					double sum = 0;
					for ( container_type::iterator it = g.begin(); it != g.end(); ++it )
					{
						double result = 0;
						for ( size_t i = 0; i != ( *it ).gene->size(); ++i )
						{
							result += equation_.at( i ) * ( *it ).gene->at( i );
						}
						const double diff = fabs( result_ - result );
						sum += diff;
						it->fitness = diff ? ( 1 / diff ) : stop_flag;
					}
					const double inv_sum = 1 / sum;
					for ( container_type::iterator it = g.begin(); it != g.end(); ++it )
						it->fitness = ( it->fitness == stop_flag ) ? stop_flag : it->fitness / inv_sum;
				}
			};
		}
	}
}

#endif //_STSC_TESTS_GENETIC_OPTIMIZER_FUNCTIONS_H_
