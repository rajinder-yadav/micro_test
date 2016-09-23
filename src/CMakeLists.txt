cmake_minimum_required( VERSION 2.6 )
project( micro_tester )

include_directories( "${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/include" )
set( SOURCE_FILES main.cpp )
set( HEADER_FILES  )
add_executable( micro_tester ${SOURCE_FILES} ${HEADER_FILES} )

add_definitions( "-std=c++11" )

target_link_libraries( micro_tester ${LIB_FILES} )

add_subdirectory( test )
