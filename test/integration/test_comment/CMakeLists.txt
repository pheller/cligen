
set(cligen_file "${PROJECT_BINARY_DIR}/cligen_file -f ${CMAKE_CURRENT_SOURCE_DIR}/spec.cli 2>&1")

expect_test(COMMENT_LINE "# Comment" ${cligen_file} "cli> # Comment")
expect_test(COMMENT_WHITESPACE_LINE "   # Comment" ${cligen_file} "# Comment")
expect_test(COMMENT_AFTER_COMMAND "abc # Comment" ${cligen_file} "cli> abc # Comment.*1 name:abc type:string value:abc")

# TODO need to add a failure regex on this one
expect_test(COMMENT_IN_COMMAND "abc#Comment" ${cligen_file} "cli> abc#Comment.*CLI syntax error in: \"abc#Comment\"")

expect_test(COMMENT_AFTER_COMMAND+STR "abc str # Comment" ${cligen_file} "cli> abc str # Comment.*1 name:abc type:string value:abc.*2 name:s type:rest value:str")
expect_test(COMMENT_IN_STR "abc str#Comment" ${cligen_file} "cli> abc str#Comment.*1 name:abc type:string value:abc.*2 name:s type:rest value:str#Comment")
expect_test(COMMENT_IN_REST "abc str s# Comment" ${cligen_file} "cli> abc str s# Comment.*1 name:abc type:string value:abc.*2 name:s type:rest value:str s# Comment")
