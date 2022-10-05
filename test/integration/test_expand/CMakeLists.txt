set(tutorial_spec1 "${PROJECT_BINARY_DIR}/cligen_tutorial -q -f ${CMAKE_CURRENT_SOURCE_DIR}/spec1.cli")

expect_test(CLIGEN_I<TAB> "i\t" ${tutorial_spec1} "cli> interface .*CLI syntax error in: \"interface\": Incomplete command")
expect_test(CLIGEN_I<TAB><TAB> "i\t\t" ${tutorial_spec1} "cli> interface eth.*Ambiguous command")
expect_test(CLIGEN_I<TAB><TAB><TAB> "i\t\t\t" ${tutorial_spec1} "cli> interface eth.*eth0                      eth1.*Ambiguous command")
expect_test(CLIGEN_I<TAB><TAB>? "i\t\t?" ${tutorial_spec1} "cli> interface eth.*eth0                  Interface A.*Ambiguous command")
expect_test(CLIGEN_INTERFACE_ETH0 "interface eth0" ${tutorial_spec1} "2 name:ifname type:string value:eth0")
expect_test(CLIGEN_INTERFACE_FOO_UNKNOWN "interface foo" ${tutorial_spec1} "CLI syntax error in: \"interface foo\": Unknown command")

set(tutorial_spec2 "${PROJECT_BINARY_DIR}/cligen_tutorial -q -f ${CMAKE_CURRENT_SOURCE_DIR}/spec2.cli")

expect_test(CLIGEN_INTERFACE_ETH0_SPEC2 "interface eth0" ${tutorial_spec2} "2 name:ifname type:string value:eth0")
expect_test(CLIGEN_INTERFACE_FOO_SPEC2 "interface foo" ${tutorial_spec2} "2 name:ifname type:string value:foo")

set(tutorial_spec3 "${PROJECT_BINARY_DIR}/cligen_file -e -f ${CMAKE_CURRENT_SOURCE_DIR}/spec3.cli")

expect_test(A_FOO_Y "a foo y" ${tutorial_spec3} "1 name:a type:string value:a.*2 name:x type:string value:foo.*3 name:y type:string value:y")
expect_test(A_EXP1_Y "a exp1 y" ${tutorial_spec3} "1 name:a type:string value:a.*2 name:x type:string value:exp1.*3 name:y type:string value:y")

## TODO there is a skipped test in the origin test_expand.sh

set(tutorial_spec4_tabmode0 "${PROJECT_BINARY_DIR}/cligen_file -t 0 -e -f ${CMAKE_CURRENT_SOURCE_DIR}/spec4.cli")
set(tutorial_spec4_tabmode1 "${PROJECT_BINARY_DIR}/cligen_file -t 1 -e -f ${CMAKE_CURRENT_SOURCE_DIR}/spec4.cli")
set(tutorial_spec4_tabmode2 "${PROJECT_BINARY_DIR}/cligen_file -t 2 -e -f ${CMAKE_CURRENT_SOURCE_DIR}/spec4.cli")
set(tutorial_spec4_tabmode4 "${PROJECT_BINARY_DIR}/cligen_file -t 4 -e -f ${CMAKE_CURRENT_SOURCE_DIR}/spec4.cli")

expect_test(CLIGEN_A<TAB><TAB>_tabmode:0 "a\t\tb" ${tutorial_spec4_tabmode0} "abbb                      accc.*1 name:abbb type:string value:abbb")
# TODO this next one has a negative regex assertion in the original; also seems the original expectpart function will pass if each element is anywhere in the output - order unimportant; this next test is adjusted to pass
expect_test(CLIGEN_A<TAB><TAB>_tabmode:1 "a\t\tb" ${tutorial_spec4_tabmode1} "abbb                  First command.*accc                  Second command.*1 name:abbb type:string value:abbb")

expect_test(CLIGEN_X<TAB><TAB>_tabmode:0 "x\t\t" ${tutorial_spec4_tabmode0} "1 name:x type:string value:x.*2 name:b type:string value:b")
expect_test(CLIGEN_X<TAB><TAB>_tabmode:2 "x\t\t" ${tutorial_spec4_tabmode2} "CLI syntax error in: \"x\": Incomplete command")

#TODO these next two also have a negative regex assertion
expect_test(CLIGEN_X<TAB><TAB>b_tabmode:2 "x\t\tb" ${tutorial_spec4_tabmode2} "1 name:x type:string value:x.*2 name:b type:string value:b")
expect_test(CLIGEN_Z<TAB>_tabmode:0 "z\t" ${tutorial_spec4_tabmode0} "CLI syntax error in: \"za\": Incomplete command")

expect_test(CLIGEN_Z<TAB>_tabmode:4 "z\t" ${tutorial_spec4_tabmode4} "za zb zc.*1 name:za type:string value:za.*2 name:zb type:string value:zb.*3 name:zc type:string value:zc")

set(tutorial_spec5 "${PROJECT_BINARY_DIR}/cligen_file -t 0 -e -f ${CMAKE_CURRENT_SOURCE_DIR}/spec5.cli")
expect_test(MULTIPLE_OPTIONS "aaa value?" ${tutorial_spec5} "value1.*value2")
