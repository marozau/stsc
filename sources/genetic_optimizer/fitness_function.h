#ifndef _STSC_GENETIC_OPTIMIZER_FITNESS_FUNCTION_H_
#define _STSC_GENETIC_OPTIMIZER_FITNESS_FUNCTION_H_

namespace stsc
{
	namespace genetic_optimizer
	{
		class generation;
		class fitness_function_prototype
		{
		public:
			virtual void calculate( const generation& ) const = 0;
		};
	}
}
#endif // _STSC_GENETIC_OPTIMIZER_FITNESS_FUNCTION_H_
