#include "chayai.h"  // first include!

#include <assert.h>

#include "RoaringBitmap-CRoaring/include/roaring/roaring.h"

#define NUMEL 1000*10

BENCHMARK(RoaringBitmap, CRoaring, 100, 10) {
    uint32_t arr1[NUMEL] = {0};
    uint32_t arr2[NUMEL] = {0};

    for(int i = 0; i < NUMEL; i++) {
        arr1[i] = i*2;
        arr2[i] = i*41;
    }

    roaring_bitmap_t *bitmap1 = roaring_bitmap_of_ptr(NUMEL, arr1);
    roaring_bitmap_t *bitmap2 = roaring_bitmap_of_ptr(NUMEL, arr2);

    for(int i = 0; i < 256; i++) {
        roaring_bitmap_t *bitand1 = roaring_bitmap_and(bitmap1, bitmap2);

        uint64_t card1 = roaring_bitmap_get_cardinality(bitand1);
        assert(card1 == 244);

        roaring_bitmap_free(bitand1);

        roaring_bitmap_t *bitxor1 = roaring_bitmap_xor(bitmap1, bitmap2);

        uint64_t card2 = roaring_bitmap_get_cardinality(bitxor1);
        assert(card2 == 19512);

        roaring_bitmap_free(bitxor1);
    }

    roaring_bitmap_free(bitmap2);
    roaring_bitmap_free(bitmap1);
}

int main(int argc, char** argv) {

    REGISTER_BENCHMARK(RoaringBitmap, CRoaring); // Roaring bitmaps in C

    RUN_BENCHMARKS(argc, argv);

    return 0;
}