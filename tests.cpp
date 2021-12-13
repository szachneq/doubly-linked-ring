#include <string>
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

TEST(Ring, push_front) {
    // Tests for empty ring
    Ring<int, int> ring;
    ASSERT_EQ(ring.empty(), true);
    ASSERT_EQ(ring.begin(), ring.end());
    for (auto it = ring.begin(); it != ring.end(); it++) { FAIL(); }

    // Push front for empty ring
    auto push_iter = ring.push_front(10, 20);
    auto it = ring.begin();
    ASSERT_EQ(it->first, 10);
    ASSERT_EQ(it->second, 20);
    ASSERT_EQ(push_iter, ring.begin());
    ASSERT_EQ(ring.empty(), false);
    ASSERT_NE(ring.begin(), ring.end());

    // Push front for non empty ring
    push_iter = ring.push_front(30, 40);
    it = ring.begin();
    ASSERT_EQ(it->first, 30);
    ASSERT_EQ(it->second, 40);
    ASSERT_EQ(push_iter, ring.begin());
    it++;
    push_iter++;
    ASSERT_EQ(it, push_iter);
    ASSERT_EQ(it->first, 10);
    ASSERT_EQ(it->second, 20);

    // Test moving backwards
    it = ring.begin();
    it--; // We are now on sentinel so have to go back once again
    it--;
    ASSERT_EQ(it->first, 10);
    ASSERT_EQ(it->second, 20);
    ASSERT_EQ(it, --ring.end());
    it--;
    ASSERT_EQ(it->first, 30);
    ASSERT_EQ(it->second, 40);
    ASSERT_EQ(it, ring.begin());
}

TEST(Ring, insert) {
    // Tests for empty ring
    Ring<std::string, double> ring;
    ASSERT_EQ(ring.empty(), true);

    // Insert for empty ring, insert after sentinel
    auto insert_iter = ring.insert(ring.begin(), std::string("One"), 2.0);
    // ASSERT_EQ(ring.empty(), false);
    ASSERT_EQ(insert_iter->first, std::string("One"));
    ASSERT_EQ(insert_iter->second, 2.0);
    ASSERT_EQ(insert_iter, ring.begin());
    ASSERT_NE(insert_iter, ring.end());

    // Insert after sentinel again
    insert_iter = ring.insert(--ring.begin(), std::string("Three"), 4.0);
    ASSERT_EQ(insert_iter->first, std::string("Three"));
    ASSERT_EQ(insert_iter->second, 4.0);
    ASSERT_EQ(insert_iter, ring.begin());
    ASSERT_NE(insert_iter, ring.end());

    // Insert after last element
    insert_iter = ring.insert(--ring.end(), std::string("Five"), 6.0);
    ASSERT_EQ(insert_iter->first, std::string("Five"));
    ASSERT_EQ(insert_iter->second, 6.0);
    ASSERT_EQ(insert_iter, --ring.end());

    // Insert after middle element
    insert_iter = ring.insert(++ring.begin(), std::string("Seven"), 8.0);

    std::string keys[] = {"Three", "One", "Seven", "Five"};
    double infos[] = {4.0, 2.0, 8.0, 6.0};
    auto it = ring.begin();
    for (int i = 0; i <4; i++) {
        ASSERT_EQ(it->first, keys[i]);
        ASSERT_EQ(it->second, infos[i]);
        it++;
    }
    it = --ring.end();
    for (int i = 3; i >= 0; i--) {
        ASSERT_EQ(it->first, keys[i]);
        ASSERT_EQ(it->second, infos[i]);
        it--;
    }

    // Try to use wrong iterator
    Ring<std::string, int> ring2;
    auto it2 = ring2.begin();
    try {
        ring2.insert(it2, std::string("A"), 1.0);
    } catch(std::invalid_argument const &err) {
        // EXPECT_EQ(err.what(), std::string("Trying to insert item with invalid owner"));
    } catch(...) {
        FAIL(); // Wrong exception thrown
    }
}

