#include "generation.h"

namespace stsc
{
	namespace genetic_optimizer
	{
		gene_storage::gene_storage( const gene_ptr g, const double f )
			: gene( g )
			, fitness( f )
		{
		}
		const bool gene_storage::operator <( const gene_storage& gs ) const
		{
			return gene < gs.gene;
		}
		//
		std::pair< generation::iterator, bool > generation::insert( const value_type& val )
		{
			std::pair< base_map::iterator, bool > res = base_map::insert( val );
			if ( res.second )
				inner_map_.insert( inner_pair( res.first->fitness, res.first->gene ) );
			return res;
		}
		void generation::erase( iterator position )
		{
			std::pair< inner_iterator, inner_iterator > res = inner_map_.equal_range( position->fitness );
			for( inner_iterator it = res.first; it != res.second; ++it )
			{
				if ( it->second == position->gene )
				{
					inner_map_.erase( it );
					break;
				}
			}
			base_map::erase( position );
		}
		generation::size_type generation::erase( const value_type& val )
		{
			iterator it = base_map::find( val );
			if ( it == base_map::end() )
				return size_type( 0 );
			erase( it );
			return size_type( 1 );
		}
		generation::iterator generation::find( const value_type& val ) const
		{
			return base_map::find( val );
		}
		generation::size_type generation::size() const
		{
			return base_map::size();
		}
		void generation::clear()
		{
			base_map::clear();
			inner_map_.clear();
		}
	}
}