#ifndef _STSC_GENETIC_OPTIMIZER_SELECTION_OPERATOR_H_
#define _STSC_GENETIC_OPTIMIZER_SELECTION_OPERATOR_H_

#include <vector>

#include "generation.h"

namespace stsc
{
	namespace genetic_optimizer
	{
		class selection_function_prototype
		{
		public:
			typedef std::pair< gene_ptr, gene_ptr > parants;
			typedef std::vector< gene_ptr > mating_pool;

		public:
			virtual mating_pool calculate( const generation& ) const = 0;
		};
		inline selection_function_prototype::parants get_parants( const selection_function_prototype::mating_pool& mp )
		{
			const size_t male = details::rand( mp.size() - 1 );
			size_t female = 0;
			do
			{
				female = details::rand( mp.size() - 1 ); 
			} while ( male == female && mp.at( male ) != mp.at( female ) );
			return selection_function_prototype::parants( mp.at( male ), mp.at( female ) ) ;
		}
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_SELECTION_OPERATOR_H_
