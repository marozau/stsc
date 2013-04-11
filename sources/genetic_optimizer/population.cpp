#include <population.h>

namespace stsc
{
	namespace genetic_optimizer
	{
		const size_t population::min_to_survive = 1;
		population::population( const genome * const genome, 
								const size_t size, 
								const percent_type reproduction_rate,
								const percent_type mutation_rate,
								const percent_type survival_rate )
			: reproduction_rate_( reproduction_rate )
			, mutation_rate_( mutation_rate )
			, survival_size_( ( size_t )( size * survival_rate / 100 ) ? ( size_t )( size * survival_rate / 100 ) : min_to_survive )
		{
			generation_.reserve( size );
			for ( size_t i = 0; i < size; ++i )
				generation_.push_back( gene_ptr( genome->create_gene() ) );
		}
		population::~population()
		{
		}
		//
		const population::generation& population::genes() const
		{
			return generation_;
		}
		void population::life_cycle( const fitness& fitness )
		{
			if ( generation_.size() != fitness.size() )
				throw std::invalid_argument( "fitness size is not equal to genes size" );
						
			reproduction_( fitness );
			mutation_();
		}
		void population::renewal()
		{
			for ( generation::iterator it = generation_.begin(); it != generation_.end(); ++it )
				( *it )->renewal();
		}
		void population::reproduction_( const fitness& fitness )
		{
			generation descendant;
			descendant.reserve( generation_.size() );
			while ( descendant.size() < generation_.size() )
			{
				const size_t father_gene = details::rand( generation_.size() - 1 );
				size_t mother_gene = 0;
				do 
				{ 
					mother_gene = details::rand( generation_.size() - 1 ); 
				} while ( mother_gene != father_gene );
				if ( fitness.at( father_gene ) >= details::rand_percent() && fitness.at( mother_gene ) >= details::rand_percent() )
					descendant.push_back( gene_ptr( generation_.at( mother_gene )->reproduction( *generation_.at( father_gene ) ) ) );
			}
			generation_.swap( descendant );
		}
		void population::mutation_()
		{
			for ( generation::iterator it = generation_.begin(); it != generation_.end(); ++it )
				if ( mutation_rate_ >= details::rand_percent() )
					( *it )->mutation();
		}
	}
}