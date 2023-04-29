#include <iostream>
#include <sstream>
#include <vector>

#include "tape_impl.h"
#include "tape_sorter_impl.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "wrong number of arguments" << std::endl;
        std::cerr << "example usage: ./main conf_file_name input_tape_file_name output_tape_file_name" << std::endl;
        return -1;
    }

    auto conf_file_name = argv[1];
    auto input_tape_file_name = argv[2];
    auto output_tape_file_name = argv[3];

    std::cout << "tape config file name = " << conf_file_name << '\n';
    std::cout << "tape content file name = " << input_tape_file_name << '\n';

    auto conf = tape_impl::configuration::from_file(conf_file_name);
    auto tape = tape_impl(input_tape_file_name, conf);

    auto sorter = tape_sorter_impl(2, conf);
    sorter.sort(&tape, output_tape_file_name);

    return 0;
}
