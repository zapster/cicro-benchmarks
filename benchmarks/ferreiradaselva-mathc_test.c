#include "chayai.h"  // first include!

#include <assert.h>

#include "ferreiradaselva-mathc/mathc.h"

BENCHMARK(ferreiradaselva, mathc, 100, 10) {

    /* Pass by value and return a value */
    struct mat mat1 = matrix_identity(), mat2 = matrix_zero();

    // change the same matrix over and over with some operations
    for(int i=0; i < 10000; i++) { // TODO: pretty tight loop
        pmatrix_inverse(&mat1, &mat1);
        pmatrix_rotation_x(0.1, &mat1);
        pmatrix_multiply_matrix(&mat1, &mat1, &mat2);
        pmatrix_multiply_matrix(&mat2, &mat2, &mat1);
        pmatrix_rotation_x(-0.1, &mat1);
        pmatrix_multiply(&mat1, 3, &mat1);

        struct vec quat1 = quaternion_rotation_matrix(mat1);
        pquaternion_inverse(&quat1, &quat1);

        pmatrix_rotation_quaternion(&quat1, &mat1);
    }

    pmatrix_multiply(&mat1, 1000, &mat1);

    assert((int)mat1.m11 == 1000 && (int)mat1.m21 == 0 && (int)mat1.m31 == 0 && (int)mat1.m41 == 0);
    assert((int)mat1.m12 == 0 && (int)mat1.m22 == 997 && (int)mat1.m32 == -47 && (int)mat1.m42 == 0);
    assert((int)mat1.m13 == 0 && (int)mat1.m23 == 47 && (int)mat1.m33 == 997 && (int)mat1.m43 == 0);
    assert((int)mat1.m14 == 0 && (int)mat1.m24 == 0 && (int)mat1.m34 == 0 && (int)mat1.m44 == 1000);
}

int main(int argc, char** argv) {

    REGISTER_BENCHMARK(ferreiradaselva, mathc); // Pure C math library for 2D and 3D game programming

    RUN_BENCHMARKS(argc, argv);

    return 0;
}