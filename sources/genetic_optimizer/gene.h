#ifndef _STSC_GENETIC_OPTIMIZER_GENE_H_ 
#define _STSC_GENETIC_OPTIMIZER_GENE_H_

#include <genome.h>

namespace stsc
{
	namespace tests_
	{
		namespace genetic_optimizer
		{
			class gene_tests;
			class population_tests;
		}
	}
	namespace genetic_optimizer
	{
		namespace details
		{
			struct crossover_prototype 
			{
				virtual void operator()( const genome::allele_storage&, const genome::allele_storage&, genome::allele_storage& ) = 0;
			};
			struct base_crossover : public crossover_prototype
			{
				virtual void operator()( const genome::allele_storage&, const genome::allele_storage&, genome::allele_storage& );
			};
			struct bit_crossover : public crossover_prototype
			{
				virtual void operator()( const genome::allele_storage&, const genome::allele_storage&, genome::allele_storage& );
			};
		}
		//
		class population;
		class gene : boost::noncopyable
		{
			friend class stsc::tests_::genetic_optimizer::gene_tests;
			friend class stsc::tests_::genetic_optimizer::population_tests;
			friend class genome;

		public:			
			typedef genome::allele_ptr allele_ptr;
			typedef genome::allele_storage allele_storage;

		private:
			allele_storage alleles_;

		public:
			explicit gene( const genome& gt );
			explicit gene( const gene& father_gene, const gene& mother_gene, details::crossover_prototype& func );
			//
			void mutation( const double mutation_rate );
			void renewal();
			const size_t hash() const;
			//
			const size_t size() const;
			const allele::value_type at( const size_t i ) const;
		};
		typedef boost::shared_ptr< gene > gene_ptr;
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_GENE_H_
