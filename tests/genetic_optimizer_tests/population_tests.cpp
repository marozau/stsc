#include "test_registrator.h"

#include <population.h>

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
					genome gt_;
					fill_genome( gt_, 0.0, 100.0 );
					fill_genome( gt_, 0.0, 200.0 );
					fill_genome( gt_, 0.0, 300.0 );

					p_ptr p;
					BOOST_CHECK_NO_THROW( p.reset( new population( gt_, 5, 1.0, 1.0, 100.0 ) ) );
					BOOST_CHECK_EQUAL( p->generation_.size(), 5 );
					BOOST_CHECK_EQUAL( p->mutation_rate_, 1.0 );
					BOOST_CHECK_EQUAL( p->reproduction_rate_, 1.0 );
					BOOST_CHECK_EQUAL( p->survival_size_, 5 );
					for ( size_t i = 0; i < p->generation_.size(); ++i )
						BOOST_CHECK_EQUAL( p->generation_.at( i ), p->genes().at( i ) );

					BOOST_CHECK_NO_THROW( p.reset( new population( gt_, 5, 1.0, 1.0, 1.0 ) ) );
					BOOST_CHECK_EQUAL( p->survival_size_, 1 );
				}
				static void life_cycle_tests()
				{
					{
						genome gt_;
						fill_genome( gt_, 0.0, 100.0 );
						fill_genome( gt_, 0.0, 200.0 );
						fill_genome( gt_, 0.0, 300.0 );

						p_ptr p;
						BOOST_CHECK_NO_THROW( p.reset( new population( gt_, 5, 1.0, 1.0, 10.0 ) ) );
						population::generation copy( p->generation_ );

						population::fitness f;
						f.push_back( 30.0 );
						f.push_back( 20.0 );
						f.push_back( 70.0 );
						f.push_back( 10.0 );
						BOOST_CHECK_THROW( p->life_cycle( f ), std::invalid_argument );
						f.push_back( 10.0 );
						BOOST_CHECK_NO_THROW( p->life_cycle( f ) );

						size_t diffs = 0;
						for ( size_t i = 0; i < p->generation_.size(); ++i )
							if ( p->generation_.at( i ) != copy.at( i ) )
								++diffs;
						BOOST_CHECK_EQUAL( diffs > 0, true );
					}
					{
						genome gt_;
						fill_genome( gt_, 0.0, 100.0 );
						fill_genome( gt_, 0.0, 200.0 );
						fill_genome( gt_, 0.0, 300.0 );

						p_ptr p;
						BOOST_CHECK_NO_THROW( p.reset( new population( gt_, 5, 10.0, 1.0, 1.0 ) ) );

						population::fitness f;
						f.push_back( 30.0 );
						f.push_back( 20.0 );
						f.push_back( 70.0 );
						f.push_back( 10.0 );
						f.push_back( 10.0 );
						for ( size_t i = 0; i < 1000; ++i )
							BOOST_CHECK_NO_THROW( p->life_cycle( f ) );
					}
				}
				static void renewal_tests()
				{
					genome gt_;
					fill_genome( gt_, 0.0, 100.0 );
					fill_genome( gt_, 0.0, 200.0 );
					fill_genome( gt_, 0.0, 300.0 );

					p_ptr p;
					BOOST_CHECK_NO_THROW( p.reset( new population( gt_, 5, 1.0, 1.0, 1.0 ) ) );
					population::generation copy( p->generation_ );

					BOOST_CHECK_NO_THROW( p->renewal() );
					size_t diffs = 0;
					for ( size_t i = 0; i < p->generation_.size(); ++i )
						if ( p->generation_.at( i ) != copy.at( i ) )
							++diffs;
					BOOST_CHECK_EQUAL( diffs > 0, true );

				}
			};
			void population_constructor_tests()
			{
				population_tests::constructor_tests();
			}
			void population_life_cycle_tests()
			{
				population_tests::life_cycle_tests();
			}
		}
	}
}
