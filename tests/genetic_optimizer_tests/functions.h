#ifndef _STSC_TESTS_GENETIC_OPTIMIZER_FUNCTIONS_H_
#define _STSC_TESTS_GENETIC_OPTIMIZER_FUNCTIONS_H_

#include <algorithm>

#include <population.h>
#include <random.h>

namespace stsc
{
	namespace tests_
	{
		namespace genetic_optimizer
		{
			class turnament_selection : public stsc::genetic_optimizer::population::selection_function
			{
			public:
				virtual gene_container calculate( const gene_container& g, const fitness_container& f )
				{
					gene_container parant_pool;
					parant_pool.reserve( g.size() );
					while ( parant_pool.size() < g.size() )
					{
						size_t first_partner = stsc::genetic_optimizer::details::rand( g.size() - 1 );
						size_t second_partner = stsc::genetic_optimizer::details::rand( g.size() - 1 );
						parant_pool.push_back( f.at( first_partner ) > f.at( second_partner ) ?
							g.at( first_partner ) : g.at( second_partner ) );
					}
					return parant_pool;
				}
			};
			class test_zero_stop : public stsc::genetic_optimizer::population::stop_function
			{
			public:
				virtual const bool calculate( const fitness_container& f )
				{
					static const fitness_type max_percent = 100;
					 fitness_container::const_iterator it = std::find( f.begin(), f.end(), max_percent );
					 return it != f.end();
				}
			};
			class test_fitness : public stsc::genetic_optimizer::population::fitness_function
			{
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
				virtual fitness_container calculate( const gene_container& g )
				{
					std::vector< double > results;
					results.reserve( g.size() );
					double sum = 0;
					for ( gene_container::const_iterator it = g.begin(); it != g.end(); ++it )
					{
						double result = 0;
						for ( size_t i = 0; i != ( *it )->size(); ++i )
						{
							result += equation_.at( i ) * ( *it )->at( i );
						}
						const double diff = fabs( result_ - result );
						results.push_back( diff != 0.0 ? 1 / diff : 0.0 );
						sum += diff;
					}
					const double inv_sum = ( sum != 0.0 ? 1 / sum : 1 ) ;
					fitness_container f;
					f.reserve( g.size() );
					for ( std::vector< double >::const_iterator it = results.begin(); it != results.end(); ++it )
						f.push_back( ( float )( ( *it ) / inv_sum ) );

					return f;
				}
			};
		}
	}
}

#endif //_STSC_TESTS_GENETIC_OPTIMIZER_FUNCTIONS_H_
