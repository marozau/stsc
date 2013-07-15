#ifndef _STSC_GENETIC_OPTIMIZER_POPULATION_H_
#define _STSC_GENETIC_OPTIMIZER_POPULATION_H_

#include <vector>
#include <set>
#include <map>

#include <boost/noncopyable.hpp>

#include <gene.h>
#include <random.h>
#include <fitness_function.h>
#include <selection_function.h>
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
			typedef std::pair< gene_ptr, gene_ptr > parants;
			typedef std::pair< gene_ptr, double > gene_pair;
			typedef std::map< gene_ptr, double > generation;
			typedef fitness_function< generation > fitness_function;
			typedef selection_function< generation > selection_function;
			typedef stop_function< generation > stop_function;
			typedef std::set< size_t > hash_storage;
			
		private:
			generation generation_;

			const double mutation_rate_;
			const double reproduction_rate_;
			const size_t survival_size_;

			fitness_function& fitness_function_;
			selection_function& selection_function_;
			stop_function& stop_function_;

			hash_storage hash_storage_;

			const size_t max_reproduction_iteration_count_;
			const size_t global_max_reproduction_iteration_count_;

		public:
			explicit population( const genome& genome,
								fitness_function& ff,
								selection_function& sel_f,
								stop_function& stop_f,
								const size_t size,
								const double reproduction_rate,
								const double mutation_rate,
								const double survival_rate,
								const size_t max_reproduction_iteration_count,
								const size_t global_max_reproduction_iteration_count );
			~population();
			//
			const generation& get() const;
			const bool life_cycle();
			void renewal();

		private:
			void reproduction_();
			void mutation_();
		};
		namespace details
		{
			population::parants get_parants( const population::selection_function::mating_pool& mp );
		}
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_POPULATION_H_
