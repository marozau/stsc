#ifndef _STSC_GENETIC_OPTIMIZER_RANDOM_H_
#define _STSC_GENETIC_OPTIMIZER_RANDOM_H_

#include <stdlib.h>

namespace stsc
{
	namespace genetic_optimizer
	{
		namespace details
		{
			typedef float percent_type;
			const size_t rand( const size_t max );
			const percent_type rand_percent();
		}
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_RANDOM_H_
