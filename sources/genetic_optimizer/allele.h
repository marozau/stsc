#ifndef _STSC_GENETIC_OPTIMIZER_ALLELE_H_
#define _STSC_GENETIC_OPTIMIZER_ALLELE_H_

#include <boost\noncopyable.hpp>
#include <vector>
#include <bitset>

#include <gray_code.h>

namespace stsc
{
	namespace tests_
	{
		namespace genetic_optimizer
		{
			class allele_tests;
		}
	}
	namespace genetic_optimizer
	{
		class allele : protected virtual boost::noncopyable
		{
			friend class stsc::tests_::genetic_optimizer::allele_tests;

		public:
			typedef double value_type;

		private:
			const value_type min_;
			const value_type max_;
			const value_type step_;
			value_type value_;

			details::gray_code_generator gcg_;
			
		public:
			explicit allele( const value_type min, const value_type max, const value_type step );
			allele( const allele& a );
			//
			const value_type value() const;
			void mutation();
			void reset();

		private:
			void calculate_value_();
		};
		namespace details
		{
			const size_t calculate_periods_count( const allele::value_type min, const allele::value_type max, const allele::value_type step );
		}
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_ALLELE_H_
