#include <population.h>

namespace stsc
{
	namespace genetic_optimizer
	{
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
				generation_.insert( gene_storage::no_fitness, new_gene );
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
			generation_.for_each_gene( std::mem_fun( &gene::renewal ), generation_.size(), true );
		}
		void population::renewal_()
		{
			generation_.for_each_gene( std::mem_fun( &gene::renewal ), generation_.size() - settings_.survival_size, true );
		}
		void population::reproduction_()
		{
			selection_function_prototype::mating_pool mating_pool = selection_function_.calculate( generation_ ); 
			generation descendant( generation_ );
			size_t iteration = 0;
			size_t global_iteration = 0;
			while ( descendant.size() < generation_.size() )
			{
				selection_function_prototype::parants parants = get_parants( mating_pool );
				gene_ptr new_gene( new gene( *parants.first, *parants.second, details::bit_crossover() ) );
				descendant.insert( gene_storage::no_fitness, new_gene );
				
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
			generation_.for_each_gene( std::bind2nd( std::mem_fun( &gene::mutation ), settings_.mutation_rate ), generation_.size(), false );
		}
	}
}