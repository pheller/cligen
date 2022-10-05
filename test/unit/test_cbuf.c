//
// Created by Phillip Heller on 10/7/22.
//

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <cligen/cligen.h>

static void null_test_success(void **state) {
    (void) state; /* unused */
}

static void test_cbuf_alloc_get_set(void **state) {
    /* test defaults */
    size_t default_start, default_threshold, start, threshold;

    assert_int_equal(cbuf_alloc_get(&default_start, &default_threshold), 0);
    assert_true(default_start == 1024);
    assert_true(default_threshold == 65536);

    assert_int_equal(cbuf_alloc_set(42, 8675309), 0);
    assert_int_equal(cbuf_alloc_get(&start, &threshold), 0);

    assert_true(start == 42);
    assert_true(threshold == 8675309);

    assert_int_equal(cbuf_alloc_set(default_start, default_threshold), 0);
}

static void test_cbuf_create_destroy(void **state) {
    cbuf *cb1, *cb2;

    assert_non_null(cb1 = cbuf_new_alloc(42));
    assert_true(cbuf_buflen(cb1) == 42);
    assert_non_null(cbuf_get(cb1));
    assert_true(cbuf_len(cb1) == 0);

    assert_true(cbuf_append(cb1, 'f') == 0);
    assert_true(strcmp(cbuf_get(cb1), "f") == 0);

    assert_true(cbuf_append_str(cb1, "oo") == 0);
    assert_true(strcmp(cbuf_get(cb1), "foo") == 0);

    assert_non_null(cb2 = cbuf_new());
    // TODO cprintf suggests its return should match printf, but it does not
    assert_true(cprintf(cb2, "bar %d", 123) == 0);

    assert_true(cbuf_append_buf(cb1, cbuf_get(cb2), 99) == 0);
    assert_true(strcmp(cbuf_get(cb1), "foobar 123") == 0);

}

int main(void) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(null_test_success),
            cmocka_unit_test(test_cbuf_alloc_get_set),
            cmocka_unit_test(test_cbuf_create_destroy),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}