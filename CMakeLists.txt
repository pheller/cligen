cmake_minimum_required(VERSION 3.20)

project(cligen
        VERSION 6.0.0
        DESCRIPTION "The CLIGEN command line generation tool"
        HOMEPAGE_URL "http://www.cligen.se"
        LANGUAGES C)

string(TIMESTAMP build_timestamp "%Y.%m.%d %H:%M")
cmake_host_system_information(RESULT _host_name QUERY HOSTNAME)
if("$ENV{USER}" STREQUAL "")
    # USER environment variable isn't set in docker
    set(build_message "${build_timestamp} on ${_host_name}")
else()
    set(build_message "${build_timestamp} by $ENV{USER} on ${_host_name}")
endif()
string(LENGTH ${build_message} build_message_len)

if(UNIX)
    # necessary because Apple compilers apparently don't set __unix__
    # this define will cause that to happen in cligen_getline.c
    add_compile_definitions(unix)
endif()

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
find_package(CMOCKA REQUIRED)

include(CheckSymbolExists)
include(CheckFunctionExists)
include(CheckIncludeFile)

option(CLIGEN_REGFD "Enable BSD select semantics." ON)
option(CLIGEN_SUBMODE "Experimental CLIGEN sub-modes." OFF)
option(WITH_LIBXML2 "use gnome/libxml2 regex engine" ON)
if (WITH_LIBXML2)
    find_package(LibXml2)

    # this doesn't seem to work, even though the symbol does exist
#    file(GLOB_RECURSE LIBXML2_INCLUDES ${LIBXML2_INCLUDE_DIR}/*.h)
#    check_symbol_exists(xmlRegexpCompile ${LIBXML2_INCLUDES} HAVE_XMLREGEXP_H)
endif()

option(CLIGEN_BUILD_EXAMPLES "Build Cligen Examples." ON)
option(CLIGEN_BUILD_TESTS "Build Cligen Tests." ON)

option(BUILD_SHARED_LIBS "Build shared libraries (.so) instead of static ones (.a)" ON)

check_function_exists(strverscmp HAVE_STRVERSCMP)

configure_file(src/build.c.in build.c)                  # contains the build_message constructed above
configure_file(include/cligen/cligen_config.h.in cligen_config.h)  # contains all the compile-time defines for features, libraries, etc.

bison_target(parser
        src/cligen_parse.y
        cligen_parse.tab.c
        COMPILE_FLAGS "-y -l -d -b cligen_parse -p cligen_parse"
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/cligen_parse.tab.h
        )
flex_target(lexer
        src/cligen_parse.l
        ${CMAKE_CURRENT_BINARY_DIR}/cligen_parse.c
        COMPILE_FLAGS "-Pcligen_parse"
        )
add_flex_bison_dependency(lexer parser)

add_library(cligen SHARED
        src/cligen_object.c
        src/cligen_callback.c
        src/cligen_parsetree.c
        src/cligen_pt_head.c
        src/cligen_handle.c
        src/cligen_cv.c
        src/cligen_match.c
        src/cligen_result.c
        src/cligen_read.c
        src/cligen_io.c
        src/cligen_expand.c
        src/cligen_syntax.c
        src/cligen_print.c
        src/cligen_cvec.c
        src/cligen_buf.c
        src/cligen_util.c
        src/cligen_history.c
        src/cligen_regex.c
        src/cligen_getline.c
        build.c
        cligen_config.h
        ${FLEX_lexer_OUTPUTS}
        ${BISON_parser_OUTPUTS}
        )
set_target_properties(cligen PROPERTIES POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS} VERSION ${PROJECT_VERSION})

include_directories(${PROJECT_BINARY_DIR})
target_include_directories(cligen PRIVATE ${PROJECT_SOURCE_DIR}/include/cligen)
target_include_directories(cligen INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/cligen>
        )

