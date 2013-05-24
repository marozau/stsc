#include <population.h>

namespace stsc
{
	namespace genetic_optimizer
	{
		namespace details
		{
			std::pair< size_t, size_t > get_parants( const generation& g )
			{
				const size_t male = details::rand( g.size() - 1 );
				size_t female = 0;
				do
				{
					female = details::rand( g.size() - 1 ); 
				} while ( male != female );
				return std::make_pair( male, female );
			}
		}
		//
		const size_t population::min_to_survive = 1;
		population::population( const genome& genome, 
								fitness_function& ff,
								selection_function& sel_f,
								stop_function& stop_f,
								const size_t size, 
								const percent_type reproduction_rate,
								const percent_type mutation_rate,
								const percent_type survival_rate )
			: ff_( ff )
			, sel_f_( sel_f )
			, stop_f_( stop_f )
			, reproduction_rate_( reproduction_rate )
			, mutation_rate_( mutation_rate )
			, survival_size_( ( size_t )( size * survival_rate / 100 ) ? ( size_t )( size * survival_rate / 100 ) : min_to_survive )
		{
			if ( size <= 1 )
				throw std::invalid_argument( "population construction error: size of population must be greater than 1" );

			generation_.reserve( size );
			for ( size_t i = 0; i < size; ++i )
				generation_.push_back( gene_ptr( genome.create_gene() ) );
			fitnesses_ = ff_.calculate( generation_ );
		}
		population::~population()
		{
		}
		//
		const generation& population::genes() const
		{
			return generation_;
		}
		const bool population::life_cycle()
		{
			reproduction_();
			mutation_();
			fitnesses_ = ff_.calculate( generation_ );
			const bool is_stop = stop_f_.calculate( fitnesses_ );
			return is_stop;
		}
		void population::renewal()
		{
			for ( generation::iterator it = generation_.begin(); it != generation_.end(); ++it )
				( *it )->renewal();
		}
		void population::reproduction_()
		{
			selection_function::gene_container parants_pool = sel_f_.calculate( generation_, fitnesses_ ); ///todo: tests what will be faster: = or pass vector as argument reference
			generation descendant;
			descendant.reserve( generation_.size() );
			while ( descendant.size() < generation_.size() )
			{
				std::pair< size_t, size_t > parants = details::get_parants( parants_pool );
				if ( reproduction_rate_ >= details::rand_percent() )
					descendant.push_back( gene_ptr( parants_pool.at( parants.first )->reproduction( *parants_pool.at( parants.second ) ) ) );
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