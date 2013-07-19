#ifndef _STSC_GENETIC_OPTIMIZER_SAMPLE_FUNCTIONS_TOURNAMENT_SELECTION_H_
#define _STSC_GENETIC_OPTIMIZER_SAMPLE_FUNCTIONS_TOURNAMENT_SELECTION_H_

#include "selection_function_prototype.h"

namespace stsc
{
	namespace genetic_optimizer
	{
		struct gene_storage;
		class generation;
		namespace sample_functions
		{
			namespace details
			{
				class turnament_selection_helper : public generation_functor
				{					
					std::vector< generation::value_type > genes;

				public:
					explicit turnament_selection_helper( const size_t size );					
					virtual void operator () ( const gene_storage& g );					
					selection_function_prototype::mating_pool generate( const size_t size );
				};
			}
			class turnament_selection : public stsc::genetic_optimizer::selection_function_prototype
			{
				typedef stsc::genetic_optimizer::generation container_type;

			public:
				virtual mating_pool calculate( const stsc::genetic_optimizer::generation& g ) const;			
			};
		}
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_SAMPLE_FUNCTIONS_TOURNAMENT_SELECTION_H_
