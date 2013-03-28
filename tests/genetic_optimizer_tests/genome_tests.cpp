#include "test_registrator.h"

#include <genome.h>
#include <gene.h>

using namespace stsc::genetic_optimizer;

namespace stsc
{
	namespace tests_
	{
		namespace genetic_optimizer
		{
			namespace details
			{
				inline void fill_genome( genome& gt )
				{
					gt.add_allele( new allele( 0.0, 300.0, 1.0 ) );
					gt.add_allele( new allele( 0.0, 300.0, 1.0 ) );
					gt.add_allele( new allele( 0.0, 300.0, 1.0 ) );
					gt.add_allele( new allele( 0.0, 300.0, 1.0 ) );
				}
			}
			typedef boost::shared_ptr< gene > gene_ptr;
			void genome_add_allele_tests()
			{
				genome gt;
				BOOST_CHECK_NO_THROW( details::fill_genome( gt ) );
			}
			void genome_create_gene_tests()
			{
				genome gt;
				BOOST_CHECK_NO_THROW( details::fill_genome( gt ) );
				gene_ptr g;
				BOOST_CHECK_NO_THROW( g.reset( gt.create_gene() ) );
			}
		}
	}
}
