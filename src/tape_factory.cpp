//
// Created by Roman Teriaev on 27.04.2023.
//

#include "tape_factory.h"

tape_factory::tape_factory(tape_impl::configuration conf)
        : conf_(conf) {}

tape_impl *tape_factory::create(const std::vector<int> &elems) {
    return new tape_impl(elems,next_tape_name(), conf_);
}

std::string tape_factory::next_tape_name() {
    return "temp_tape_" + std::to_string(tape_id_++);
}
