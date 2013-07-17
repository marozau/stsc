#include "generation.h"

namespace stsc
{
	namespace genetic_optimizer
	{
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
		const bool generation::insert( const fitness_type& key, const gene_type& value )
		{
			if ( hash_storage_.insert( value->hash() ).second )
			{
				iterator it = inner_map_.insert( value_type( key, value ) );
				return true;
			}
			return false;
		}
		void generation::swap( generation& g )
		{
			inner_map_.swap( g.inner_map_ );
			hash_storage_.insert( g.hash_storage_.begin(), g.hash_storage_.end() );
		}
		generation::size_type generation::size() const
		{
			return inner_map_.size();
		}
	}
}