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
				size_ = last_set_bit + 1;
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
				if ( pos >= size_ )
					throw std::invalid_argument( "gray_code flip error: pos out of range" );
				code_.flip( pos );
			}
			void gray_code::combine( const gray_code& gc, const size_t crossing_point )
			{
				if ( gc.size_ != size_ || crossing_point >= size_ )
					throw std::invalid_argument( "gray_code error: bad combining gray code size or crossing position" );
				for ( size_t i = crossing_point; i < size_; ++i )  
					code_.at( i ) = gc.code_.at( i );
			}
			const gray_code combine( const gray_code& gc1, const gray_code& gc2, const size_t crossing_point )
			{
				gray_code gc( gc1 );
				gc.combine( gc2, crossing_point );
				return gc;
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
			gray_code_generator::gray_code_generator( const gray_code_generator& gcg1, const gray_code_generator& gcg2 )
				: max_( gcg1.max_ )
				, gc_( combine( gcg1.gc_, gcg2.gc_, rand( gcg1.gc_.size() - 2 ) + 1 ) )
			{
				if ( gcg1.max_ != gcg2.max_ )
					throw std::invalid_argument( "gray_code_generator constructor error: gcg1.max != gcg2.max_" );
				if ( gc_.decode() > max_ )
					gc_ = gray_code( rand( max_ ), max_ );
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
