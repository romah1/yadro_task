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
    explicit TapeImpl(const std::string &file_name);

    void left() override;

    void right() override;

    bool has_right() override;

    bool has_left() override;

    int value() override;

    void write(int value) override;

private:
    std::fstream fin_;
    std::optional<int> cur_value;
    std::string file_name_;

    void move_one_char_left();

    void unread_delim();

    void unread();

    int read();

    void read_delim();

    static const char delim = ',';
};

#endif //TAPE_TAPE_IMPL_H
