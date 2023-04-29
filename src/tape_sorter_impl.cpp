//
// Created by Roman Teriaev on 26.04.2023.
//

#include <vector>
#include <algorithm>

#include "tape_sorter_impl.h"
#include "tape_impl.h"

tape_sorter_impl::tape_sorter_impl(
        unsigned int batch_size,
        tape_impl::configuration conf
) : batch_size_(batch_size), tape_factory_(conf), conf_(conf) {}

tape_impl *tape_sorter_impl::sort(tape<int> *t, const std::string &out_tape_filename) {
    auto temp_tapes = split(t);

    while (temp_tapes->size() > 1) {
        auto *new_temp_tapes = new std::vector<tape_impl *>();
        for (int i = 0; i < temp_tapes->size(); i += 2) {
            auto lTape = temp_tapes->at(i);
            tape_impl *rTape;
            if (i + 1 < temp_tapes->size()) {
                rTape = temp_tapes->at(i + 1);
            } else {
                rTape = tape_factory_.create({});
            }
            new_temp_tapes->push_back(merge(lTape, rTape));
            lTape->clean();
            rTape->clean();
        }
        temp_tapes = new_temp_tapes;
    }
    auto temp_result = temp_tapes->at(0);
    auto result = new tape_impl({}, out_tape_filename, conf_);
    while (!temp_result->ended()) {
        result->append_right(temp_result->value());
        temp_result->right();
    }
    temp_result->clean();
    result->rewind();
    result->right();
    return result;
}

std::vector<tape_impl *> *tape_sorter_impl::split(tape<int> *t) {
    auto *tapes = new std::vector<tape_impl *>();
    while (true) {
        auto *buf = new std::vector<int>();
        for (int i = 0; i < batch_size_; ++i) {
            buf->push_back(t->value());
            if (!t->ended()) {
                t->right();
                if (t->ended()) {
                    break;
                }
            } else {
                break;
            }
        }
        std::sort(buf->begin(), buf->end());
        auto new_tape = tape_factory_.create(*buf);
        tapes->push_back(new_tape);
        if (t->ended()) {
            break;
        }
    }
    return tapes;
}

tape_impl *tape_sorter_impl::merge(tape_impl *lhs, tape_impl *rhs) {
    auto *result = tape_factory_.create({});
    while (!lhs->ended() && !rhs->ended()) {
        auto lhsValue = lhs->value();
        auto rhsValue = rhs->value();
        if (lhsValue < rhsValue) {
            result->append_right(lhsValue);
            lhs->right();
        } else {
            result->append_right(rhsValue);
            rhs->right();
        }
    }

    while (!lhs->ended()) {
        result->append_right(lhs->value());
        lhs->right();
    }

    while (!rhs->ended()) {
        result->append_right(rhs->value());
        rhs->right();
    }

    result->rewind();
    result->right();

    return result;
}
