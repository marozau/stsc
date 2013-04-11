#include "gene.h"

#include "random.h"

namespace stsc
{
	namespace genetic_optimizer
	{
		namespace details
		{
			void base_crossover::operator()( const genome::allele_storage& father_alleles, const genome::allele_storage& mother_alleles, genome::allele_storage& child_alleles )
			{
				const size_t i = details::rand( father_alleles.size() - 2 ) + 1; /// -2 ) + 1 is used to make sure that child allele will have both parant alleles.
				gene::allele_storage temp_alleles;
				child_alleles.insert( child_alleles.end(), father_alleles.begin(), father_alleles.begin() + i );
				child_alleles.insert( child_alleles.end(), mother_alleles.begin() + i, mother_alleles.end() );
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
		void gene::mutation()
		{
			/// todo: maybe it'll be useful to add const size_t alleles_mutant_count parameter to mutate several aleles
			const size_t i = details::rand( alleles_.size() - 1 );
			alleles_.at( i )->mutation();
		}
		void gene::reset()
		{
			for ( allele_storage::iterator it = alleles_.begin(); it != alleles_.end(); ++it )
				( *it )->reset();
		}
		const size_t gene::size() const
		{
			return alleles_.size();
		}
		const allele::value_type gene::at( const size_t i ) const
		{
			return alleles_.at( i )->value();
		}
	}
}
