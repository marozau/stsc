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
			fitness_type fitness;

		public:
			explicit gene_storage( const gene_ptr g, const double f );
			const bool operator <( const gene_storage& gs ) const;
		};
		class generation_functor;
		class generation
		{
		public:
			typedef gene_ptr gene_type;
			typedef double fitness_type;
						
			typedef std::multimap< fitness_type, gene_type > inner_map;
			typedef inner_map::iterator iterator;
			typedef inner_map::const_iterator const_iterator;
			typedef inner_map::key_type key_type;
			typedef inner_map::mapped_type mapped_type;
			typedef inner_map::value_type value_type;
			typedef inner_map::reference reference;
			typedef inner_map::const_reference const_reference;
			typedef inner_map::size_type size_type;

			typedef std::set< size_t > hash_storage;

		private:
			inner_map inner_map_;
			hash_storage hash_storage_;

		public:
			const bool insert( const key_type& key, const mapped_type& value );
			template< class functor >
			void for_each( functor& f, const size_t count, const bool mandatory_change = false );
			template< class functor >
			void for_each( functor& f, const size_t count ) const;
			void swap( generation& g );
			size_type size() const;
		};
		template< class functor >
		void generation::for_each( functor& f, const size_t count, const bool mandatory_change )
		{
			inner_map temp_map;
			bool changed = false;
			size_t counter = 1;
			for( iterator it = inner_map_.begin(); it != inner_map_.end() && counter < count; ++counter )
			{
				do 
				{
					f( it->second );
					changed = hash_storage_.insert( it->second->hash() ).second;
				} while ( !changed && mandatory_change );
				if ( it->first != 0 && changed )
				{
					temp_map.insert( value_type( 0, it->second ) );
					inner_map_.erase( it++ );
				}
				else
					++it;
			}
		}
		template< class functor >
		void generation::for_each( functor& f, const size_t count ) const
		{
			size_t counter = 1;
			for( const_iterator it = inner_map_.begin(); it != inner_map_.end() && counter < count; ++counter )
					f( it->first, it->second );
		}
		//
		class generation_functor
		{
		public:
			virtual void operator () ( const generation::fitness_type&, generation::gene_type& ) = 0;
		};
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_GENERATION_H_
