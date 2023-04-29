//
// Created by Roman Teriaev on 24.04.2023.
//

#define BOOST_TEST_MODULE TapeTests

#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <random>
#include <vector>
#include <cstdio>

#include "tape_impl.h"
#include "tape_sorter_impl.h"

const std::string input_filename = "input.in";

struct tape_fixture {
    std::vector<int> input = {-10, -5, -3, 0, 3, 5, 10};
    tape_impl *tape;
    tape_sorter_impl *tape_sorter;
    tape_factory *factory;

    tape_fixture() {
        auto rng = std::default_random_engine{};
        std::shuffle(input.begin(), input.end(), rng);
        tape = new tape_impl(input, input_filename, {});
        tape_sorter = new tape_sorter_impl(2, {});
        factory = new tape_factory({});
    }

    ~tape_fixture() {
        tape->clean();
    }
};

BOOST_FIXTURE_TEST_SUITE(test_tape, tape_fixture);

    BOOST_AUTO_TEST_CASE(TestTapeImplReadReturnsCorrectValue) {
        for (auto v: input) {
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

        for (int i = (int) input.size() - 1; i >= 0; --i) {
            BOOST_CHECK_EQUAL(tape->value(), i);
            if (tape->has_left()) {
                tape->left();
            }
        }
    }

    BOOST_AUTO_TEST_CASE(TestTapeSorterImplMergesWithEmptyCorrectly) {
        tape_impl tape1({1, 3, 5}, "test_merge_tape_1", {});
        tape_impl tape2({}, "test_merge_tape_2", {});

        std::vector<int> expect = {1, 3, 5};
        auto out = tape_sorter->merge(&tape1, &tape2);

        for (auto v: expect) {
            BOOST_CHECK_EQUAL(out->value(), v);
            out->right();
        }
        tape1.clean();
        tape2.clean();
        out->clean();
    }

    BOOST_AUTO_TEST_CASE(TestTapeSorterImplMergesCorrectly) {
        tape_impl tape1({1, 3, 5}, "test_merge_tape_1", {});
        tape_impl tape2({2, 4, 6}, "test_merge_tape_2", {});

        std::vector<int> expect = {1, 2};
        auto out = tape_sorter->merge(&tape1, &tape2);

        for (auto v: expect) {
            BOOST_CHECK_EQUAL(out->value(), v);
            out->right();
        }
        tape1.clean();
        tape2.clean();
        out->clean();
    }

    BOOST_AUTO_TEST_CASE(TestTapeSorterSplitsCorrectly) {
        std::vector<int> input = {1, 2, 3, 4, 5, 6, 7};
        tape_impl tape(
                input,
                "test_split_tape",
                {}
        );
        auto res = tape_sorter->split(&tape);
        int i = 0;
        for (auto r: *res) {
            while (!r->ended()) {
                BOOST_CHECK_NE(i, input.size());
                BOOST_CHECK_EQUAL(r->value(), input[i++]);
                r->right();
            }
            r->clean();
        }
        tape.clean();
    }

    BOOST_AUTO_TEST_CASE(TestTapeSorterSortsCorrectly) {
        auto res = tape_sorter->sort(tape);
        std::sort(input.begin(), input.end());
        for (auto v: input) {
            BOOST_CHECK_EQUAL(res->value(), v);
            res->right();
        }
        res->clean();
    }

    BOOST_AUTO_TEST_CASE(TestTapeImplConfigurationWriteReadFile) {
        const char *file_name = "TestTapeImplConfigurationWriteReadFile";
        auto write_conf = tape_impl::configuration(
                std::chrono::seconds(1),
                std::chrono::seconds(2),
                std::chrono::seconds(3)
        );
        write_conf.to_file(file_name);
        auto read_conf = tape_impl::configuration::from_file(file_name);

        BOOST_CHECK_EQUAL(write_conf.read_delay.count(), read_conf.read_delay.count());
        BOOST_CHECK_EQUAL(write_conf.write_delay.count(), read_conf.write_delay.count());
        BOOST_CHECK_EQUAL(write_conf.move_delay.count(), read_conf.move_delay.count());

        std::remove(file_name);
    }

BOOST_AUTO_TEST_SUITE_END();