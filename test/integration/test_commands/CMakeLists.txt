
set(cligen_file "${PROJECT_BINARY_DIR}/cligen_file -f ${CMAKE_CURRENT_SOURCE_DIR}/spec.cli")
set(cligen_file_preference "${PROJECT_BINARY_DIR}/cligen_file -P 1 -f ${CMAKE_CURRENT_SOURCE_DIR}/spec.cli")
set(cligen_hello "${PROJECT_BINARY_DIR}/cligen_hello")

expect_test(B_UNKNOWN "b" ${cligen_file} "Unknown command")
expect_test(A_OK "a" ${cligen_file} "1 name:a type:string value:a")
expect_test(AB_AMBIGUOUS "ab" ${cligen_file} "Ambiguous command")
expect_test(AB_AMBIGUOUS_PREFERENCE_MODE "ab" ${cligen_file_preference} "Ambiguous command")
expect_test(ABC_OK "abc" ${cligen_file} "1 name:abc type:string value:abc")
expect_test(ABD_INCOMPLETE "abd" ${cligen_file} "CLI syntax error in: \"abd\": Incomplete command")
expect_test(RUN_HELLO "hello world" ${cligen_hello} "hello world")
expect_test(RUN_EXEC "exec foo" ${cligen_file} "foo")