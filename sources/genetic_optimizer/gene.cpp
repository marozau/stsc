#include "gene.h"

#include "random.h"
#include "hash.h"

namespace stsc
{
	namespace genetic_optimizer
	{
		namespace details
		{
			void base_crossover::operator()( const genome::allele_storage& father_alleles, const genome::allele_storage& mother_alleles, genome::allele_storage& child_alleles )
			{
				child_alleles.reserve( father_alleles.size() );
				const size_t i = details::rand( father_alleles.size() - 2 ) + 1; /// '-2 ) + 1' is used to make sure that child allele will have both parant alleles.
				child_alleles.insert( child_alleles.end(), father_alleles.begin(), father_alleles.begin() + i );
				child_alleles.insert( child_alleles.end(), mother_alleles.begin() + i, mother_alleles.end() );
			}
			void bit_crossover::operator()( const genome::allele_storage& father_alleles, const genome::allele_storage& mother_alleles, genome::allele_storage& child_alleles )
			{
				for( size_t i = 0; i != father_alleles.size(); ++i )
					child_alleles.push_back( gene::allele_ptr( new allele( *father_alleles.at( i ), *mother_alleles.at( i ) ) ) );
			}
		}
		//
		gene::gene( const genome& gt )
		{
			alleles_.reserve( gt.alleles_.size() );
			for ( genome::allele_storage::const_iterator it = gt.alleles_.begin();  it != gt.alleles_.end(); ++it )
			{
				gene::allele_ptr new_allele( new allele( *( *it ) ) );
				new_allele->reset();
				alleles_.push_back( gene::allele_ptr( new_allele ) );
			}
		}
		gene::gene( const gene& father_gene, const gene& mother_gene, details::crossover_prototype& func )
		{
			if ( father_gene.alleles_.size() != mother_gene.alleles_.size() )
				throw std::logic_error( "gene reproduction error: genes must be equal in size" );
			func( father_gene.alleles_, mother_gene.alleles_, alleles_ );
		}
		//
		void gene::mutation( const double mutation_rate )
		{
			for( allele_storage::iterator it = alleles_.begin(); it != alleles_.end(); ++it )
			{
				if ( !( *it ).unique() )
					( *it ).reset( new allele( *( *it ) ) );
				( *it )->mutation( mutation_rate );
			}
		}
		void gene::renewal()
		{
			for ( allele_storage::iterator it = alleles_.begin(); it != alleles_.end(); ++it )
			{
				if ( !( *it ).unique() )
					( *it ).reset( new allele( *( *it ) ) );
				( *it )->reset();
			}
		}
		const size_t gene::hash() const
		{
			stsc::genetic_optimizer::hash h;
			for ( allele_storage::const_iterator it = alleles_.begin(); it != alleles_.end(); ++it )
				h.calculate( ( *it )->value() );
			return h.get_value();
		}
		const size_t gene::size() const
		{
			return alleles_.size();
		}
		const allele::value_type gene::at( const size_t i ) const
		{
			return alleles_.at( i )->value();
		}
		//
		gene_storage::gene_storage( const gene_ptr g, const double f )
			: gene( g )
			, fitness( f )
		{
		}
		const bool gene_storage::operator <( const gene_storage& gs ) const
		{
			return gene < gs.gene;
		}
	}
}
