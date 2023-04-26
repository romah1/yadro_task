//
// Created by Roman Teriaev on 26.04.2023.
//

#ifndef TAPE_TAPE_SORTER_IMPL_H
#define TAPE_TAPE_SORTER_IMPL_H

#include "tape_sorter.h"

class tape_sorter_impl : public tape_sorter<int> {
    const tape<int>& sort(const tape<int> &t) override;
};


#endif //TAPE_TAPE_SORTER_IMPL_H
