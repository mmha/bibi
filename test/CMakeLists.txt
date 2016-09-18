get_target_property(bibi_include_dir bibi::bibi INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(bibi_compile_options bibi::bibi INTERFACE_COMPILE_OPTIONS)

function(bibi_testcase testname expectation file)
	try_compile(result
		"${CMAKE_CURRENT_BINARY_DIR}/${testname}_expect_${expectation}"
		"${CMAKE_CURRENT_SOURCE_DIR}/${file}"
		CMAKE_FLAGS -DINCLUDE_DIRECTORIES=${bibi_include_dir} -DCOMPILE_DEFINITIONS=${bibi_compile_options}
		OUTPUT_VARIABLE output
	)

	if(NOT (${result} STREQUAL ${expectation}))
		message(WARNING "Testcase ${testname} failed with result ${result}! (expected ${expectation})")
		message(WARNING "${output}")
	endif()
endfunction()

bibi_testcase(chrono_success TRUE Chrono/Success.cpp)
bibi_testcase(container_success TRUE Container/Success.cpp)
bibi_testcase(random_success TRUE Random/Success.cpp)
bibi_testcase(thread_success TRUE Thread/Success.cpp)