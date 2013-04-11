#include <boost/test/test_tools.hpp>

namespace stsc
{
	namespace tests_
	{
		namespace genetic_optimizer
		{
			namespace details
			{
				void gray_code_constructor_tests();
				void gray_code_flip_tests();
				void gray_code_generator_constructor_tests();
				void gray_code_generator_flip_tests();
				void gray_code_generator_reset_tests();
				void rand_tests();
				void rand_percent_tests();
				//
				void rand_tests();
			}
			void allele_constructor_tests();
			void allele_mutation_tests();
			void allele_reset_tests();
			//
			void genome_add_allele_tests();
			void genome_create_gene_tests();
			//
			void gene_constructor_tests();
			void gene_reproduction_tests();
			void gene_mutation_tests();
			void gene_reset_tests();
			//
			void population_constructor_tests();
		}
	}
}
