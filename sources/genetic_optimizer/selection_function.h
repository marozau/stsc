#ifndef _STSC_GENETIC_OPTIMIZER_SELECTION_OPERATOR_H_
#define _STSC_GENETIC_OPTIMIZER_SELECTION_OPERATOR_H_

#include <vector>

namespace stsc
{
	namespace genetic_optimizer
	{
		template< class gene_type, class fitness_type >
		class selection_function
		{
		public:
			typename typedef std::vector< gene_type > gene_container;
			typename typedef std::vector< fitness_type > fitness_container;
		public:
			virtual gene_container calculate( const gene_container&, const fitness_container& ) = 0;
		};
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_SELECTION_OPERATOR_H_
