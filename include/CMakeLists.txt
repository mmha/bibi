add_library(bibi INTERFACE)
add_library(bibi::bibi ALIAS bibi)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_compile_options(bibi INTERFACE -fconcepts) 
endif()

set_property(TARGET bibi PROPERTY INTERFACE_bibi_MAJOR_VERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET bibi PROPERTY INTERFACE_bibi_MINOR_VERSION ${PROJECT_VERSION_MINOR})

target_include_directories(bibi INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS bibi EXPORT bibiTargets
        INCLUDES DESTINATION include
)
install(DIRECTORY bibi
        DESTINATION include
        COMPONENT devel
)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/bibi/bibiConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

export(EXPORT bibiTargets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/bibi/bibiTargets.cmake"
       NAMESPACE bibi::
)
configure_file(bibiConfig.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/bibi/bibiConfig.cmake"
        COPYONLY
)

set(ConfigPackageLocation lib/cmake/bibi)
install(EXPORT bibiTargets
        FILE bibiTargets.cmake
        NAMESPACE bibi::
        DESTINATION ${ConfigPackageLocation}
)
install(FILES bibiConfig.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/bibi/bibiConfigVersion.cmake"
        DESTINATION ${ConfigPackageLocation}
        COMPONENT devel
)