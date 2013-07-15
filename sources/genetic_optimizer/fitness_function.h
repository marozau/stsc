#ifndef _STSC_GENETIC_OPTIMIZER_FITNESS_FUNCTION_H_
#define _STSC_GENETIC_OPTIMIZER_FITNESS_FUNCTION_H_

#include <gene.h>

namespace stsc
{
	namespace genetic_optimizer
	{
		template < class container = std::map< gene_ptr, double > >
		class fitness_function
		{
		public:
			typename typedef container container_type;
			typename typedef container::key_type gene_type;
			typename typedef container::mapped_type fitness_type;

		public:
			virtual void calculate( container_type& ) = 0;
		};
	}
}
#endif // _STSC_GENETIC_OPTIMIZER_FITNESS_FUNCTION_H_
