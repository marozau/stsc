#include "test_registrator.h"

#include <population.h>
#include "functions.h"

using namespace stsc::genetic_optimizer;

namespace stsc
{
	namespace tests_
	{
		namespace genetic_optimizer
		{
			class population_tests
			{
				typedef boost::shared_ptr< population > p_ptr;
								
				static void fill_genome( genome& gt, const allele::value_type min, const allele::value_type max )
				{
					gt.add_allele( new allele( min, max, 1.0 ) );
				}

			public:
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
					BOOST_CHECK_NO_THROW( p.reset( new population( gt_, tf, ts, tzs, 5, 1.0, 1.0, 100.0, 10, 30 ) ) );
					BOOST_CHECK_EQUAL( p->generation_.size(), 5 );
					BOOST_CHECK_EQUAL( p->mutation_rate_, 1.0 );
					BOOST_CHECK_EQUAL( p->reproduction_rate_, 1.0 );
					BOOST_CHECK_EQUAL( p->survival_size_, 5 );
					for ( size_t i = 0; i < p->generation_.size(); ++i )
						BOOST_CHECK_EQUAL( p->generation_.at( i ), p->genes().at( i ) );

					BOOST_CHECK_NO_THROW( p.reset( new population( gt_, tf, ts, tzs, 5, 1.0, 1.0, 1.0, 10, 30 ) ) );
					BOOST_CHECK_EQUAL( p->survival_size_, 1 );
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
					BOOST_CHECK_NO_THROW( p.reset( new population( gt_, tf, ts, tzs, 5, 1.0, 1.0, 1.0, 10, 30 ) ) );
					gene::allele_storage copy( p->generation_.front()->alleles_ );

					BOOST_CHECK_NO_THROW( p->renewal() );
					size_t diffs = 0;
					bool res = true;
					for ( size_t i = 0; i < p->generation_.front()->alleles_.size(); ++i )
						if ( p->generation_.front()->alleles_.at( i )->value() != copy.at( i )->value() )
								res = false;
					BOOST_CHECK_EQUAL( res, false );
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
					BOOST_CHECK_NO_THROW( p.reset( new population( gt_, tf, ts, tzs, 5, 30.0, 2.0, 1.0, 10, 30 ) ) );

					static const size_t max_cycles = 1000000;
					size_t i = 0;
					bool is_stop = false;
					do 
					{						
						is_stop = p->life_cycle();
						++i;
					} while ( !is_stop && i < max_cycles );
					BOOST_CHECK_EQUAL( i < max_cycles, true );
				}
			};
			void population_constructor_tests()
			{
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
