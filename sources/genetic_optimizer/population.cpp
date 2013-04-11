#include <population.h>

namespace stsc
{
	namespace genetic_optimizer
	{
		const size_t population::min_to_survive = 1;
		population::population( const genome * const genome, 
								const size_t size, 
								const percent_type mutation_percent,
								const percent_type survival_rate )
			: mutation_percent_( mutation_percent )
			, survival_size_( ( size_t )( size * survival_rate ) ? ( size_t )( size * survival_rate ) : min_to_survive )
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
			if ( genes_.size() != fitness.size() )
				throw std::invalid_argument( "fitness size is not equal to genes size" );
						
			reproduction_( fitness );
			mutation_();
		}
		void population::renewal()
		{
			for ( genotype::iterator it = genes_.begin(); it != genes_.end(); ++it )
				( *it )->renewal();
		}
		void population::reproduction_( const fitness& fitness )
		{
			genotype descendant;
			descendant.reserve( genes_.size() );
			while ( descendant.size() < genes_.size() )
			{
				const size_t father_gene = details::rand( genes_.size() - 1 );
				const size_t mother_gene = details::rand( genes_.size() - 1 );
				if ( fitness.at( father_gene ) >= details::rand_percent() && fitness.at( mother_gene ) >= details::rand_percent() )
					descendant.push_back( gene_ptr( genes_.at( mother_gene )->reproduction( *genes_.at( father_gene ) ) ) );
			}
			genes_.swap( descendant );
		}
		void population::mutation_()
		{
			for ( genotype::iterator it = genes_.begin(); it != genes_.end(); ++it )
				if ( mutation_percent_ >= details::rand_percent() )
					( *it )->mutation();
		}
	}
}