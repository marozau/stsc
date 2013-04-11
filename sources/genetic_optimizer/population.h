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
			static const size_t min_to_survive;
			friend class stsc::tests_::genetic_optimizer::population_tests;
		public:
			typedef details::percent_type percent_type;
			typedef percent_type fitness_type;
			typedef std::vector< fitness_type > fitness;
			typedef boost::shared_ptr< gene > gene_ptr;
			typedef std::vector< gene_ptr > generation;
			
		private:
			generation generation_;

			const percent_type mutation_rate_;
			const percent_type reproduction_rate_;
			const size_t survival_size_;

		public:
			explicit population( const genome * const genome, 
								const size_t size, 
								const percent_type reproduction_rate, 
								const percent_type mutation_rate,
								const percent_type survival_rate );
			~population();
			//
			const generation& genes() const;
			void life_cycle( const fitness& fitness );
			void renewal();

		private:
			void reproduction_( const fitness& fitness );
			void mutation_();
		};
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_POPULATION_H_
