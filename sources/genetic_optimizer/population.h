#ifndef _STSC_GENETIC_OPTIMIZER_POPULATION_H_
#define _STSC_GENETIC_OPTIMIZER_POPULATION_H_

#include <vector>

#include <boost/noncopyable.hpp>

#include <gene.h>

namespace stsc
{
	namespace genetic_optimizer
	{
		class population : protected virtual boost::noncopyable
		{
		public:
			typedef float fitness_type;
			typedef std::vector< fitness_type > fitness;
			typedef boost::shared_ptr< gene > gene_ptr;
			typedef std::vector< gene_ptr > genotype;
			
		private:
			const size_t size_;
			genotype genes_;

			const size_t mutation_percent_;

		public:
			explicit population( const genome * const genome, const size_t size, const size_t mutation_percent );
			~population();
			//
			const size_t size() const;
			const genotype& genes() const;
			//
			void life_cycle( const fitness& fitness );
		};
	}
}
#endif // _STSC_GENETIC_OPTIMIZER_POPULATION_H_
