#include <population.h>

namespace stsc
{
	namespace genetic_optimizer
	{
		const size_t population::min_to_survive = 1;
		population::population( const genome& genome, 
								fitness_function& ff,
								selection_operator& so,
								stop_function& sf,
								const size_t size, 
								const percent_type reproduction_rate,
								const percent_type mutation_rate,
								const percent_type survival_rate )
			: ff_( ff )
			, so_( so )
			, sf_( sf )
			, reproduction_rate_( reproduction_rate )
			, mutation_rate_( mutation_rate )
			, survival_size_( ( size_t )( size * survival_rate / 100 ) ? ( size_t )( size * survival_rate / 100 ) : min_to_survive )
		{
			generation_.reserve( size );
			for ( size_t i = 0; i < size; ++i )
				generation_.push_back( gene_ptr( genome.create_gene() ) );
			fitnesses_ = ff_.calculate( generation_ );
		}
		population::~population()
		{
		}
		//
		const population::generation& population::genes() const
		{
			return generation_;
		}
		const bool population::life_cycle()
		{
			reproduction_();
			mutation_();
			fitnesses_ = ff_.calculate( generation_ );
			const bool is_stop = sf_.calculate( fitnesses_ );
			return is_stop;
		}
		void population::renewal()
		{
			for ( generation::iterator it = generation_.begin(); it != generation_.end(); ++it )
				( *it )->renewal();
		}
		void population::reproduction_()
		{
			generation descendant;
			descendant.reserve( generation_.size() );
			while ( descendant.size() < generation_.size() )
			{
				std::pair< size_t, size_t > parants = get_parants_();
				if ( fitnesses_.at( parants.first ) >= details::rand_percent() && fitnesses_.at( parants.second ) >= details::rand_percent() )
					descendant.push_back( gene_ptr( generation_.at( parants.first )->reproduction( *generation_.at( parants.second ) ) ) );
			}
			generation_.swap( descendant );
		}
		void population::mutation_()
		{
			for ( generation::iterator it = generation_.begin(); it != generation_.end(); ++it )
				if ( mutation_rate_ >= details::rand_percent() )
					( *it )->mutation();
		}
		std::pair< size_t, size_t > population::get_parants_()
		{
			const size_t male = details::rand( generation_.size() - 1 );
			size_t female = 0;
			do 
			{ 
				female = details::rand( generation_.size() - 1 ); 
			} while ( male != female );
			return std::make_pair( male, female );
		}
	}
}