set(cligen_file "${PROJECT_BINARY_DIR}/cligen_file -f ${CMAKE_CURRENT_SOURCE_DIR}/spec.cli 2>&1")

expect_test(EMPTY? "?" ${cligen_file} "cli>.*values.*vb")
expect_test(EMPTY<TAB> "\t  " ${cligen_file} "cli> v  .*Ambiguous command")
expect_test(EMPTY<TAB><TAB> "\t\t" ${cligen_file} "cli> v.*values                    vb")
expect_test(V<TAB>_AMBIGUOUS "v\t  " ${cligen_file} "values                    vb.*Ambiguous command")
expect_test(V<TAB>A<TAB>_INCOMPLETE "v\ta\t" ${cligen_file} "values                    vb.*cli> values.*CLI syntax error in: \"values\": Incomplete command")
expect_test(V<TAB>A<TAB>42_OK "v\ta\t42" ${cligen_file} "cli> values 42.*1 name:values type:string value:values.*2 name:int32 type:int32 value:42")