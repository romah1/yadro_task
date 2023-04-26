//
// Created by Roman Teriaev on 24.04.2023.
//

#define BOOST_TEST_MODULE TapeTests

#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <random>
#include <vector>
#include <fstream>

#include "tape_impl.h"
#include "tape_sorter_impl.h"

const std::string input_filename = "input.in";

struct tape_fixture {
    std::vector<int> input = {-10, 5, -3, 0, 3, 5, 10};
    tape_impl* tape;
    tape_sorter_impl* tape_sorter;

    tape_fixture() {
        auto rng = std::default_random_engine{};
        std::shuffle(input.begin(), input.end(), rng);
        std::ofstream out(input_filename);
        for (auto v: input) {
            out << v << ',';
        }
        out.close();
        tape = new tape_impl(input_filename);
        tape->right();

        tape_sorter = new tape_sorter_impl(2, tape_impl::configuration({}, {}, {}));
    }
};

BOOST_FIXTURE_TEST_SUITE(test_tape, tape_fixture);

    BOOST_AUTO_TEST_CASE(TestTapeImplReadReturnsCorrectValue) {
        for (auto v : input) {
            BOOST_CHECK_EQUAL(tape->value(), v);
            if (tape->has_right()) {
                tape->right();
            }
        }

        for (auto i = input.rbegin(); i != input.rend(); i++) {
            BOOST_CHECK_EQUAL(tape->value(), *i);
            if (tape->has_left()) {
                tape->left();
            }
        }
    }

    BOOST_AUTO_TEST_CASE(TestTapeImplWriteReplacesValues) {
        for (int i = 0; i < input.size(); ++i) {
            tape->write(i);
            if (tape->has_right()) {
                tape->right();
            }
        }

        for (int i = (int)input.size() - 1; i >= 0; --i) {
            BOOST_CHECK_EQUAL(tape->value(), i);
            if (tape->has_left()) {
                tape->left();
            }
        }
    }

    BOOST_AUTO_TEST_CASE(TestTapeSorterImplMergesCorrectly) {
        tape_impl tape1({1, 2, 3}, "test_merge_tape_1", tape_impl::configuration({}, {}, {}));
        tape1.right();
        tape_impl tape2({4, 5, 6}, "test_merge_tape_2", tape_impl::configuration({}, {}, {}));
        tape2.right();
        tape_sorter->merge(tape1, tape2);
//        tape_sorter->sort(*tape);
    }

    BOOST_AUTO_TEST_CASE(TestTapeSorterImplSortsCorrectly) {
        tape_sorter->sort(*tape);
    }

BOOST_AUTO_TEST_SUITE_END();