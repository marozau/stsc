
find_package( Boost 1.41 ${SEARCH_PARAMETERS} COMPONENTS
	filesystem
	thread
	regex
	date_time
	system
	program_options
	unit_test_framework
)

find_package( system_utilities ${SEARCH_PARAMETERS} COMPONENTS
	logger
	ts_logger
	file_logger
	ts_queue
	queue_logger
	task_processor
	system_processor
	property_reader
	timer
)

add_source_list( ${tests_name} algorithms "algorithms/*.cpp" )
add_source_list( ${tests_name} algorithms "algorithms/*.h" )

compile_project( ${tests_name} "*.cpp" "*.h" BINARY tests ${tests_name} ${module_name} common system_utilities Boost )
register_test( ${tests_name} 1.0 1.0 )

