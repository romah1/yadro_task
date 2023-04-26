//
// Created by Roman Teriaev on 26.04.2023.
//

#ifndef TAPE_TAPE_SORTER_IMPL_H
#define TAPE_TAPE_SORTER_IMPL_H

#include "tape_impl.h"
#include "tape_sorter.h"

class tape_sorter_impl : public tape_sorter<int> {
public:
    explicit tape_sorter_impl(unsigned int batch_size, tape_impl::configuration tape_configuration);

    tape<int> &sort(tape<int> &t) override;

    tape_impl *merge(tape_impl &lhs, tape_impl &rhs);

private:
    unsigned int batch_size_;
    int tape_id_ = 0;
    tape_impl::configuration tape_configuration_;

    std::vector<tape_impl *> split(tape<int> &t);

    int next_tape_id();

    std::string next_tape_name();
};


#endif //TAPE_TAPE_SORTER_IMPL_H
