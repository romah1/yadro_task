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

class tape_impl : public tape<int> {
public:
    class configuration {
    public:
        std::chrono::seconds read_delay;
        std::chrono::seconds write_delay;
        std::chrono::seconds move_delay;

        configuration(
                std::chrono::seconds read_delay,
                std::chrono::seconds write_delay,
                std::chrono::seconds move_delay
        );

        configuration();

        void to_file(const std::string &file_name);

        static tape_impl::configuration from_file(const std::string &file_name);

        class serialization_exception : public std::exception {
        public:
            explicit serialization_exception(const char *msg);

            [[nodiscard]] const char *what() const noexcept override;

        private:
            const char *message_;
        };

    private:
        constexpr static const char *READ_DELAY = "read_delay";
        constexpr static const char *WRITE_DELAY = "write_delay";
        constexpr static const char *MOVE_DELAY = "move_delay";
    };

    class tape_exception : public std::exception {
    public:
        explicit tape_exception(const char *msg);

        [[nodiscard]] const char *what() const noexcept override;

    private:
        const char *message_;
    };

    explicit tape_impl(const std::string &file_name);

    tape_impl(const std::vector<int> &elems, const std::string &file_name, configuration conf);

    tape_impl(const std::string &file_name, configuration conf);

    void left() override;

    void right() override;

    bool has_right() override;

    bool has_left() override;

    bool ended() override;

    int value() override;

    void write(int value) override;

    void append_right(int value);

    void rewind();

    void clean();

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

    void right_();

    static const char delim = ',';
};

#endif //TAPE_TAPE_IMPL_H
