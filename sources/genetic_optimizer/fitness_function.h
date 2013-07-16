#ifndef _STSC_GENETIC_OPTIMIZER_FITNESS_FUNCTION_H_
#define _STSC_GENETIC_OPTIMIZER_FITNESS_FUNCTION_H_

#include "gene.h"

namespace stsc
{
	namespace genetic_optimizer
	{
		class fitness_function
		{
		public:
			virtual void calculate( generation& ) = 0;
		};
	}
}
#endif // _STSC_GENETIC_OPTIMIZER_FITNESS_FUNCTION_H_
