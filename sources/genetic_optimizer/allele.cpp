#include "allele.h"

namespace stsc
{
	namespace genetic_optimizer
	{
		allele::allele( const value_type min, const value_type max, const value_type step )
			: min_( min )
			, max_( max )
			, step_( step )
			, gcg_( details::calculate_periods_count( min, max, step ) ) 
		{
			calculate_value_();
		}
		allele::allele( const allele& a )
			: min_( a.min_ )
			, max_( a.max_ )
			, step_( a.step_ )
			, gcg_( a.gcg_ )
		{
			calculate_value_();
		}
		const allele::value_type allele::value() const
		{
			return value_;
		}
		void allele::mutation()
		{
			gcg_.flip();
			calculate_value_();
		}
		void allele::reset()
		{
			gcg_.reset();
			calculate_value_();
		}
		void allele::calculate_value_()
		{
			value_ = min_ + step_ * gcg_.value();
		}
		namespace details
		{
			const size_t calculate_periods_count( const allele::value_type min, const allele::value_type max, const allele::value_type step )
			{
				if ( min >= max )
					throw std::invalid_argument( "allele contruction error: max value must be bigger than min value" );
				if ( step <= 0 )
					throw std::invalid_argument( "allele contruction error: step value must be nonzero positive number" );
				return (size_t)( ( max - min ) / step );
			}
		}
	}
}
