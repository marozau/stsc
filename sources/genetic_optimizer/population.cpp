#include <population.h>

namespace stsc
{
	namespace genetic_optimizer
	{
		const size_t population::min_to_survive = 1;
		population::population( const genome& genome, 
								fitness_function& ff,
								selection_function& sel_f,
								stop_function& stop_f,
								const size_t size, 
								const double reproduction_rate,
								const double mutation_rate,
								const double survival_rate,
								const size_t max_reproduction_iteration_count,
								const size_t global_max_reproduction_iteration_count )
			: fitness_function_( ff )
			, selection_function_( sel_f )
			, stop_function_( stop_f )
			, reproduction_rate_( reproduction_rate )
			, mutation_rate_( mutation_rate )
			, survival_size_( ( size_t )( size * survival_rate / 100 ) ? ( size_t )( size * survival_rate / 100 ) : min_to_survive )
			, max_reproduction_iteration_count_( max_reproduction_iteration_count )
			, global_max_reproduction_iteration_count_( global_max_reproduction_iteration_count )
		{
			if ( size <= 1 )
				throw std::invalid_argument( "population construction error: size of population must be greater than 1" );

			while( generation_.size() < size )
			{
				gene_ptr new_gene( genome.create_gene() );				
				if ( hash_storage_.insert( new_gene->hash() ).second ) 
					generation_.insert( std::make_pair( new_gene, 0 ) );
			}
			fitness_function_.calculate( generation_ );
		}
		population::~population()
		{
		}
		//
		const population::generation& population::get() const
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
				it->first->renewal();
				it->second = 0;
			}
		}
		void population::reproduction_()
		{
			selection_function::mating_pool mating_pool = selection_function_.calculate( generation_ ); ///todo: tests what will be faster: = or pass vector as argument reference
			generation descendant;
			size_t iteration = 0;
			size_t global_iteration = 0;
			while ( descendant.size() < generation_.size() )
			{
				parants parants = details::get_parants( mating_pool );
				gene_ptr new_gene( new gene( *parants.first, *parants.second, details::bit_crossover() ) );
				if ( hash_storage_.insert( new_gene->hash() ).second )
					descendant.insert( std::make_pair( new_gene, 0 ) );
				
				++iteration;
				++global_iteration;
				if ( iteration > max_reproduction_iteration_count_ )
				{
					mating_pool = selection_function_.calculate( generation_ );
					iteration = 0;
					if ( global_iteration > global_max_reproduction_iteration_count_ )
					{
						generation::iterator min_it = generation_.begin();
						for( generation::iterator it = generation_.begin(); it != generation_.end(); ++it )
							if ( it->second < min_it->second )
								min_it = it;
						min_it->first->renewal();
						min_it->second = 0;
						return;
					}
				}
			}
			generation_.swap( descendant );
		}
		void population::mutation_()
		{
			for ( generation::iterator it = generation_.begin(); it != generation_.end(); ++it )
				if ( mutation_rate_ >= details::rand_percent() )
					it->first->mutation();
		}
		namespace details
		{
			population::parants get_parants( const population::selection_function::mating_pool& mp )
			{
				const size_t male = details::rand( mp.size() - 1 );
				size_t female = 0;
				do
				{
					female = details::rand( mp.size() - 1 ); 
				} while ( male == female && mp.at( male ) != mp.at( female ) );
				return population::parants( mp.at( male ), mp.at( female ) ) ;
			}
		}
	}
}