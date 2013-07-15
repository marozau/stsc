#ifndef _STSC_GENETIC_OPTIMIZER_STOP_FUNCTION_H_
#define _STSC_GENETIC_OPTIMIZER_STOP_FUNCTION_H_

#include <vector>

namespace stsc
{
	namespace genetic_optimizer
	{
		template < class container = std::map< gene_ptr, double > >
		class stop_function
		{
		public:
			typename typedef container::key_type gene_type;
			typename typedef container::mapped_type fitness_type;

		public:
			virtual const bool calculate( const container& ) = 0;
		};
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_STOP_FUNCTION_H_
