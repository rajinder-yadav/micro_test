cmake_minimum_required( VERSION 2.6 )
project( check_all_tests )

include_directories( "${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/include" )
set( SOURCE_FILES micro-test.test.cpp )
set( HEADER_FILES  )
add_executable( check_all_tests ${SOURCE_FILES} ${HEADER_FILES} )

# C++11 Support, note to add thread support need to link with pthread
add_definitions( "-std=c++11" )

find_package( Threads )
set( LIB_FILES pthread )
#set( LIB_FILES pthread boost_system boost_thread boost_regex boost_date_time boost_serialization )
target_link_libraries( check_all_tests ${LIB_FILES} ${CMAKE_THREAD_LIBS_INIT} )
