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
		class gene;
		//
		typedef boost::shared_ptr< gene > gene_ptr;
		typedef std::vector< gene_ptr > generation;
		//
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
			class equal_gene : public std::binary_function< gene, gene, bool >
			{
			public:
				const result_type operator() ( const first_argument_type& f, const second_argument_type& s );
			};
			class equal_gene_ptr : public std::binary_function< gene_ptr, gene_ptr, bool >
			{
			public:
				const result_type operator() ( const first_argument_type& f, const second_argument_type& s );
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

		private:
			explicit gene( const genome& gt );
			explicit gene(); /// using in reproduction, but may be rewriten 

		public:
			gene* const reproduction( const gene& g, details::crossover_prototype& func = details::base_crossover() ) const;
			void mutation();
			void renewal();
			const size_t hash() const;
			
		public:
			const size_t size() const;
			const allele::value_type at( const size_t i ) const;
		};
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_GENE_H_
