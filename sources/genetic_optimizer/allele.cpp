#include "allele.h"

namespace stsc
{
	namespace genetic_optimizer
	{
		namespace details			
		{
			gray_code::gray_code( const size_t bin )
				: code_( std::bitset< bitset_size >( bin ^ ( bin >> 1 ) ) )
			{
				size_t last_set_bit = 0;
				for ( size_t i = 0; i < bitset_size; ++i )
					if ( code_.test( i ) )
						last_set_bit = i;
				max_bit_ = last_set_bit;
			}
			size_t gray_code::decode() const
			{
			}
			size_t gray_code::invesrse_bit( const size_t pos )
			{
			}
		}
		allele::allele( const value_type min, const value_type max, const value_type step )
			: min_( min )
			, max_( max )
			, step_( step )
		{
		}
		allele::~allele()
		{
		}
		void allele::mutation()
		{
		}
	}
}
