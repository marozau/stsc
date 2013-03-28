#ifndef _STSC_GENETIC_OPTIMIZER_GENOME_H_
#define _STSC_GENETIC_OPTIMIZER_GENOME_H_

#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <allele.h>

namespace stsc
{
	namespace genetic_optimizer
	{
		class gene;
		class allele;
		class genome : protected virtual boost::noncopyable
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
	}
}

#endif // _STSC_GENETIC_OPTIMIZER_GENOME_H_
