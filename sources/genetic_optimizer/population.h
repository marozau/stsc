#ifndef _STSC_GENETIC_OPTIMIZER_POPULATION_H_
#define _STSC_GENETIC_OPTIMIZER_POPULATION_H_

#include <vector>
#include <set>

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
		namespace details
		{
			std::pair< size_t, size_t > get_parants( const generation& g );
		}
		//
		class population : protected virtual boost::noncopyable
		{
			friend class stsc::tests_::genetic_optimizer::population_tests;
			static const size_t min_to_survive;

		public:
			typedef details::percent_type percent_type;
			typedef fitness_function< gene_ptr, percent_type > fitness_function;
			typedef selection_function< gene_ptr, percent_type > selection_function;
			typedef stop_function< percent_type > stop_function;
			typedef std::set< size_t > hash_storage;
			
		private:
			generation generation_;
			fitness_function::fitness_container fitnesses_;

			const percent_type mutation_rate_;
			const percent_type reproduction_rate_;
			const size_t survival_size_;

			fitness_function& ff_;
			selection_function& sel_f_;
			stop_function& stop_f_;

			hash_storage hash_storage_;

		public:
			explicit population( const genome& genome,
								fitness_function& ff,
								selection_function& sel_f,
								stop_function& stop_f,
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
		};
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_POPULATION_H_
