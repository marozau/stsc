#ifndef _STSC_GENETIC_OPTIMIZER_HASH_H_
#define _STSC_GENETIC_OPTIMIZER_HASH_H_

#include <boost/functional/hash.hpp>

namespace stsc
{
	namespace genetic_optimizer
	{
		class hash
		{
			size_t hash_value_;

		public:
			explicit hash();
			//
			const size_t get_value() const;
			void reset();
			template< class T >
			void calculate( const T& t )
			{
				hash_value_ += boost::hash_value( t );
			}
		};
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_HASH_H_