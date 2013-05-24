#include <test_registrator.h>

#include <boost/test/unit_test.hpp>

using boost::unit_test_framework::test_suite;
using boost::unit_test_framework::test_case;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
	test_suite* ts1 = BOOST_TEST_SUITE( "genetic_optimizer tests" );
	boost::unit_test::unit_test_log.set_threshold_level( boost::unit_test::log_messages );

	using namespace stsc::tests_::genetic_optimizer::details;
	/*ts1->add( BOOST_TEST_CASE( &gray_code_constructor_tests ) );
	ts1->add( BOOST_TEST_CASE( &gray_code_flip_tests ) );
	ts1->add( BOOST_TEST_CASE( &gray_code_generator_constructor_tests ) );
	ts1->add( BOOST_TEST_CASE( &gray_code_generator_flip_tests ) );
	ts1->add( BOOST_TEST_CASE( &gray_code_generator_reset_tests ) );
	ts1->add( BOOST_TEST_CASE( &rand_tests ) );
	ts1->add( BOOST_TEST_CASE( &rand_percent_tests ) );*/
	//
	using namespace stsc::tests_::genetic_optimizer;
	//ts1->add( BOOST_TEST_CASE( &allele_constructor_tests ) );
	//ts1->add( BOOST_TEST_CASE( &allele_mutation_tests ) );
	//ts1->add( BOOST_TEST_CASE( &allele_reset_tests ) );
	////
	//ts1->add( BOOST_TEST_CASE( &genome_add_allele_tests ) );
	//ts1->add( BOOST_TEST_CASE( &genome_create_gene_tests ) );
	////
	//ts1->add( BOOST_TEST_CASE( &gene_constructor_tests ) );
	//ts1->add( BOOST_TEST_CASE( &gene_reproduction_tests ) );
	//ts1->add( BOOST_TEST_CASE( &gene_mutation_tests ) );
	//ts1->add( BOOST_TEST_CASE( &gene_renewal_tests ) );
	//
	ts1->add( BOOST_TEST_CASE( &population_constructor_tests ) );
	ts1->add( BOOST_TEST_CASE( &population_life_cycle_tests ) );
	ts1->add( BOOST_TEST_CASE( &population_renewal_tests ) );

	return ts1;
}

