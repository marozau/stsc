#include "test_registrator.h"

#include <iostream>

#include <population.h>
#include "functions.h"

using namespace stsc::genetic_optimizer;

namespace stsc
{
	namespace tests_
	{
		namespace genetic_optimizer
		{
			namespace details
			{
				class generation_out : public stsc::genetic_optimizer::generation_functor
				{
				public:
					virtual void operator () ( const gene_storage& g )
					{
						std::cout << "equation: " 
						<< g.gene->at( 0 ) << " "
						<< g.gene->at( 1 ) << " "
						<< g.gene->at( 2 ) << " "
						<< " ; rating: " << g.fitness << std::endl;
					}
				};
				class renewal_helper : stsc::genetic_optimizer::generation_functor
				{
					bool filled_;
					std::vector< size_t > storage_;
					size_t i_;
					size_t diffs_;

				public:
					renewal_helper()
						: filled_( false )
						, i_( 0 )
						, diffs_( 0 )

					{
					}
					virtual void operator () ( const gene_storage& g )
					{
						if ( filled_ )
						{
							if ( storage_.at( i_ ) != g.gene->hash() )
								++diffs_;
						}
						else
						{
							storage_.push_back( g.gene->hash() );
						}
					}
					void set_filled()
					{
						filled_ = true;
					}
					const size_t get_diff() const
					{
						return diffs_;
					}
				};
			}
			class population_tests
			{
				typedef boost::shared_ptr< population > p_ptr;
				static population_settings test_population_settings_;

				static void fill_genome( genome& gt, const allele::value_type min, const allele::value_type max )
				{
					gt.add_allele( new allele( min, max, 1.0 ) );
				}

			public:
				static void initialization()
				{
					test_population_settings_.population_size = 10;
					test_population_settings_.reproduction_rate = 1.0;
					test_population_settings_.mutation_rate = 1.0;
					test_population_settings_.survival_size = 3;
					test_population_settings_.max_reproduction_iteration_count = 10;
					test_population_settings_.global_max_reproduction_iteration_count = 30;
				}
				static void constructor_tests()
				{
					test_fitness::equation_type e;
					e.push_back( 1.0 );
					e.push_back( 2.0 );
					e.push_back( 3.0 );
					const double result = 35.0;
					test_fitness tf( e, result );
					turnament_selection ts;
					test_zero_stop tzs;

					genome gt_;
					fill_genome( gt_, 0.0, 5.0 );
					fill_genome( gt_, 0.0, 10.0 );
					fill_genome( gt_, 0.0, 35.0 );

					p_ptr p;
					BOOST_CHECK_NO_THROW( p.reset( new population( gt_, tf, turnament_selection(), test_zero_stop(), test_population_settings_ ) ) );
					BOOST_CHECK_EQUAL( p->generation_.size(), 10 );
					BOOST_CHECK_EQUAL( p->settings_.mutation_rate, 1.0 );
					BOOST_CHECK_EQUAL( p->settings_.reproduction_rate, 1.0 );
					BOOST_CHECK_EQUAL( p->settings_.survival_size, 3 );
					BOOST_CHECK_EQUAL( p->settings_.max_reproduction_iteration_count, 10 );
					BOOST_CHECK_EQUAL( p->settings_.global_max_reproduction_iteration_count, 30 );

					BOOST_CHECK_NO_THROW( p.reset( new population( gt_, tf, turnament_selection(), test_zero_stop(), test_population_settings_ ) ) );
				}				
				static void renewal_tests()
				{
					genome gt_;
					fill_genome( gt_, 0.0, 100.0 );
					fill_genome( gt_, 0.0, 200.0 );
					fill_genome( gt_, 0.0, 300.0 );

					test_fitness::equation_type e;
					e.push_back( 1.0 );
					e.push_back( 2.0 );
					e.push_back( 3.0 );
					const double result = 35.0;
					test_fitness tf( e, result );
					turnament_selection ts;
					test_zero_stop tzs;

					p_ptr p;
					BOOST_CHECK_NO_THROW( p.reset( new population( gt_, tf, turnament_selection(), test_zero_stop(), test_population_settings_ ) ) );
					details::renewal_helper helper;
					p->generation_.for_each( helper, p->generation_.size() );
					helper.set_filled();
					BOOST_CHECK_NO_THROW( p->renewal() );
					p->generation_.for_each( helper, p->generation_.size() );
					BOOST_CHECK_EQUAL( helper.get_diff() == p->generation_.size(), true );
				}
				static void life_cycle_tests()
				{
					genome gt_;
					fill_genome( gt_, 0.0, 100.0 );
					fill_genome( gt_, 0.0, 200.0 );
					fill_genome( gt_, 0.0, 300.0 );

					test_fitness::equation_type e;
					e.push_back( 1.0 );
					e.push_back( 2.0 );
					e.push_back( 3.0 );
					const double result = 35.0;
					test_fitness tf( e, result );
					turnament_selection ts;
					test_zero_stop tzs;

					p_ptr p;
					BOOST_CHECK_NO_THROW( p.reset( new population( gt_, tf, turnament_selection(), test_zero_stop(), test_population_settings_ ) ) );

					static const size_t max_cycles = 1000000;
					size_t i = 0;
					bool is_stop = false;
					do
					{
						BOOST_CHECK_NO_THROW( is_stop = p->life_cycle() );
						++i;
					} while ( !is_stop && i < max_cycles );
					BOOST_CHECK_EQUAL( i < max_cycles, true );
					p->generation_.for_each( details::generation_out(), p->generation_.size() );
					std::cout << "Iterations: " << i << std::endl;					
				}
			};
			population_settings population_tests::test_population_settings_ = population_settings();			
			//
			void population_constructor_tests()
			{
				population_tests::initialization();
				population_tests::constructor_tests();
			}			
			void population_renewal_tests()
			{
				population_tests::renewal_tests();
			}
			void population_life_cycle_tests()
			{
				population_tests::life_cycle_tests();
			}
		}
	}
}
