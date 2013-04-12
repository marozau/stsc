#ifndef _STSC_GENETIC_OPTIMIZER_POPULATION_H_
#define _STSC_GENETIC_OPTIMIZER_POPULATION_H_

#include <vector>

#include <boost/noncopyable.hpp>

#include <gene.h>
#include <random.h>
#include <fitness_function.h>
#include <selection_operator.h>
#include <stop_function.h>

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
			static const size_t min_to_survive;

		public:
			typedef details::percent_type percent_type;
			typedef boost::shared_ptr< gene > gene_ptr;
			typedef std::vector< gene_ptr > generation;
			typedef fitness_function< gene_ptr, percent_type > fitness_function;
			typedef selection_operator< gene_ptr > selection_operator;
			typedef stop_function< percent_type > stop_function;
			
		private:
			generation generation_;
			fitness_function::fitness_container fitnesses_;

			const percent_type mutation_rate_;
			const percent_type reproduction_rate_;
			const size_t survival_size_;

			fitness_function& ff_;
			selection_operator& so_;
			stop_function& sf_;

		public:
			explicit population( const genome& genome,
								fitness_function& ff,
								selection_operator& so,
								stop_function& sf,
								const size_t size,
								const percent_type reproduction_rate,
								const percent_type mutation_rate,
								const percent_type survival_rate );
			~population();
			//
			const generation& genes() const;
			const bool life_cycle();
			void renewal();

		private:
			void reproduction_();
			void mutation_();
			std::pair< size_t, size_t > get_parants_();
		};
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_POPULATION_H_
