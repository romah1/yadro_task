//
// Created by Roman Teriaev on 26.04.2023.
//

#include "tape_exception.h"

tape_exception::tape_exception(const char *msg) : message(msg) {}

const char *tape_exception::what() const noexcept {
    return message;
}
