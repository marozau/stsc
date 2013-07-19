#include "convergence_function.h"

namespace stsc
{
	namespace genetic_optimizer
	{
		namespace sample_functions
		{
			namespace details
			{
				average_functor::average_functor()
					: sum_( generation::fitness_type( 0 ) )
					, count_( 0 )					
				{
				}
				void average_functor::operator () ( const gene_storage& g )
				{
					++count_;
					sum_ += g.fitness;
				}
				const double average_functor::get_average() const
				{
					return count_ ? ( double )sum_ / count_ : 0.0;
				}
				moving_average::moving_average( const size_t period )
					: period_( period )
				{
				}				
				void moving_average::add( const double value )
				{
					storage_.push_back( value );
					sum_ += value;
					if ( is_mature() )
					{
						sum_ -= storage_.front();
						storage_.pop_front();
					}
				}
				const double moving_average::get_average() const
				{
					return storage_.size() ? sum_ / storage_.size() : 0.0;
				}
				const bool moving_average::is_mature() const
				{
					return storage_.size() == period_;
				}
				const size_t moving_average::get_period() const
				{
					return period_;
				}
			}			
			convergence_function::convergence_function( const size_t period, const double min_convergence_coefficient )
				: moving_average_( period )
				, convergence_coefficient_( std::numeric_limits< double >::max() )
				, min_convergence_coefficient_( min_convergence_coefficient )
				, counter_( 0 )
			{
			}
			const bool convergence_function::calculate( const generation& g )
			{
				details::average_functor functor;
				g.for_each( functor, g.size() );
				add_new_value_( functor.get_average() );
				return is_converge_();
			}
			const bool convergence_function::is_converge_() const
			{				
				return counter_ == moving_average_.get_period();
			}
			void convergence_function::add_new_value_( const double value )
			{
				moving_average_.add( value );
				if ( moving_average_.is_mature() )
					convergence_coefficient_ = 	value / moving_average_.get_average();
				if ( convergence_coefficient_ < min_convergence_coefficient_ )
					++counter_;
				else
					counter_ = 0;
			}
		}
	}
}
