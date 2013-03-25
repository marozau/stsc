#ifndef _STSC_GENETIC_OPTIMIZER_ALLELE_H_
#define _STSC_GENETIC_OPTIMIZER_ALLELE_H_

#include <boost\noncopyable.hpp>
#include <vector>
#include <bitset>

namespace stsc
{
	namespace genetic_optimizer
	{
		namespace details
		{
			class gray_code
			{
				static const size_t bitset_size = 32;
				std::bitset< bitset_size > code_;
				size_t max_bit_;

			public:
				explicit gray_code( const size_t bin );
				//
				size_t decode() const;
				size_t invesrse_bit( const size_t pos );
			};
			unsigned int grayencode( unsigned int g ) 
			{
				return g ^ (g >> 1);
			}
			unsigned int graydecode( unsigned int gray ) 
			{
				unsigned int bin;
				for (bin = 0; gray; gray >>= 1) {
					bin ^= gray;
				}
				return bin;
			}
			unsigned int invesrse_bit( const size_t pos ) 
			{

			}
		}
		class allele : protected virtual boost::noncopyable
		{
			typedef float value_type;

			const value_type min_;
			const value_type max_;
			const value_type step_;
			std::vector< bool > value_;

		public:
			explicit allele( const value_type min, const value_type max, const value_type step );
			~allele();
			//
			void mutation();
		};
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_ALLELE_H_