TEST(Ring, pop_front) {
    // Initial setup
    Ring<int, int> ring;
    ASSERT_EQ(ring.empty(), true);
    auto it = ring.insert(ring.begin(), 1, 1);
    it = ring.insert(it, 2, 2);
    it = ring.insert(it, 3, 3);
    it = ring.insert(it, 4, 4);
    it = ring.insert(it, 5, 5);
    it = ring.begin();
    for (int i = 0; i < 5; i++) {
        ASSERT_EQ(it->first, i+1);
        ASSERT_EQ(it->second, i+1);
        it++;
    }

    // Remove elements until one is left,
    // Check if proper iterator is returned
    for (int i = 2; i < 6; i++) {
        auto it = ring.pop_front();
        ASSERT_EQ(it->first, i);
        ASSERT_EQ(it->second, i);
    }
    // Should not be empty yet
    ASSERT_EQ(ring.empty(), false);

    // Remove last element
    it = ring.pop_front();
    ASSERT_EQ(ring.empty(), true); // Ring is empty
    ASSERT_EQ(it, ring.begin()); // So begin is sentinel
    ASSERT_EQ(ring.begin(), ring.end());
}

TEST(Ring, erase) {
    SUCCEED();
}

TEST(Ring, copy_constructor) {
    SUCCEED();
}

TEST(Ring, assignment_operator) {
    SUCCEED();
}

TEST(Ring, remove_all) {
    SUCCEED();
}

TEST(Ring, push_end) {
    SUCCEED();
}

TEST(Ring, iterator) {
    Ring<int, int> ring;
    auto it = ring.insert(ring.begin(), 1, 1);
    it = ring.insert(it, 2, 2);
    it = ring.insert(it, 3, 3);
    it = ring.insert(it, 4, 4);
    it = ring.insert(it, 5, 5);
    it = ring.begin();
    it--;
    try {
        it->first = 1;
    } catch(std::runtime_error const &err) {
        EXPECT_EQ(err.what(), std::string("Inaccessible memory"));
    } catch(...) {
        FAIL();
    }
}

TEST(Ring, shuffle) {
    Ring<std::string, int> first;
    first.push_end("uno", 1);
    first.push_end("due", 2);
    first.push_end("tre", 3);
    first.push_end("quattro", 4);

    Ring<std::string, int> second;
    second.push_end("bir", 1);
    second.push_end("iki", 2);
    second.push_end("uc", 3);
    second.push_end("dort", 4);
    second.push_end("bes", 5);

    Ring<std::string, int> result = shuffle(first, 1, second, 2, 3);
    std::string keys[] = {"uno", "bir", "iki", "due", "uc", "dort", "tre", "bes", "bir"};
    int infos[] = {1, 1, 2, 2, 3, 4, 3, 5, 1};

    auto it = result.begin();
    for (int i = 0; i < 9; i++) {
        ASSERT_EQ(it->first, keys[i]);
        ASSERT_EQ(it->second, infos[i]);
        it++;
    }
    ASSERT_EQ(result.empty(), false);

    Ring<std::string, int> empty;

    Ring<std::string, int> r1 = shuffle(first, 1, empty, 2, 3);
    ASSERT_EQ(r1.empty(), false);
    auto it_r1 = r1.begin();
    auto it_first = first.begin();
    for (auto it = first.begin(); it != first.end(); it++) {
        ASSERT_EQ(it_r1->first, it_first->first);
        ASSERT_EQ(it_r1->second, it_first->second);
    }

    Ring<std::string, int> r2 = shuffle(empty, 1, second, 2, 3);
    ASSERT_EQ(r2.empty(), false);
    auto it_r2 = r2.begin();
    auto it_second = second.begin();
    for (auto it = second.begin(); it != second.end(); it++) {
        ASSERT_EQ(it_r2->first, it_second->first);
        ASSERT_EQ(it_r2->second, it_second->second);
    }

    Ring<std::string, int> r3 = shuffle(empty, 1, empty, 2, 3);
    ASSERT_EQ(r3.empty(), true);
}
