//
// Created by Roman Teriaev on 27.04.2023.
//

#ifndef TAPE_TAPE_FACTORY_H
#define TAPE_TAPE_FACTORY_H

#include "tape_impl.h"

class tape_factory {
public:
    tape_factory(tape_impl::configuration conf);

    tape_impl* create(const std::vector<int> &elems);
private:
    int tape_id_ = 0;
    tape_impl::configuration conf_;

    std::string next_tape_name();
};


#endif //TAPE_TAPE_FACTORY_H
