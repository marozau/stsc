#include <hash.h>

namespace stsc
{
	namespace genetic_optimizer
	{
		hash::hash()
			: hash_value_( 0 )
		{
		}
		const size_t hash::get_value() const
		{
			return hash_value_;
		}
		void hash::reset()
		{
			hash_value_ = 0;
		}
	}
}
