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
		struct population_settings
		{
			size_t population_size;
			double mutation_rate;
			double reproduction_rate;
			size_t survival_size;

			size_t max_reproduction_iteration_count;
			size_t global_max_reproduction_iteration_count;
		};
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
			population_settings settings_;

			generation generation_;
						
			fitness_function& fitness_function_;
			selection_function& selection_function_;
			stop_function& stop_function_;

			hash_storage hash_storage_;

		public:
			explicit population( const genome& genome,
								fitness_function& ff,
								selection_function& sel_f,
								stop_function& stop_f,
								const population_settings& pop_settings );
			~population();
			//
			const generation& get() const;
			const bool life_cycle();
			void renewal();


		private:
			void renewal_();
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
