cmake_minimum_required( VERSION 2.6 )
project( health_check )

include_directories( "${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/include" )
set( SOURCE_FILES micro-test.test.cpp )
set( HEADER_FILES  )
add_executable( health_check ${SOURCE_FILES} ${HEADER_FILES} )

add_definitions( "-std=c++11" )

target_link_libraries( health_check ${LIB_FILES} )
