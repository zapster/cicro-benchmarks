#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "harness.h"

#include <stdbool.h>
#include <stdint.h>

#include "camgunz-cmp/cmp.h"

#define LOREM_IPSUM "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet."
#define LOREM_IPSUM10 LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM LOREM_IPSUM
#define LOREM_IPSUM100 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10 LOREM_IPSUM10
#define LOREM_IPSUM1000 LOREM_IPSUM100 LOREM_IPSUM100 LOREM_IPSUM100 LOREM_IPSUM100 LOREM_IPSUM100 LOREM_IPSUM100 LOREM_IPSUM100 LOREM_IPSUM100 LOREM_IPSUM100 LOREM_IPSUM100

static bool file_reader(cmp_ctx_t *ctx, void *data, size_t limit) {
    return true;
}

static bool file_skipper(cmp_ctx_t *ctx, size_t count) {
    return true;
}

static size_t file_writer(cmp_ctx_t *ctx, const void *data, size_t count) {
    return count;
}

int __attribute__ ((noinline)) test_harness(void) {

    cmp_ctx_t cmp;
    cmp_init(&cmp, NULL, file_reader, file_skipper, file_writer);

    for (int i = 0; i < 10000000; i++) { // TODO: very tight loop
        cmp_write_double(&cmp, 1.234567);
        cmp_write_str(&cmp, LOREM_IPSUM1000, sizeof(LOREM_IPSUM1000));
    }
    return 0;
}

int main(int argc, char* argv[]) {
    _test_harness harness = {
        .name="camgunz-cmp",
        .description="An implementation of the MessagePack serialization format in C",
        .test_harness=*test_harness,
        .expected_runtime=500L
    };
    return _execute_harness(argc, argv, harness);
}