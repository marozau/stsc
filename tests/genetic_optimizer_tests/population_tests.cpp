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
					BOOST_CHECK_NO_THROW( p.reset( new population( &gt_, 5, 1.0 ) ) );
					BOOST_CHECK_EQUAL( p->genes_.size(), 5 );
					BOOST_CHECK_EQUAL( p->mutation_percent_, 1.0 );
				}
			};
			void population_constructor_tests()
			{
				population_tests::constructor_tests();
			}
		}
	}
}
