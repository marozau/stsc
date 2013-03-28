#include "gene.h"

namespace stsc
{
	namespace genetic_optimizer
	{
		namespace details
		{
			void base_crossover::operator()( const genome::allele_storage& father_alleles, const genome::allele_storage& mother_alleles, genome::allele_storage& child_alleles )
			{
				gene::allele_storage temp_alleles;
				const size_t i = details::rand( father_alleles.size() );
				for ( gene::allele_storage::const_iterator it = father_alleles.begin(); it != father_alleles.begin() + i; ++it )
					temp_alleles.push_back( gene::allele_ptr( new allele( *(*it) ) ) );
				for ( gene::allele_storage::const_iterator it = mother_alleles.begin() + i; it != mother_alleles.end(); ++it )
					temp_alleles.push_back( gene::allele_ptr( new allele( *(*it) ) ) );
				child_alleles.swap( temp_alleles );
			}
		}
		//
		gene::gene( const genome& gt )
		{
			alleles_.reserve( gt.alleles_.size() );
			for ( genome::allele_storage::const_iterator it = gt.alleles_.begin();  it != gt.alleles_.end(); ++it )
				alleles_.push_back( gene::allele_ptr( new allele( *( *it ) ) ) );
		}
		gene::gene()
		{
		}
		gene* const gene::reproduction( const gene& g, details::crossover_prototype& func ) const
		{
			if ( alleles_.size() != g.alleles_.size() )
				throw std::logic_error( "gene reproduction error: genes size must be equal" );
			std::auto_ptr< gene > child_gene( new gene() );
			func( alleles_, g.alleles_, child_gene->alleles_ );
			return child_gene.release();
		}
		void gene::mutation( const size_t mutation_probability )
		{
			static const size_t max_percent = 100;
			const size_t p = details::rand( max_percent );
			if ( p <= mutation_probability )
			{
				const size_t i = details::rand( alleles_.size() );
				alleles_.at( i )->mutation();
			}
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
	}
}
