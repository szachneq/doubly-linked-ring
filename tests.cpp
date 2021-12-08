#include "gtest/gtest.h"
#include "ring.h"

TEST(Ring, ring) {
    try {
        Ring<int, int> ring;
        SUCCEED();
    } catch(...) {
        FAIL();
    }
}
