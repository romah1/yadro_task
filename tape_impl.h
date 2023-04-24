//
// Created by Roman Teriaev on 24.04.2023.
//

#ifndef TAPE_TAPE_IMPL_H
#define TAPE_TAPE_IMPL_H

#include <string>
#include <fstream>
#include "tape.h"

class TapeImpl : public Tape<char> {
public:
    explicit TapeImpl(std::string &fileName);

    void left() override;

    void right() override;

    char read() override;

private:
    std::fstream fin_;
};

#endif //TAPE_TAPE_IMPL_H
