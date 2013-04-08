#ifndef _STSC_GENETIC_OPTIMIZER_GENETIC_OPTIMIZER_H_
#define _STSC_GENETIC_OPTIMIZER_GENETIC_OPTIMIZER_H_

#include <boost/noncopyable.hpp>

#include <population.h>

namespace stsc
{
	namespace genetic_optimizer
	{
		class optimizer : protected virtual boost::noncopyable
		{
			
		public:
			explicit optimizer();
			~optimizer();
		};
	}
}
#endif // _STSC_GENETIC_OPTIMIZER_GENETIC_OPTIMIZER_H_
