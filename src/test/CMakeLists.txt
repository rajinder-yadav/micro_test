cmake_minimum_required( VERSION 2.6 )
project( check_all_tests )

include_directories( "${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/include" )
set( SOURCE_FILES micro-test.test.cpp )
set( HEADER_FILES  )
add_executable( check_all_tests ${SOURCE_FILES} ${HEADER_FILES} )

add_definitions( "-std=c++11" )

target_link_libraries( check_all_tests ${LIB_FILES} )
