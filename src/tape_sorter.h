//
// Created by Roman Teriaev on 26.04.2023.
//

#ifndef TAPE_TAPE_SORTER_H
#define TAPE_TAPE_SORTER_H

#include "tape.h"

template<typename T>
class tape_sorter {
public:
    virtual tape<T>* sort(tape<T> *t) = 0;
};

#endif //TAPE_TAPE_SORTER_H
