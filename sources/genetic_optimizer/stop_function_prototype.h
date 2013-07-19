#ifndef _STSC_GENETIC_OPTIMIZER_STOP_FUNCTION_PROTOTYPE_H_
#define _STSC_GENETIC_OPTIMIZER_STOP_FUNCTION_PROTOTYPE_H_

namespace stsc
{
	namespace genetic_optimizer
	{
		class generation;
		class stop_function_prototype
		{
		public:
			virtual const bool calculate( const generation& ) const = 0;
		};
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_STOP_FUNCTION_PROTOTYPE_H_
