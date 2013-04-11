#include "test_registrator.h"

#include <gene.h>

using namespace stsc::genetic_optimizer;

namespace stsc
{
	namespace tests_
	{
		namespace genetic_optimizer
		{
			namespace details
			{
				inline void fill_genome( genome& gt )
				{
					gt.add_allele( new allele( 0.0, 300.0, 1.0 ) );
					gt.add_allele( new allele( 0.0, 300.0, 1.0 ) );
					gt.add_allele( new allele( 0.0, 300.0, 1.0 ) );
					gt.add_allele( new allele( 0.0, 300.0, 1.0 ) );
				}
			}
			class gene_tests
			{
				typedef boost::shared_ptr< gene > gene_ptr;

				genome gt_;
			public:
				explicit gene_tests()
				{					
					details::fill_genome( gt_ );
				}

				void constructor_tests()
				{
					gene_ptr g;
					BOOST_CHECK_NO_THROW( g.reset( new gene( gt_ ) ) );
					BOOST_CHECK_EQUAL( g->alleles_.size(), 4 );
					gene_ptr g_copy;
					BOOST_CHECK_NO_THROW( g_copy.reset( new gene( gt_ ) ) );
					for ( size_t it = 0; it != g->alleles_.size(); ++it )
						BOOST_CHECK_EQUAL( g->alleles_.at( it )->value() == g_copy->alleles_.at( it )->value(), true );
				}
				void reproduction_tests()
				{
					gene_ptr g_father;
					BOOST_CHECK_NO_THROW( g_father.reset( new gene( gt_ ) ) );
					gene_ptr g_mother;
					BOOST_CHECK_NO_THROW( g_mother.reset( new gene( gt_ ) ) );
					g_mother->renewal();
					{
						gene_ptr g_child;
						BOOST_CHECK_NO_THROW( g_child.reset( g_father->reproduction( *g_mother ) ) );
						size_t unique = 0;
						for ( gene::allele_storage::iterator it =  g_child->alleles_.begin(); it != g_child->alleles_.end(); ++it )
							if ( ( *it ).unique() )
								++unique;
						BOOST_CHECK_EQUAL( unique < g_child->alleles_.size(), true );

						BOOST_CHECK_NO_THROW( g_child->renewal() );
						unique = 0;
						for ( gene::allele_storage::iterator it =  g_child->alleles_.begin(); it != g_child->alleles_.end(); ++it )
							if ( ( *it ).unique() )
								++unique;
						BOOST_CHECK_EQUAL( unique == g_child->alleles_.size(), true );
					}
					{
						gene_ptr g_child;
						BOOST_CHECK_NO_THROW( g_child.reset( g_father->reproduction( *g_mother ) ) );
						size_t unique = 0;
						for ( gene::allele_storage::iterator it =  g_child->alleles_.begin(); it != g_child->alleles_.end(); ++it )
							if ( ( *it ).unique() )
								++unique;
						BOOST_CHECK_EQUAL( unique < g_child->alleles_.size(), true );

						for ( size_t i = 0; i < 1000; ++i )
							BOOST_CHECK_NO_THROW( g_child->mutation() );
						unique = 0;
						for ( gene::allele_storage::iterator it =  g_child->alleles_.begin(); it != g_child->alleles_.end(); ++it )
							if ( ( *it ).unique() )
								++unique;
						BOOST_CHECK_EQUAL( unique == g_child->alleles_.size(), true );
					}

				}
				void mutation_tests()
				{
					{
						gene_ptr g;
						BOOST_CHECK_NO_THROW( g.reset( new gene( gt_ ) ) );
						gene::allele_storage copy1( g->alleles_ );
						BOOST_CHECK_NO_THROW( g->mutation() );
						size_t diffs_count = 0;
						for ( size_t it = 0; it != g->alleles_.size(); ++it )
							if ( g->alleles_.at( it )->value() != copy1.at( it )->value() )
								++diffs_count;
						BOOST_CHECK_EQUAL( diffs_count, 1 );

						gene::allele_storage copy2( g->alleles_ );
						BOOST_CHECK_NO_THROW( g->mutation() );
						for ( size_t it = 0; it != g->alleles_.size(); ++it )
							if ( g->alleles_.at( it )->value() != copy2.at( it )->value() )
								++diffs_count;
						BOOST_CHECK_EQUAL( diffs_count, 2 );
					}
				}
				void renewal_tests()
				{
					gene_ptr g;
					BOOST_CHECK_NO_THROW( g.reset( new gene( gt_ ) ) );
					gene_ptr g_copy( new gene( gt_ ) );
					BOOST_CHECK_NO_THROW( g->renewal() );
					size_t diffs_count = 0;
					for ( size_t it = 0; it != g->alleles_.size(); ++it )
						if ( g->alleles_.at( it )->value() != g_copy->alleles_.at( it )->value() )
							++diffs_count;
					BOOST_CHECK_EQUAL( diffs_count > g->alleles_.size() / 2, true );
				}
			};
			void gene_constructor_tests()
			{
				gene_tests g_test;
				g_test.constructor_tests();
			}
			void gene_reproduction_tests()
			{
				gene_tests g_test;
				g_test.reproduction_tests();
			}
			void gene_mutation_tests()
			{
				gene_tests g_tests;
				g_tests.mutation_tests();
			}
			void gene_renewal_tests()
			{
				gene_tests g_tests;
				g_tests.renewal_tests();
			}
		}
	}
}
