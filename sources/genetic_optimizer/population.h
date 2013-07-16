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
			typedef std::set< size_t > hash_storage;
			
		private:
			population_settings settings_;

			generation generation_;
						
			const fitness_function_prototype& fitness_function_;
			const selection_function_prototype& selection_function_;
			const stop_function_prototype& stop_function_;

			hash_storage hash_storage_;

		public:
			explicit population( const genome& genome,
								fitness_function_prototype& ff,
								selection_function_prototype& sel_f,
								stop_function_prototype& stop_f,
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
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_POPULATION_H_
