cmake_minimum_required( VERSION 2.6 )
project( micro_tester )

include_directories( "${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/include" )
set( SOURCE_FILES main.cpp )
set( HEADER_FILES  )
add_executable( micro_tester ${SOURCE_FILES} ${HEADER_FILES} )

# C++11 Support, note to add thread support need to link with pthread
add_definitions( "-std=c++11" )

find_package( Threads )
set( LIB_FILES pthread )
#set( LIB_FILES pthread boost_system boost_thread boost_regex boost_date_time boost_serialization )
target_link_libraries( micro_tester ${LIB_FILES} ${CMAKE_THREAD_LIBS_INIT} )

add_subdirectory( test )
