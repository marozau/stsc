#include "gene.h"

#include <algorithm>
#include <ctime>

#include "allele.h"

namespace stsc
{
	namespace genetic_optimizer
	{
		namespace details
		{
			const size_t rand( const size_t max )
			{
				std::srand ( std::time( NULL ) );
				const size_t i = std::rand() % ( max + 1 );
				return i;
			}
		}
		void genotype::add_allele( allele * const a )
		{
			alleles_.push_back( allele_ptr( a ) );
		}
		const gene * const genotype::create_gene() const
		{
			return new gene( *this );
		}
		//
		const double gene::mutation_percent = 4.0;
		gene::gene( const genotype& gt )
		{
			std::copy( gt.alleles_.begin(), gt.alleles_.end(), alleles_.begin() );
		}
		gene::gene( const gene& g )
		{
			std::copy( g.alleles_.begin(), g.alleles_.end(), alleles_.begin() );
		}
		gene* const gene::reproduction( const gene& g )
		{
			const size_t i = details::rand( alleles_.size() );
			gene* const nested_gene = new gene( *this );
			///todo: cteare tempalte crossover function. input two alleles sequences, output - one of them
			std::copy( g.alleles_.begin(), g.alleles_.begin() + i,	nested_gene->alleles_.begin() );
			return nested_gene;
		}
		void gene::mutation()
		{
			const size_t i = details::rand( alleles_.size() );
			alleles_.at( i )->mutation();
		}
		const allele& gene::at( const size_t i )
		{
			return *alleles_.at( i );
		}
	}
}