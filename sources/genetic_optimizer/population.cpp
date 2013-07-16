#include <population.h>

namespace stsc
{
	namespace genetic_optimizer
	{
		const size_t population::min_to_survive = 1;
		population::population( const genome& genome, 
								fitness_function_prototype& ff,
								selection_function_prototype& sel_f,
								stop_function_prototype& stop_f,
								const population_settings& pop_settings )
			: fitness_function_( ff )
			, selection_function_( sel_f )
			, stop_function_( stop_f )
			, settings_( pop_settings )
		{
			if ( settings_.population_size <= 1 )
				throw std::invalid_argument( "population construction error: size of population must be greater than 1" );
			if ( settings_.survival_size >= settings_.population_size )
				throw std::invalid_argument( "population construction error: survival size must be lower than population size" );
			while( generation_.size() < settings_.population_size )
			{
				gene_ptr new_gene( genome.create_gene() );				
				if ( hash_storage_.insert( new_gene->hash() ).second ) 
					generation_.insert( gene_storage( new_gene, 0 ) );
			}
			fitness_function_.calculate( generation_ );
		}
		population::~population()
		{
		}
		//
		const generation& population::get() const
		{
			return generation_;
		}
		const bool population::life_cycle()
		{
			reproduction_();
			mutation_();
			fitness_function_.calculate( generation_ );
			const bool is_stop = stop_function_.calculate( generation_ );
			return is_stop;
		}
		void population::renewal()
		{
			for ( generation::iterator it = generation_.begin(); it != generation_.end(); ++it )
			{
				do
				{
					it->gene->renewal();
				} while( !hash_storage_.insert( it->gene->hash() ).second );
				it->fitness = 0;
			}
		}
		void population::renewal_()
		{
			typedef std::map< double, gene_ptr > fitness_to_gene_map;
			fitness_to_gene_map fitness_to_gene_map_;
			for ( generation::const_iterator it = generation_.begin(); it != generation_.end(); ++it )
				fitness_to_gene_map_.insert( std::make_pair( it->fitness, it->gene ) );
			size_t survived = generation_.size();
			for( fitness_to_gene_map::iterator it = fitness_to_gene_map_.begin(); 
				it != fitness_to_gene_map_.end() && ( survived > settings_.survival_size ); ++it )
			{
				const generation::value_type& g = ( *generation_.find( gene_storage( it->second, it->first ) ) );
				do
				{
					g.gene->renewal();
				} while( !hash_storage_.insert( g.gene->hash() ).second );
				g.fitness = 0;
				--survived;
			}
		}
		void population::reproduction_()
		{
			selection_function_prototype::mating_pool mating_pool = selection_function_.calculate( generation_ ); ///todo: tests what will be faster: = or pass vector as argument reference
			generation descendant;
			size_t iteration = 0;
			size_t global_iteration = 0;
			while ( descendant.size() < generation_.size() )
			{
				selection_function_prototype::parants parants = get_parants( mating_pool );
				gene_ptr new_gene( new gene( *parants.first, *parants.second, details::bit_crossover() ) );
				if ( hash_storage_.insert( new_gene->hash() ).second )
					descendant.insert( gene_storage( new_gene, 0 ) );
				
				++iteration;
				++global_iteration;
				if ( iteration > settings_.max_reproduction_iteration_count )
				{
					mating_pool = selection_function_.calculate( generation_ );
					iteration = 0;
					if ( global_iteration > settings_.global_max_reproduction_iteration_count )
					{
						renewal_();
						return;
					}
				}
			}
			generation_.swap( descendant );
		}
		void population::mutation_()
		{
			for ( generation::iterator it = generation_.begin(); it != generation_.end(); )
			{
				it->gene->mutation( settings_.mutation_rate );
				if ( hash_storage_.insert( it->gene->hash() ).second )
					++it;
			}
		}
	}
}