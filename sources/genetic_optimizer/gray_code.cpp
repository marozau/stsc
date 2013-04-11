#include "gray_code.h"

#include "random.h"

namespace stsc
{
	namespace genetic_optimizer
	{
		namespace details			
		{
			gray_code::gray_code( const size_t dec, const size_t max )
				: code_( bitset( dec ^ ( dec >> 1 ) ) )
			{
				if ( dec > max )
					throw std::invalid_argument( "gray_code construction error: dec value must be lower than max value" );
				size_t last_set_bit = 0;
				bitset max_bin( max );
				for ( size_t i = 0; i < bitset_size; ++i )
				{
					if ( max_bin.test( i ) )
						last_set_bit = i;
				}
				size_ = last_set_bit;
			}
			const size_t gray_code::size() const
			{
				return size_;
			}
			const size_t gray_code::decode() const
			{
				size_t bin = 0;
				size_t gray = code_.to_ullong();
				for ( ; gray; gray >>= 1 ) 
					bin ^= gray;
				return bin;
			}
			void gray_code::flip( const size_t pos )
			{
				if ( pos > size_ )
					throw std::invalid_argument( "gray_code flip error: pos out of range" );
				code_.flip( pos );
			}
			//
			gray_code_generator::gray_code_generator( const size_t max )
				: max_( max )
				, gc_( rand( max_ ), max_ )
			{
			}
			gray_code_generator::gray_code_generator( const gray_code_generator& gcg )
				: max_( gcg.max_ )
				, gc_( gcg.value(), max_ )
			{
			}
			const size_t gray_code_generator::value() const
			{
				return gc_.decode();
			}
			void gray_code_generator::reset()
			{
				gc_ = gray_code( rand( max_ ), max_ );
			}
			void gray_code_generator::flip()
			{
				for (;;)
				{
					const size_t i = details::rand( gc_.size() - 1 );
					gc_.flip( i );
					if ( gc_.decode() > max_ )
						gc_.flip( i );
					else 
						break;
				} 
			}
		}
	}
}
