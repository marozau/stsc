#include "genome.h"

#include "gene.h"

namespace stsc
{
	namespace genetic_optimizer
	{
		void genome::add_allele( allele * const a )
		{
			alleles_.push_back( allele_ptr( a ) );
		}
		gene * const genome::create_gene() const
		{
			return new gene( *this );
		}
	}
}
