#include <population.h>

namespace stsc
{
	namespace genetic_optimizer
	{
		population::population( const genome * const genome, const size_t size, const size_t mutation_percent )
			: size_( size )
			, mutation_percent_( mutation_percent )
		{
			genes_.reserve( size_ );
			for ( size_t i = 0; i < size_; ++i )
				genes_.push_back( gene_ptr( genome->create_gene() ) );
		}
		population::~population()
		{
		}
		//
		const size_t population::size() const
		{
			return size_;
		}
		const population::genotype& population::genes() const
		{
			return genes_;
		}
		void population::life_cycle( const fitness& fitness )
		{
			genotype descendant;
			descendant.reserve( size_ );
			reproduction_( fitness, descendant );
			mutation_( descendant );
			genes_.swap( descendant );
		}
		void population::reproduction_( const fitness& fitness, genotype& descendant )
		{
			static const size_t max_percent = 100;
			while ( descendant.size() < size_ )
			{
				const size_t father_gene = details::rand( size_ );
				const size_t mother_gene = details::rand( size_ );
				if ( fitness.at( father_gene ) >= details::rand( max_percent ) && fitness.at( mother_gene ) >= details::rand( max_percent ) )
					genes_.push_back( gene_ptr( genes_.at( mother_gene )->reproduction( *genes_.at( father_gene ) ) ) );
			}
		}
		void population::mutation_( genotype& descendant )
		{
			static const size_t max_percent = 100;
			for ( genotype::iterator it = descendant.begin(); it != descendant.end(); ++it )
				if ( mutation_percent_ >= details::rand( max_percent ) )
					( *it )->mutation();
		}
	}
}