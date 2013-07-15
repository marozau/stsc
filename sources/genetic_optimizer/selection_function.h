#ifndef _STSC_GENETIC_OPTIMIZER_SELECTION_OPERATOR_H_
#define _STSC_GENETIC_OPTIMIZER_SELECTION_OPERATOR_H_

#include <vector>

namespace stsc
{
	namespace genetic_optimizer
	{
		template < class container = std::map< gene_ptr, double > >
		class selection_function
		{
		public:
			typename typedef container container_type;
			typename typedef container::key_type gene_type;
			typename typedef container::mapped_type fitness_type;

			typename typedef std::vector< gene_type > mating_pool;

		public:
			virtual mating_pool calculate( const container_type& ) = 0;
		};
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_SELECTION_OPERATOR_H_
