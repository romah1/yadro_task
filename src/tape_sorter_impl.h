//
// Created by Roman Teriaev on 26.04.2023.
//

#ifndef TAPE_TAPE_SORTER_IMPL_H
#define TAPE_TAPE_SORTER_IMPL_H

#include "tape_sorter.h"

class tape_sorter_impl : public tape_sorter<int> {
public:
    explicit tape_sorter_impl(unsigned int batch_size);
    const tape<int>& sort(const tape<int> &t) override;

private:
    unsigned int batch_size_;
};


#endif //TAPE_TAPE_SORTER_IMPL_H
