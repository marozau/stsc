#ifndef _STSC_GENETIC_OPTIMIZER_SELECTION_OPERATOR_H_
#define _STSC_GENETIC_OPTIMIZER_SELECTION_OPERATOR_H_

#include <vector>

namespace stsc
{
	namespace genetic_optimizer
	{
		template< class gene_type >
		class selection_operator
		{
		public:
			typename typedef  std::vector< gene_type > gene_container;
		public:
			virtual void operator () ( const gene_container& initial_sequence, gene_container& result_sequence ) = 0;
		};
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_SELECTION_OPERATOR_H_