install(FILES
        include/cligen/cligen_cv.h
        include/cligen/cligen_cvec.h
        include/cligen/cligen_object.h
        include/cligen/cligen_callback.h
        include/cligen/cligen_handle.h
        include/cligen/cligen_parsetree.h
        include/cligen/cligen_pt_head.h
        include/cligen/cligen_result.h
        include/cligen/cligen_print.h
        include/cligen/cligen_read.h
        include/cligen/cligen_io.h
        include/cligen/cligen_expand.h
        include/cligen/cligen_syntax.h
        include/cligen/cligen_buf.h
        include/cligen/cligen_util.h
        include/cligen/cligen_history.h
        include/cligen/cligen_regex.h
        include/cligen/cligen.h
        DESTINATION include/cligen
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
        COMPONENT devel
        )

install(TARGETS cligen
        DESTINATION lib
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
        EXPORT cligen-targets
        COMPONENT runtime
        )

install(EXPORT cligen-targets
        DESTINATION lib
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
        COMPONENT devel
        )

# Create files so that other CMake projects can find this library with find_package(cligen REQUIRED)
configure_file(${cligen_SOURCE_DIR}/cligen-config.cmake.in ${cligen_BINARY_DIR}/cligen-config.cmake @ONLY)
configure_file(${cligen_SOURCE_DIR}/cligen-config-version.cmake.in ${cligen_BINARY_DIR}/cligen-config-version.cmake @ONLY)

install(FILES
        ${PROJECT_BINARY_DIR}/cligen-config.cmake
        ${PROJECT_BINARY_DIR}/cligen-config-version.cmake
        DESTINATION lib/cligen
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
        COMPONENT devel
        )

if(CLIGEN_BUILD_EXAMPLES)
#    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)     # this presumes the current directory is named "cligen"
                                                            # better would be to reorganize the source directories
    add_executable(cligen_hello examples/cligen_hello.c)
    target_link_libraries(cligen_hello cligen)

    add_executable(cligen_file examples/cligen_file.c)
    target_link_libraries(cligen_file cligen)

    add_executable(cligen_tutorial examples/cligen_tutorial.c)
    target_link_libraries(cligen_tutorial cligen)
endif()

if(CLIGEN_BUILD_TESTS)
    set(MEMORYCHECK_SUPPRESSIONS_FILE ${PROJECT_SOURCE_DIR}/test/valgrind.supp)
    set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --show-leak-kinds=all  --track-fds=yes --trace-children=no --child-silent-after-fork=yes")
    include(CTest)
    add_subdirectory(test)
endif()

set(CPACK_BINARY_STGZ "OFF")
set(CPACK_BINARY_TZ "OFF")
set(CPACK_BINARY_RPM "ON")
set(CPACK_SOURCE_TBZ2 "OFF")
set(CPACK_SOURCE_TXZ "OFF")
set(CPACK_SOURCE_RPM "ON")
set(CPACK_SOURCE_TZ "OFF")
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-${CMAKE_HOST_SYSTEM_NAME}-${CMAKE_HOST_SYSTEM_PROCESSOR}")

set(CPACK_PACKAGE_NAME "cligen")
set(CPACK_PACKAGE_CONTACT "olof@hagsand.se")
set(CPACK_PACKAGE_VENDOR "clicon")
set(CMAKE_PROJECT_HOMEPAGE_URL "http://www.cligen.se")

set(CPACK_RPM_COMPONENT_INSTALL ON)
set(CPACK_RPM_MAIN_COMPONENT "runtime")
set(CPACK_RPM_PACKAGE_LICENSE "ASL 2.0 or GPLv2")
set(CPACK_RPM_PACKAGE_GROUP "System Environment/Libraries")

set(CPACK_RPM_DEV_PACKAGE_SUMMARY "CLIGEN header files")
set(CPACK_RPM_DEV_PACKAGE_GROUP "Development/Libraries")
set(CPACK_RPM_BUILDREQUIRES "flex, bison")

# TODO this doesn't seem to work.
set(CPACK_SOURCE_IGNORE_FILES "/\\\\.DS_Store/;.editorconfig;.git/;.github/;.gitignore;/\\\\.idea/;build/;cmake-build.*/;local-build/")

include(CPack)

cpack_add_component(runtime DISPLAY_NAME "runtime"
        DESCRIPTION "The CLIGEN command line generation tool"
        )
cpack_add_component(devel DISPLAY_NAME "development"
        DESCRIPTION "This package contains header files for CLIGEN."
        DEPENDS runtime
        )