#include <test_registrator.h>

#include <boost/test/unit_test.hpp>

using boost::unit_test_framework::test_suite;
using boost::unit_test_framework::test_case;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
	test_suite* ts1 = BOOST_TEST_SUITE( "genetic_optimizer tests" );
	boost::unit_test::unit_test_log.set_threshold_level( boost::unit_test::log_messages );


	return ts1;
}

