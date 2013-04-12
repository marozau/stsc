#ifndef _STSC_GENETIC_OPTIMIZER_STOP_FUNCTION_H_
#define _STSC_GENETIC_OPTIMIZER_STOP_FUNCTION_H_

#include <vector>

namespace stsc
{
	namespace genetic_optimizer
	{
		template< class T >
		class stop_function
		{
		public:
			typename typedef T fitness_type;
			typename typedef std::vector< fitness_type > fitness_container;
		public:
			virtual const bool calculate( const fitness_container& ) = 0;
		};
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_STOP_FUNCTION_H_
