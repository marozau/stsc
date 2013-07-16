#ifndef _STSC_GENETIC_OPTIMIZER_SELECTION_OPERATOR_H_
#define _STSC_GENETIC_OPTIMIZER_SELECTION_OPERATOR_H_

#include <vector>

#include "gene.h"

namespace stsc
{
	namespace genetic_optimizer
	{
		class selection_function
		{
		public:
			typedef std::vector< gene_ptr > mating_pool;
		public:
			virtual mating_pool calculate( const generation& ) = 0;
		};
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_SELECTION_OPERATOR_H_
