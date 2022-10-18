#add_subdirectory(unit)

configure_file(lib.sh lib.sh COPYONLY)

add_test(NAME "test commands" COMMAND "sh" "-c" "${CMAKE_CURRENT_SOURCE_DIR}/test_commands.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME "test comment" COMMAND "sh" "-c" "${CMAKE_CURRENT_SOURCE_DIR}/test_comment.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME "test compile" COMMAND "sh" "-c" "${CMAKE_CURRENT_SOURCE_DIR}/test_compile.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set_tests_properties("test compile" PROPERTIES ENVIRONMENT
    "CC=${CMAKE_C_COMPILER};CFLAGS=-I ${PROJECT_SOURCE_DIR}/include;LDFLAGS=-L${PROJECT_BINARY_DIR} -lcligen;LD_LIBRARY_PATH=${PROJECT_BINARY_DIR}")

add_test(NAME "test completion" COMMAND "sh" "-c" "${CMAKE_CURRENT_SOURCE_DIR}/test_completion.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME "test expand" COMMAND "sh" "-c" "${CMAKE_CURRENT_SOURCE_DIR}/test_expand.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME "test getline" COMMAND "sh" "-c" "${CMAKE_CURRENT_SOURCE_DIR}/test_getline.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME "test helpstrings" COMMAND "sh" "-c" "${CMAKE_CURRENT_SOURCE_DIR}/test_helpstrings.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME "test hide" COMMAND "sh" "-c" "${CMAKE_CURRENT_SOURCE_DIR}/test_hide.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME "test list" COMMAND "sh" "-c" "${CMAKE_CURRENT_SOURCE_DIR}/test_list.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME "test mode" COMMAND "sh" "-c" "${CMAKE_CURRENT_SOURCE_DIR}/test_mode.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME "test preference" COMMAND "sh" "-c" "${CMAKE_CURRENT_SOURCE_DIR}/test_preference.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME "test reftree" COMMAND "sh" "-c" "${CMAKE_CURRENT_SOURCE_DIR}/test_reftree.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME "test rest" COMMAND "sh" "-c" "${CMAKE_CURRENT_SOURCE_DIR}/test_rest.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

configure_file(test_scroll_wide.exp test_scroll_wide.exp COPYONLY)
configure_file(test_scroll_wrap.exp test_scroll_wrap.exp COPYONLY)
add_test(NAME "test scroll" COMMAND "sh" "-c" "${CMAKE_CURRENT_SOURCE_DIR}/test_scroll.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME "test sets" COMMAND "sh" "-c" "${CMAKE_CURRENT_SOURCE_DIR}/test_sets.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

configure_file(../examples/tutorial.cli ../examples/tutorial.cli COPYONLY)
add_test(NAME "test tutorial" COMMAND "sh" "-c" "${CMAKE_CURRENT_SOURCE_DIR}/test_tutorial.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME "test types" COMMAND "sh" "-c" "${CMAKE_CURRENT_SOURCE_DIR}/test_types.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME "test var" COMMAND "sh" "-c" "${CMAKE_CURRENT_SOURCE_DIR}/test_var.sh" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
