#include "test_registrator.h"

#include <gene.h>

using namespace stsc::genetic_optimizer;

namespace stsc
{
	namespace tests_
	{
		namespace genetic_optimization
		{
			typedef boost::shared_ptr< gene > gene_ptr;
			void genotype_add_allele()
			{
				genotype gt;
				allele* a = new allele( 1.0, 2.0, 3.0 );
				gt.add_allele( a );
			}
		}
	}
}
