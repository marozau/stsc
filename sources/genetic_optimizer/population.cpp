#include <population.h>

namespace stsc
{
	namespace genetic_optimizer
	{
		population::population( const genome * const genome, const size_t size, const percent_type mutation_percent )
			: mutation_percent_( mutation_percent )
		{
			genes_.reserve( size );
			for ( size_t i = 0; i < size; ++i )
				genes_.push_back( gene_ptr( genome->create_gene() ) );
		}
		population::~population()
		{
		}
		//
		const population::genotype& population::genes() const
		{
			return genes_;
		}
		void population::life_cycle( const fitness& fitness )
		{
			genotype descendant;
			descendant.reserve( genes_.size() );
			reproduction_( fitness, descendant );
			mutation_( descendant );
			genes_.swap( descendant );
		}
		void population::reproduction_( const fitness& fitness, genotype& descendant )
		{
			while ( descendant.size() < genes_.size() )
			{
				const size_t father_gene = details::rand( genes_.size() );
				const size_t mother_gene = details::rand( genes_.size() );
				if ( fitness.at( father_gene ) >= details::rand_percent() && fitness.at( mother_gene ) >= details::rand_percent() )
					descendant.push_back( gene_ptr( genes_.at( mother_gene )->reproduction( *genes_.at( father_gene ) ) ) );
			}
		}
		void population::mutation_( genotype& descendant )
		{
			for ( genotype::iterator it = descendant.begin(); it != descendant.end(); ++it )
				if ( mutation_percent_ >= details::rand_percent() )
					( *it )->mutation();
		}
	}
}