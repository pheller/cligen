add_executable(test_cbuf test_cbuf.c)
target_link_libraries(test_cbuf cligen ${CMOCKA_LIBRARIES})
target_include_directories(test_cbuf PUBLIC ${CMOCKA_INCLUDE_DIR})
add_test(test_cbuf test_cbuf)
