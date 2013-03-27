#include "test_registrator.h"

#include <allele.h>

using namespace stsc::genetic_optimizer;

namespace stsc
{
	namespace tests_
	{
		namespace genetic_optimizer
		{
			class allele_tests
			{
				typedef boost::shared_ptr< allele > allele_ptr;
			public:
				static void constructor_tests()
				{
					{
						allele_ptr a;
						BOOST_CHECK_NO_THROW( a.reset( new allele( 10.0, 20.0, 1.0 ) ) );
						BOOST_CHECK_EQUAL( a->min_, 10.0 );
						BOOST_CHECK_EQUAL( a->max_, 20.0 );
						BOOST_CHECK_EQUAL( a->step_, 1.0 );
						BOOST_CHECK_EQUAL( a->value_, a->value() );
					}
					{
						allele_ptr a;
						BOOST_CHECK_THROW( a.reset( new allele( 10.0, 9.0, 1.0 ) ), std::invalid_argument );
						BOOST_CHECK_THROW( a.reset( new allele( 10.0, 9.0, -0.00001 ) ), std::invalid_argument );
					}
					{
						allele_ptr a;
						allele_ptr a_copy;
						BOOST_CHECK_NO_THROW( a.reset( new allele( 10.0, 100.0, 1.0 ) ) );
						BOOST_CHECK_NO_THROW( a_copy.reset( new allele( *a ) ) );
						BOOST_CHECK_EQUAL( a_copy->min_, 10.0 );
						BOOST_CHECK_EQUAL( a_copy->max_, 100.0 );
						BOOST_CHECK_EQUAL( a_copy->step_, 1.0 );
						BOOST_CHECK_EQUAL( a_copy->value_, a_copy->value() );
						BOOST_CHECK_EQUAL( a_copy->value_ != a->value(), true );
					}
				}
				static void mutation_tests()
				{
					{
						allele_ptr a;
						BOOST_CHECK_NO_THROW( a.reset( new allele( 10.0, 20.0, 1.0 ) ) );
						for ( size_t i = 0; i < 100000; ++i )
						{
							a->mutation();
							BOOST_CHECK_EQUAL( a->value() <= 20.0, true );
							BOOST_CHECK_EQUAL( a->value() >= 10.0, true );
						}
					}
				}
				static void reset_tests()
				{
					{
						allele_ptr a;
						BOOST_CHECK_NO_THROW( a.reset( new allele( 10.0, 200.0, 1.0 ) ) );
						for ( size_t i = 0; i < 100000; ++i )
						{
							a->reset();
							BOOST_CHECK_EQUAL( a->value() <= 200.0, true );
							BOOST_CHECK_EQUAL( a->value() >= 10.0, true );
						}
					}
				}
			};
			void allele_constructor_tests()
			{
				allele_tests::constructor_tests();
			}
			void allele_mutation_tests()
			{
				allele_tests::mutation_tests();
			}
			void allele_reset_tests()
			{
				allele_tests::reset_tests();
			}
		}
	}
}
