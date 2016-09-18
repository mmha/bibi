cmake_minimum_required(VERSION 3.6)
project(bibi VERSION "0.1.0")

include(CMakePackageConfigHelpers)

add_subdirectory(include)

option(BIBI_RUN_TESTS "Run the unit test suite" OFF)
if(BIBI_RUN_TESTS)
	add_subdirectory(test)
endif()