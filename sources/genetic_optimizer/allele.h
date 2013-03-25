#ifndef _STSC_GENETIC_OPTIMIZER_ALLELE_H_
#define _STSC_GENETIC_OPTIMIZER_ALLELE_H_

#include <boost\noncopyable.hpp>

namespace stsc
{
	namespace genetic_optimizer
	{
		class allele : protected virtual boost::noncopyable
		{
		public:
			allele() {}
			~allele() {}
			//
			void mutation();
		};
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_ALLELE_H_
