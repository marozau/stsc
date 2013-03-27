#include "gene.h"

#include <algorithm>
#include <ctime>

#include "allele.h"

namespace stsc
{
	namespace genetic_optimizer
	{
		void genotype::add_allele( allele * const a )
		{
			alleles_.push_back( allele_ptr( a ) );
		}
		gene * const genotype::create_gene() const
		{
			return new gene( *this );
		}
		//
		gene::gene( const genotype& gt )
		{
			alleles_.reserve( gt.alleles_.size() );
			std::transform( gt.alleles_.begin(), gt.alleles_.end(), alleles_.begin(), details::get_clone );
		}
		gene::gene( const gene& g )
		{
			alleles_.reserve( g.alleles_.size() );
			std::transform( g.alleles_.begin(), g.alleles_.end(), alleles_.begin(), details::get_clone );
		}
		gene* const gene::reproduction( const gene& g ) const
		{
			const size_t i = details::rand( alleles_.size() );
			gene* const nested_gene = new gene( *this );
			///todo: cteare tempalte crossover function. input two alleles sequences, output - new one
			std::copy( g.alleles_.begin(), g.alleles_.begin() + i,	nested_gene->alleles_.begin() );
			return nested_gene;
		}
		void gene::mutation()
		{
			const size_t i = details::rand( alleles_.size() );
			alleles_.at( i )->mutation();
		}
		void gene::reset()
		{
			for ( allele_storage::iterator it = alleles_.begin(); it != alleles_.end(); ++it )
				( *it )->reset();
		}
		const allele& gene::at( const size_t i )
		{
			return *alleles_.at( i );
		}
		namespace details
		{
			const gene::allele_ptr get_clone( const gene::allele_ptr a )
			{
				return gene::allele_ptr( new allele( *a ) );
			}
		}
	}
}
