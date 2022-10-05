macro(expect_test name input command output)
    add_test(NAME ${name} COMMAND sh -c "echo '${input}' | ${command}")
    set_tests_properties(${name} PROPERTIES PASS_REGULAR_EXPRESSION ${output})
endmacro()

macro(expect_test_nonl name input command output)
    add_test(NAME ${name} COMMAND sh -c "echo -en '${input}' | ${command}")
    set_tests_properties(${name} PROPERTIES PASS_REGULAR_EXPRESSION ${output})
endmacro()

add_subdirectory(unit)
add_subdirectory(integration)
