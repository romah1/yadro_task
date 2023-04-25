//
// Created by Roman Teriaev on 24.04.2023.
//

#define BOOST_TEST_MODULE TapeTests

#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <random>
#include <vector>
#include <fstream>

#include "tape.h"
#include "tape_impl.h"

const std::string input_filename = "input.in";

struct tape_fixture {
    std::vector<int> input = {-10, -5, -3, 0, 3, 5, 10};

    tape_fixture() {
//        auto rng = std::default_random_engine{};
//        std::shuffle(input.begin(), input.end(), rng);
        std::ofstream out(input_filename);
        for (auto v: input) {
            out << v << ' ';
        }
        out.close();
    }
};

BOOST_FIXTURE_TEST_SUITE(test_tape, tape_fixture);

    BOOST_AUTO_TEST_CASE(TestTapeImplReadReturnsCorrectValue) {
        auto tape = new TapeImpl(input_filename);

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

BOOST_AUTO_TEST_SUITE_END();