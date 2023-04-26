//
// Created by Roman Teriaev on 26.04.2023.
//

#include <vector>
#include <algorithm>

#include "tape_sorter_impl.h"
#include "tape_impl.h"

tape_sorter_impl::tape_sorter_impl(
        unsigned int batch_size,
        tape_impl::configuration tape_configuration
) : batch_size_(batch_size), tape_configuration_(tape_configuration) {}

tape<int> &tape_sorter_impl::sort(tape<int> &t) {
    auto temp_tapes = split(t);

    while (temp_tapes.size() > 1) {
        std::vector<tape_impl *> new_temp_tapes;
        for (int i = 0; i < temp_tapes.size(); i += 2) {
            auto lTape = temp_tapes[i];
            tape_impl *rTape;
            if (i + 1 < temp_tapes.size()) {
                rTape = temp_tapes[i + 1];
            } else {
                rTape = new tape_impl({}, next_tape_name(), tape_configuration_);
            }
            new_temp_tapes.push_back(merge(*lTape, *rTape));
        }
        temp_tapes = new_temp_tapes;
    }

    return *temp_tapes[0];
}

std::vector<tape_impl *> tape_sorter_impl::split(tape<int> &t) {
    std::vector<tape_impl *> tapes = {};
    while (true) {
        auto* buf = new std::vector<int>();
        for (int i = 0; i < batch_size_; ++i) {
            buf->push_back(t.value());
            if (t.has_right()) {
                t.right();
            } else {
                break;
            }
        }
        std::sort(buf->begin(), buf->end());
        auto new_tape = new tape_impl(
                *buf,
                next_tape_name(),
                tape_configuration_
        );
        new_tape->right();
        tapes.push_back(new_tape);
        if (!t.has_right()) {
            break;
        }
    }
    return tapes;
}

tape_impl *tape_sorter_impl::merge(tape_impl &lhs, tape_impl &rhs) {
    auto *result = new tape_impl({0}, next_tape_name(), tape_configuration_);;
    while (lhs.has_right() && rhs.has_right()) {
        auto lhsValue = lhs.value();
        auto rhsValue = rhs.value();
        if (lhsValue < rhsValue) {
            result->append_right(lhsValue);
            lhs.right();
        } else {
            result->append_right(rhsValue);
            rhs.right();
        }
    }

    while (lhs.has_right()) {
        lhs.right();
        result->append_right(lhs.value());
    }

    while (rhs.has_right()) {
        rhs.right();
        result->append_right(rhs.value());
    }

    return result;
}

int tape_sorter_impl::next_tape_id() {
    return tape_id_++;
}

std::string tape_sorter_impl::next_tape_name() {
    if (tape_id_ > 10) {
        throw std::out_of_range("wtf");
    }
    return "temp_tape_" + std::to_string(next_tape_id()) + ".tmp";
}
