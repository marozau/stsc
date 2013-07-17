#ifndef _STSC_GENETIC_OPTIMIZER_GENERATION_H_
#define _STSC_GENETIC_OPTIMIZER_GENERATION_H_

#include <set>
#include <map>

#include "gene.h"

namespace stsc
{
	namespace genetic_optimizer
	{
		struct gene_storage
		{
			typedef gene_ptr gene_type;
			const gene_type gene;
			typedef double fitness_type;
			mutable fitness_type fitness;

		public:
			explicit gene_storage( const gene_ptr g, const double f );
			const bool operator <( const gene_storage& gs ) const;
		};
		class generation : public std::set< gene_storage >
		{
		public:
			typedef std::set< gene_storage > base_map;
			typedef std::pair< gene_storage::fitness_type, gene_storage::gene_type > inner_pair;
			typedef std::multimap< gene_storage::fitness_type, gene_storage::gene_type > inner_map;
			typedef inner_map::const_iterator inner_iterator;

			typedef base_map::key_type key_type;
			typedef base_map::value_type value_type;
			typedef base_map::reference reference;
			typedef base_map::const_reference const_reference;
			typedef base_map::pointer pointer;
			typedef base_map::const_pointer const_pointer;
			typedef base_map::iterator iterator;
			typedef base_map::const_iterator const_iterator;
			typedef base_map::size_type size_type;

		private:
			inner_map inner_map_;

		public:
			std::pair< iterator, bool > insert( const value_type& val );
			//
			void erase( iterator position );
			size_type erase( const value_type& val );
			//
			iterator find( const value_type& val ) const;
			//
			size_type size() const;
			//
			void clear();
			//
			template< class functor >
			void for_each( functor& f )
			{
				for( inner_iterator it = inner_map_.begin(); it != inner_map_.end(); ++it )
					f( base_map::find( it->second ) );
			}
			template< class functor >
			void for_each( functor& f, const size_t count )
			{
				size_t counter = 1;
				for( inner_iterator it = inner_map_.begin(); it != inner_map_.end() && counter < count; ++it, ++counter )
					f( base_map::find( it->second ) );
			}
		};
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_GENERATION_H_
