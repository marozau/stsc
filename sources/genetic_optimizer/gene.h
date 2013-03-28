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
		}
		//
		class gene
		{
			friend class stsc::tests_::genetic_optimizer::gene_tests;

		public:
			friend class genome;
			typedef genome::allele_ptr allele_ptr;
			typedef genome::allele_storage allele_storage;

		private:
			allele_storage alleles_;

		private:
			explicit gene( const genome& gt );
			explicit gene();
			//
			explicit gene( const gene& g ) {}
			gene& operator =( const gene& g ) {}

		public:
			gene* const reproduction( const gene& g, details::crossover_prototype& func = details::base_crossover() ) const;
			void mutation( const size_t mutation_probability );
			void reset();
			const allele& at( const size_t i );
		};
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_GENE_H_
