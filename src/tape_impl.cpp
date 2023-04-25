//
// Created by Roman Teriaev on 24.04.2023.
//

#include "tape_impl.h"

TapeImpl::TapeImpl(const std::string &fileName) : fin_(fileName, std::fstream::in) {
    right_();
}

// Tape
void TapeImpl::left() {
    left_();
}

void TapeImpl::left_() {
    skip_number_left();
    skip_number_left();
    right_();
}

void TapeImpl::move_one_char_left() {
    fin_.seekp(-1, std::ios_base::cur);
}

void TapeImpl::skip_number_left() {
    skip_whitespace_left();
    if (fin_.tellp() == 0) {
        throw std::out_of_range("trying to move tape at pos 0 to the left");
    }
    skip_not_whitespace_left();
}

void TapeImpl::skip_whitespace_left() {
    if (fin_.eof()) {
        fin_.clear(std::ios_base::goodbit);
        move_one_char_left();
    }
    while (fin_.peek() == ' ' && fin_.tellp() != 0) {
        move_one_char_left();
    }
}

void TapeImpl::skip_not_whitespace_left() {
    if (fin_.eof()) {
        fin_.clear(std::ios_base::goodbit);
        move_one_char_left();
    }
    while (fin_.peek() != ' ' && fin_.tellp() != 0) {
        move_one_char_left();
    }
}

void TapeImpl::right() {
    right_();
    if (fin_.eof()) {
        throw std::out_of_range("trying to move tape at max pos to the right");
    }
}

void TapeImpl::right_() {
    cur_value = std::make_optional(read());
}

bool TapeImpl::has_right() {
    read();
    bool isEof = fin_.eof();
    if (isEof) {
        skip_whitespace_left();
        return false;
    } else {
        left_();
        return true;
    }
}

bool TapeImpl::has_left() {
    skip_number_left();
    bool isFirst = fin_.tellp() == 0;
    read();
    return !isFirst;
}

int TapeImpl::value() {
    return cur_value.value();
}

int TapeImpl::read() {
    int new_value;
    fin_ >> new_value;
    return new_value;
}
