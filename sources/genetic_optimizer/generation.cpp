#include "generation.h"

#include <limits>

namespace stsc
{
	namespace genetic_optimizer
	{
		//static const gene_storage::fitness_type no_fitness = std::numeric_limits< gene_storage::fitness_type >::max();
		const gene_storage::fitness_type gene_storage::no_fitness = 0;
		gene_storage::gene_storage( const double f, const gene_ptr g )
			: gene( g )
			, fitness( f )
		{
		}
		const bool gene_storage::operator <( const gene_storage& gs ) const
		{
			return fitness < gs.fitness;
		}
		//
		generation::generation()
		{
			hash_storage_.reset( new hash_storage() );
		}
		generation::generation( const generation& g )
		{
			hash_storage_ = g.hash_storage_;
		}
		const bool generation::insert( const fitness_type& key, const gene_type& value )
		{
			if ( hash_storage_->insert( value->hash() ).second )
			{
				inner_map_.insert( value_type( key, value ) );
				return true;
			}
			return false;
		}
		void generation::swap( generation& g )
		{
			inner_map_.swap( g.inner_map_ );
			if ( hash_storage_.get() != g.hash_storage_.get() && g.hash_storage_.get() )
				hash_storage_->insert( g.hash_storage_->begin(), g.hash_storage_->end() );
		}
		generation::size_type generation::size() const
		{
			return inner_map_.size();
		}
	}
}