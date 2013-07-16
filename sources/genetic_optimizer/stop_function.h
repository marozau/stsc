#ifndef _STSC_GENETIC_OPTIMIZER_STOP_FUNCTION_H_
#define _STSC_GENETIC_OPTIMIZER_STOP_FUNCTION_H_

#include "gene.h"

namespace stsc
{
	namespace genetic_optimizer
	{
		class stop_function_prototype
		{
		public:
			virtual const bool calculate( const generation& ) const = 0;
		};
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_STOP_FUNCTION_H_
