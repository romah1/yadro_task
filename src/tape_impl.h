//
// Created by Roman Teriaev on 24.04.2023.
//

#ifndef TAPE_TAPE_IMPL_H
#define TAPE_TAPE_IMPL_H

#include <string>
#include <fstream>
#include <optional>
#include <chrono>

#include "tape.h"

class tape_impl : public Tape<int> {
public:
    struct configuration {
        std::chrono::seconds read_delay;
        std::chrono::seconds write_delay;
        std::chrono::seconds move_delay;

        configuration(
                std::chrono::seconds read_delay,
                std::chrono::seconds write_delay,
                std::chrono::seconds move_delay
        ) : read_delay(read_delay), write_delay(write_delay), move_delay(move_delay) {}
    };

    explicit tape_impl(const std::string &file_name);

    tape_impl(const std::string &file_name, configuration conf);

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
    configuration configuration_;

    void move_one_char_left();

    void unread_delim();

    void unread();

    int read();

    void read_delim();

    static const char delim = ',';
};

#endif //TAPE_TAPE_IMPL_H
