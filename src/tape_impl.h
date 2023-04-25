//
// Created by Roman Teriaev on 24.04.2023.
//

#ifndef TAPE_TAPE_IMPL_H
#define TAPE_TAPE_IMPL_H

#include <string>
#include <fstream>
#include <optional>

#include "tape.h"

class TapeImpl : public Tape<int> {
public:
    explicit TapeImpl(const std::string &fileName);

    void left() override;

    void right() override;

    bool has_right() override;

    bool has_left() override;

    int value() override;

private:
    std::fstream fin_;
    std::optional<int> cur_value;

    void left_();

    void move_one_char_left();

    void skip_whitespace_left();

    void skip_not_whitespace_left();

    void skip_number_left();

    void right_();

    int read();
};

#endif //TAPE_TAPE_IMPL_H
