//
// Created by Roman Teriaev on 26.04.2023.
//

#include "tape_sorter_impl.h"

tape_sorter_impl::tape_sorter_impl(unsigned int batch_size) :batch_size_(batch_size) {}

const tape<int>& tape_sorter_impl::sort(const tape<int> &t) {
    return t;
}
