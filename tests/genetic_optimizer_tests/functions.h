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
			namespace details
			{
				class turnament_selection_helper : public stsc::genetic_optimizer::generation_functor
				{
					typedef stsc::genetic_optimizer::selection_function_prototype selector;
					std::vector<  stsc::genetic_optimizer::generation::value_type > genes;

				public:
					explicit turnament_selection_helper( const size_t size )
					{
						genes.reserve( size );
					}
					virtual void operator () ( const stsc::genetic_optimizer::gene_storage& g )
					{
						genes.push_back( g );
					}
					selector::mating_pool generate( const size_t size )
					{
						typedef std::set< size_t > turnament_grid;
						turnament_grid tg;
						selector::mating_pool mp;
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
				};
				class zero_test_helper : public stsc::genetic_optimizer::generation_functor
				{
					static const double stop_flag = -1;
					bool result_;
				public:
					explicit zero_test_helper()
						: result_( false )
					{
					}
					virtual void operator () ( const stsc::genetic_optimizer::gene_storage& g )
					{
						if ( g.fitness == stop_flag )
							result_ = true;
					}
					const bool result() const
					{
						return result_;
					}
				};
				class test_fitness_helper : public stsc::genetic_optimizer::generation_functor
				{
				};
			}
			class turnament_selection : public stsc::genetic_optimizer::selection_function_prototype
			{
				typedef stsc::genetic_optimizer::generation container_type;

			public:
				virtual mating_pool calculate( const stsc::genetic_optimizer::generation& g ) const
				{
					details::turnament_selection_helper helper( g.size() );
					g.for_each( helper, g.size() );
					return helper.generate( g.size() );
				}
			};
			class test_zero_stop : public stsc::genetic_optimizer::stop_function_prototype
			{
				// todo: test on convergance!!!!
				typedef stsc::genetic_optimizer::generation container_type;

			public:
				virtual const bool calculate( const container_type& g ) const
				{
					details::zero_test_helper helper;
					g.for_each( helper, g.size() );
					return helper.result();
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
					/*static const double stop_flag = -1;
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
						it->fitness = ( it->fitness == stop_flag ) ? stop_flag : it->fitness / inv_sum;*/
				}
			};
		}
	}
}

#endif //_STSC_TESTS_GENETIC_OPTIMIZER_FUNCTIONS_H_
