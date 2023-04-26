//
// Created by Roman Teriaev on 26.04.2023.
//

#ifndef TAPE_TAPE_EXCEPTION_H
#define TAPE_TAPE_EXCEPTION_H

#include <iostream>

class tape_exception : public std::exception {
public:
    explicit tape_exception(const char *msg);

    [[nodiscard]] const char *what() const noexcept override;

private:
    const char *message;
};


#endif //TAPE_TAPE_EXCEPTION_H
