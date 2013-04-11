#include "random.h"

#include <ctime>

namespace stsc
{
	namespace genetic_optimizer
	{
		namespace details
		{
			const size_t rand( const size_t max )
			{
				///todo: maybe it'll be more useful to use singleton rand
				static bool is_seeded = false;
				if ( !is_seeded )
				{
					srand( ( unsigned int )std::time( NULL ) );
					is_seeded = true;
				}
				const size_t i = ::rand() % ( max + 1 );
				return i;
			}

			const percent_type rand_percent()
			{
				static const size_t max_percent = 100;
				static const size_t max_fractional = 99;
				const size_t ceil_part = rand( max_percent );
				const size_t fractional_part = rand( max_fractional );
				const percent_type rand_percent = ( percent_type )ceil_part + ( percent_type )fractional_part / 100;
				return rand_percent;
			}
		}
	}
}