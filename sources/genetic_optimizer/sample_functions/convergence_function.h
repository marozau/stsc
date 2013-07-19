#ifndef _STSC_GENETIC_OPTIMIZER_SAMPLE_FUNCTIONS_CONVERGENCE_FUNCTION_H
#define _STSC_GENETIC_OPTIMIZER_SAMPLE_FUNCTIONS_CONVERGENCE_FUNCTION_H

#include <deque>

#include <generation.h>

namespace stsc
{
	namespace genetic_optimizer
	{
		namespace sample_functions
		{
			namespace details
			{
				class average_functor: public generation_functor
				{
					generation::fitness_type sum_;
					size_t count_;
					
				public:
					explicit average_functor();
					virtual void operator () ( const gene_storage& );
					const double get_average() const;
				};
				class moving_average
				{
					typedef std::deque< double > storage;
					storage storage_;

					double sum_;
					const size_t period_;
					
				public:
					explicit moving_average( const size_t period );
					//
					void add( const double value );					
					const double get_average() const;
					const bool is_mature() const;
					const size_t get_period() const;
				};
			}
			class convergence_function_prototype
			{
			public:
				virtual const bool calculate( const generation& ) = 0;
			};
			class convergence_function : public convergence_function_prototype
			{
				details::moving_average moving_average_;

				double convergence_coefficient_;
				const double min_convergence_coefficient_;

				size_t counter_;

			public:
				explicit convergence_function( const size_t period, const double min_convergence_coefficient );
				virtual const bool calculate( const generation& );

			private:
				const bool is_converge_() const;
				void add_new_value_( const double value );
			};
		}
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_SAMPLE_FUNCTIONS_CONVERGENCE_FUNCTION_H
