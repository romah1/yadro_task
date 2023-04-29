//
// Created by Roman Teriaev on 24.04.2023.
//

#include <iostream>
#include <thread>
#include <vector>
#include <stdio.h>

#include "tape_impl.h"
#include "tape_exception.h"

tape_impl::tape_impl(const std::string &file_name) : tape_impl(
        file_name,
        {}
) {}

tape_impl::tape_impl(const std::string &file_name, configuration conf)
        : configuration_(conf) {
    std::fstream touch(file_name_, std::fstream::app | std::fstream::out);
    touch.close();
    fin_ = std::fstream(file_name, std::fstream::in | std::fstream::out);
    if (!fin_.is_open()) {
        auto msg = new std::string("failed to open file ");
        *msg += file_name_;
        throw tape_exception(msg->c_str());
    }
    right_();
}

tape_impl::tape_impl(const std::vector<int> &elems, const std::string &file_name, configuration conf)
        : file_name_(file_name),
          configuration_(conf) {
    std::ofstream touch(file_name_);
    touch.close();
    fin_ = std::fstream(file_name, std::fstream::in | std::fstream::out);
    if (!fin_.is_open()) {
        auto msg = new std::string("failed to open file ");
        *msg += file_name_;
        throw tape_exception(msg->c_str());
    }
    for (auto e: elems) {
        fin_ << e << ',';
    }
    fin_.flush();
    rewind();
    if (!elems.empty()) {
        right_();
    } else {
        fin_.get();
    }
}

// Tape
void tape_impl::left() {
    std::this_thread::sleep_for(configuration_.move_delay);
    unread_delim();
    unread();
    if (fin_.tellp() == 0) {
        throw tape_exception("trying to move tape at pos 0 to the left");
    }
    unread_delim();
    unread();
    right();
}

void tape_impl::read_delim() {
    char c;
    fin_ >> c;
    if (c != delim) {
        throw tape_exception("delim char expected to read");
    }
}

void tape_impl::move_one_char_left() {
    if (fin_.eof()) {
        fin_.clear(std::iostream::goodbit);
    }
    fin_.seekp(-1, std::ios_base::cur);
}

void tape_impl::unread_delim() {
    move_one_char_left();
    if (fin_.peek() != delim) {
        std::cout << fin_.peek() - '0' << '\n';
        throw tape_exception("delim char expected to unread");
    }
}

void tape_impl::unread() {
    move_one_char_left();
    while (fin_.peek() != delim && fin_.tellp() != 0) {
        move_one_char_left();
    }
    if (fin_.tellp() != 0) {
        read_delim();
    }
}

void tape_impl::right() {
    right_();
}

void tape_impl::right_() {
    std::this_thread::sleep_for(configuration_.move_delay);
    if (ended()) {
        throw tape_exception("trying to move tape at max pos to the right");
    }
    if (!has_right()) {
        fin_.get();
        return;
    }
    cur_value = std::make_optional(read());
    read_delim();
}

void tape_impl::append_right(int value) {
    if (fin_.eof()) {
        fin_.clear(std::iostream::goodbit);
    }
    fin_ << value << ',';
    fin_.flush();
    cur_value = std::make_optional(value);
}

bool tape_impl::has_right() {
    return fin_.peek() != EOF;
}

bool tape_impl::ended() {
    return fin_.eof();
}

bool tape_impl::has_left() {
    unread_delim();
    unread();
    bool has_left_ = fin_.tellp() != 0;
    read();
    read_delim();
    return has_left_;
}

int tape_impl::value() {
    return cur_value.value();
}

int tape_impl::read() {
    std::this_thread::sleep_for(configuration_.read_delay);
    int new_value;
    fin_ >> new_value;
    return new_value;
}

void tape_impl::write(int value) {
    std::this_thread::sleep_for(configuration_.write_delay);
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

void tape_impl::rewind() {
    fin_.clear(std::iostream::goodbit);
    fin_.seekg(0, std::iostream::beg);
    fin_.seekp(0, std::iostream::beg);
}

void tape_impl::clean() {
    fin_.close();
    std::remove(file_name_.c_str());
}
