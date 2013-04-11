#ifndef _STSC_GENETIC_OPTIMIZER_GRAY_CODE_H_
#define _STSC_GENETIC_OPTIMIZER_GRAY_CODE_H_

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
				typedef std::bitset< bitset_size > bitset;
				bitset code_;
				size_t size_;

			public:
				explicit gray_code( const size_t bin, const size_t max );
				//
				const size_t size() const;
				const size_t decode() const;
				void flip( const size_t pos );
			};
			class gray_code_generator
			{
				const size_t max_;
				gray_code gc_;

			public:
				explicit gray_code_generator( const size_t max );
				gray_code_generator( const gray_code_generator& gcg );
				//
				const size_t value() const;
				void reset();
				void flip();
			};
		}
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_GRAY_CODE_H_
