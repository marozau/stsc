#ifndef _STSC_GENETIC_OPTIMIZER_POPULATION_H_
#define _STSC_GENETIC_OPTIMIZER_POPULATION_H_

#include <vector>

#include <boost/noncopyable.hpp>

#include <gene.h>
#include <random.h>

namespace stsc
{
	namespace tests_
	{
		namespace genetic_optimizer
		{
			class population_tests;
		}
	}
	namespace genetic_optimizer
	{
		class population : protected virtual boost::noncopyable
		{
			friend class stsc::tests_::genetic_optimizer::population_tests;
		public:
			typedef details::percent_type percent_type;
			typedef float fitness_type;
			typedef std::vector< fitness_type > fitness;
			typedef boost::shared_ptr< gene > gene_ptr;
			typedef std::vector< gene_ptr > genotype;
			
		private:
			genotype genes_;

			const percent_type mutation_percent_;

		public:
			explicit population( const genome * const genome, const size_t size, const percent_type mutation_percent );
			~population();
			//
			const genotype& genes() const;
			//
			void life_cycle( const fitness& fitness );

		private:
			void reproduction_( const fitness& fitness, genotype& descendant );
			void mutation_( genotype& descendant );
		};
	}
}
#endif // _STSC_GENETIC_OPTIMIZER_POPULATION_H_
