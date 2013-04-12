#ifndef _STSC_GENETIC_OPTIMIZER_FITNESS_FUNCTION_H_
#define _STSC_GENETIC_OPTIMIZER_FITNESS_FUNCTION_H_

#include <vector>

namespace stsc
{
	namespace genetic_optimizer
	{
		template < class input_type, class result_type >
		class fitness_function
		{
		public:
			typename typedef result_type fitness_type;
			typename typedef std::vector< fitness_type > fitness_container;
			typename typedef input_type gene_type;
			typename typedef std::vector< gene_type > gene_container;
		public:
			virtual fitness_container calculate( const gene_container& ) = 0;
		};
	}
}
#endif // _STSC_GENETIC_OPTIMIZER_FITNESS_FUNCTION_H_
