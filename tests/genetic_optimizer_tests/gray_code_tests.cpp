#include "test_registrator.h"

#include <iostream>

#include <gray_code.h>

using namespace stsc::genetic_optimizer::details;

namespace stsc
{
	namespace tests_
	{
		namespace genetic_optimizer
		{
			namespace details
			{
				void gray_code_constructor_tests()
				{
					{
						gray_code gc( 10, 31 );
						BOOST_CHECK_EQUAL( gc.decode(), 10 );
						BOOST_CHECK_EQUAL( gc.size(), 4 );
					}
					{
						gray_code gc( 2, 32 );
						BOOST_CHECK_EQUAL( gc.decode(), 2 );
						BOOST_CHECK_EQUAL( gc.size(), 5 );
					}
					{
						gray_code gc( 31, 33 );
						BOOST_CHECK_EQUAL( gc.decode(), 31 );
						BOOST_CHECK_EQUAL( gc.size(), 5 );
					}
					{
						BOOST_CHECK_THROW( gray_code gc( 33, 31 ), std::invalid_argument );
					}
				}
				void gray_code_flip_tests()
				{
					{
						gray_code gc( 10, 31 );
						BOOST_CHECK_NO_THROW( gc.flip( 1 ) );
						BOOST_CHECK_EQUAL( gc.decode(), 9 );
					}
					{
						gray_code gc( 10, 31 );
						BOOST_CHECK_NO_THROW( gc.flip( 0 ) );
						BOOST_CHECK_EQUAL( gc.decode(), 11 );
					}
					{
						gray_code gc( 10, 31 );
						BOOST_CHECK_THROW( gc.flip( 5 ), std::invalid_argument );
					}
				}
				void gray_code_generator_constructor_tests()
				{
					{
						gray_code_generator gcg( 31 );
						BOOST_CHECK_EQUAL( gcg.value() != 32, true );
						std::cout << gcg.value() << std::endl;
					}
					{
						gray_code_generator gcg1( 200 );
						gray_code_generator gcg2( 200 );
						gray_code_generator gcg3( 200 );
						BOOST_CHECK_EQUAL( gcg1.value() != gcg2.value(), true );
						BOOST_CHECK_EQUAL( gcg1.value() != gcg3.value(), true );
						BOOST_CHECK_EQUAL( gcg2.value() != gcg3.value(), true );
					}
					{
						gray_code_generator gcg1( 100 );
						gray_code_generator gcg2( gcg1 );
						gray_code_generator gcg3( gcg1 );
						BOOST_CHECK_EQUAL( gcg1.value() == gcg2.value(), true );
						BOOST_CHECK_EQUAL( gcg1.value() == gcg3.value(), true );
						BOOST_CHECK_EQUAL( gcg2.value() == gcg3.value(), true );
					}
				}
				void gray_code_generator_flip_tests()
				{
					{
						gray_code_generator gcg( 18 );
						for ( size_t i = 0; i < 100000; ++i )
						{
							gcg.flip();
							BOOST_CHECK_EQUAL( gcg.value() <= 18, true );
						}
					}
				}
				void gray_code_generator_reset_tests()
				{
					{
						gray_code_generator gcg( 18 );
						for ( size_t i = 0; i < 100000; ++i )
						{
							gcg.reset();
							BOOST_CHECK_EQUAL( gcg.value() <= 18, true );
						}
					}
				}
				void rand_tests()
				{
					static const size_t iterations = 100;
					static const size_t max_value = 5;
					bool zero = false;
					bool max = false;
					for ( size_t i = 0; i < iterations; ++i )
					{
						const size_t r = rand( max_value );
						if ( r == 0 )
							zero = true;
						if ( r == max_value )
							max = true;
						if ( zero && max )
							break;
					}
					BOOST_CHECK_EQUAL( zero, true );
					BOOST_CHECK_EQUAL( max, true );
				}
			}
		}
	}
}