cmake_minimum_required( VERSION 2.6 )
project( micro_tester )

# Define ASIO project root from environment variable
#set( ASIO_INCLUDE "$ENV{ASIO_ROOT}" )
#include_directories( "${PROJECT_SOURCE_DIR}" "${ASIO_INCLUDE}" )

# ASIO with C++11
#add_definitions( "-DASIO_STANDALONE" )

# Define boost path using environment var
#set( BOOST_INCLUDE "$ENV{BOOST_ROOT}/include/" )
#set( BOOST_LIB "$ENV{BOOST_ROOT}/lib/" )

#include_directories( "${PROJECT_SOURCE_DIR}" "${BOOST_INCLUDE}" )
#link_directories( "${BOOST_LIB}" )

include_directories( "${PROJECT_SOURCE_DIR}" )
set( SOURCE_FILES main.cpp )
set( HEADER_FILES  )
add_executable( micro_tester ${SOURCE_FILES} ${HEADER_FILES} )

# C++11 Support, note to add thread support need to link with pthread
add_definitions( "-std=c++11" )

find_package( Threads )
set( LIB_FILES pthread )
#set( LIB_FILES pthread boost_system boost_thread boost_regex boost_date_time boost_serialization )
target_link_libraries( micro_tester ${LIB_FILES} ${CMAKE_THREAD_LIBS_INIT} )

#add_subdirectory( test )
