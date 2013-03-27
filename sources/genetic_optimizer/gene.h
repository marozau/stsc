#ifndef _STSC_GENETIC_OPTIMIZER_GENE_H_ 
#define _STSC_GENETIC_OPTIMIZER_GENE_H_

#include <boost\noncopyable.hpp>
#include <boost\shared_ptr.hpp>
#include <vector>

namespace stsc
{
	namespace genetic_optimizer
	{
		class gene;
		class allele;
		class genotype : protected virtual boost::noncopyable
		{
		public:
			friend class gene;		
			typedef boost::shared_ptr< allele > allele_ptr;
			typedef std::vector< allele_ptr > allele_storage;

		private:
			allele_storage alleles_;

		public:
			void add_allele( allele * const a );
			gene * const create_gene() const;
		};
		class gene : protected virtual boost::noncopyable
		{
		public:
			friend class genotype;
			typedef genotype::allele_ptr allele_ptr;
			typedef genotype::allele_storage allele_storage;

		private:
			allele_storage alleles_;

		private:
			gene( const gene& g );
			explicit gene( const genotype& gt );

		public:
			gene * const reproduction( const gene& g ) const;
			void mutation();
			void reset();
			const allele& at( const size_t i );
		};
		namespace details
		{
			const gene::allele_ptr get_clone( const gene::allele_ptr a );
		}
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_GENE_H_
