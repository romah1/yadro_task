//
// Created by Roman Teriaev on 26.04.2023.
//

#ifndef TAPE_TAPE_SORTER_IMPL_H
#define TAPE_TAPE_SORTER_IMPL_H

#include "tape_impl.h"
#include "tape_sorter.h"
#include "tape_factory.h"

class tape_sorter_impl : public tape_sorter<int> {
public:
    explicit tape_sorter_impl(unsigned int batch_size, tape_impl::configuration conf);

    tape<int> *sort(tape<int> *t) override;

    tape_impl *merge(tape_impl *lhs, tape_impl *rhs);

    std::vector<tape_impl *> *split(tape<int> *t);

private:
    unsigned int batch_size_;
    tape_factory tape_factory_;
};


#endif //TAPE_TAPE_SORTER_IMPL_H
