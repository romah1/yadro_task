//
// Created by Roman Teriaev on 24.04.2023.
//

#include <iostream>

#include "tape_impl.h"

TapeImpl::TapeImpl(const std::string &file_name)
        : fin_(file_name, std::fstream::in | std::fstream::out), file_name_(file_name) {
    cur_value = std::make_optional(read());
    read_delim();
}

// Tape
void TapeImpl::left() {
    unread_delim();
    unread();
    if (fin_.tellp() == 0) {
        throw std::out_of_range("trying to move tape at pos 0 to the left");
    }
    unread_delim();
    unread();
    right();
}

void TapeImpl::read_delim() {
    char c;
    fin_ >> c;
    if (c != delim) {
        throw std::out_of_range("delim char expected to read");
    }
}

void TapeImpl::move_one_char_left() {
    if (fin_.eof()) {
        fin_.clear(std::iostream::goodbit);
    }
    fin_.seekp(-1, std::ios_base::cur);
}

void TapeImpl::unread_delim() {
    move_one_char_left();
    if (fin_.peek() != delim) {
        std::cout << fin_.peek() - '0' << '\n';
        throw std::out_of_range("delim char expected to unread");
    }
}

void TapeImpl::unread() {
    move_one_char_left();
    while (fin_.peek() != delim && fin_.tellp() != 0) {
        move_one_char_left();
    }
    if (fin_.tellp() != 0) {
        read_delim();
    }
}

void TapeImpl::right() {
    if (!has_right()) {
        throw std::out_of_range("trying to move tape at max pos to the right");
    }
    cur_value = std::make_optional(read());
    read_delim();
}

bool TapeImpl::has_right() {
    return fin_.peek() != EOF;
}

bool TapeImpl::has_left() {
    unread_delim();
    unread();
    bool has_left_ = fin_.tellp() != 0;
    read();
    read_delim();
    return has_left_;
}

int TapeImpl::value() {
    return cur_value.value();
}

int TapeImpl::read() {
    int new_value;
    fin_ >> new_value;
    return new_value;
}

void TapeImpl::write(int value) {
    unread_delim();
    unread();
    auto tmp_file = std::tmpfile();

    {
        auto pos = fin_.tellp();
        fin_.seekp(0, std::iostream::beg);
        fin_.seekg(0, std::iostream::beg);
        char cur_c;
        while (fin_.get(cur_c) && fin_.tellp() < pos) {
            std::putc(cur_c, tmp_file);
        }
        if (pos != 0) {
            std::putc(delim, tmp_file);
        }
    }
    long pos;
    {
        for (auto c: std::to_string(value)) {
            std::putc(c, tmp_file);
        }
        pos = std::ftell(tmp_file);
    }

    {
        read();
        char cur_c;
        while (fin_.get(cur_c) && !fin_.eof()) {
            std::putc(cur_c, tmp_file);
        }
    }

    {
        fin_.close();
        fin_ = std::fstream(file_name_, std::iostream::out | std::iostream::trunc);
        std::rewind(tmp_file);
        while (!std::feof(tmp_file)) {
            auto cur_c = std::getc(tmp_file);
            if (std::feof(tmp_file)) {
                break;
            }
            fin_.put(static_cast<char>(cur_c));
        }
        fin_.close();
        fin_ = std::fstream(file_name_, std::iostream::in | std::iostream::out);
        fin_.seekp(pos, std::iostream::beg);
        fin_.seekg(pos, std::iostream::beg);
        read_delim();
    }

    cur_value = std::make_optional(value);
}
