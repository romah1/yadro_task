//
// Created by Roman Teriaev on 26.04.2023.
//

#ifndef TAPE_TAPE_SORTER_IMPL_H
#define TAPE_TAPE_SORTER_IMPL_H

#include "tape_impl.h"
#include "tape_factory.h"

class tape_sorter_impl {
public:
    explicit tape_sorter_impl(unsigned int batch_size, tape_impl::configuration conf);

    tape_impl *sort(tape<int> *t, const std::string &out_filename);

    tape_impl *merge(tape_impl *lhs, tape_impl *rhs);

    std::vector<tape_impl *> *split(tape<int> *t);

private:
    const unsigned int batch_size_;
    tape_factory tape_factory_;
    const tape_impl::configuration conf_;
};


#endif //TAPE_TAPE_SORTER_IMPL_H
