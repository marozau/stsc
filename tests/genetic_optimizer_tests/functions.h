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
				public:
					static const stsc::genetic_optimizer::gene_storage::fitness_type stop_flag;

				private:
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
				const stsc::genetic_optimizer::gene_storage::fitness_type zero_test_helper::stop_flag = -1;
				class test_fitness_helper : public stsc::genetic_optimizer::generation_functor
				{
				public:
					typedef std::vector< stsc::genetic_optimizer::gene_storage > storage;

				private:					
					storage storage_;

					stsc::genetic_optimizer::generation g_;

					typedef std::vector< double > equation_type;
					const equation_type& equation_;
					const double& result_;

					double sum_;
					
				public:
					test_fitness_helper( const equation_type& equation, const double& result )
						: equation_( equation )
						, result_( result ) 
						, sum_( 0.0 )
					{
					}
					virtual void operator () ( const stsc::genetic_optimizer::gene_storage& g )
					{
						storage_.push_back( g );
						double result = 0;
						for ( size_t i = 0; i != g.gene->size(); ++i )
						{
							result += equation_.at( i ) * g.gene->at( i );
						}
						const double diff = fabs( result_ - result );
						sum_ += diff;
						storage_.back().fitness = diff ? ( 1 / diff ) : zero_test_helper::stop_flag;
					}
					void new_generation( stsc::genetic_optimizer::generation& g )
					{
						const double invert_sum = ( sum_ != 0 ) ? 1 / sum_ : 1;				
						for ( storage::iterator it = storage_.begin(); it != storage_.end(); ++it )
						{
							const stsc::genetic_optimizer::gene_storage::fitness_type new_fitness = 
								( it->fitness == zero_test_helper::stop_flag ) ? zero_test_helper::stop_flag : it->fitness / invert_sum;
							g.insert( new_fitness, it->gene );
						}
					}
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
				virtual void calculate( const container_type& g ) const
				{
					details::test_fitness_helper helper( equation_, result_ );
					g.for_each( helper, g.size() );
					const size_t old_size = g.size();
					stsc::genetic_optimizer::generation new_generation;
					helper.new_generation( new_generation );
					const_cast< container_type& >( g ).swap( new_generation );
					if ( g.size() != old_size )
						throw std::logic_error( "generation fitness update error: new generation size differs from origin size" );
				}
			};
		}
	}
}

#endif //_STSC_TESTS_GENETIC_OPTIMIZER_FUNCTIONS_H_
