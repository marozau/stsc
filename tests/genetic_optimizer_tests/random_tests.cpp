#include "test_registrator.h"

#include <random.h>

#include <set>

using namespace stsc::genetic_optimizer::details;

namespace stsc
{
	namespace tests_
	{
		namespace genetic_optimizer
		{
			namespace details
			{
				void rand_tests()
				{
					{
						size_t same = 0;
						std::set< size_t > values;
						for ( size_t i = 0; i < 1000; ++i )
						{
							const size_t r = rand( 1000 );
							std::pair< std::set< size_t >::iterator, bool> res = values.insert( r );
							if ( !res.second )
								same++;
						}
						BOOST_CHECK_EQUAL( same < 400, true );
					}
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
				void rand_percent_tests()
				{
					{
						const percent_type rand = rand_percent();
						BOOST_CHECK_EQUAL( rand_percent() * 100 - rand > 0, true );
					}
					{
						size_t same = 0;
						std::set< percent_type > values;
						for ( size_t i = 0; i < 1000; ++i )
						{
							const float r = rand_percent();
							std::pair< std::set< percent_type >::iterator, bool> res = values.insert( r );
							if ( !res.second )
								same++;
						}
						BOOST_CHECK_EQUAL( same < 50, true );
					}
				}
			}
		}
	}
}
