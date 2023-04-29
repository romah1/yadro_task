#include <iostream>
#include <sstream>
#include <vector>

#include "tape_impl.h"
#include "tape_sorter_impl.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "wrong number of arguments" << std::endl;
        std::cerr << "example usage: ./main conf_file_name tape_file_name" << std::endl;
        return -1;
    }

    auto conf_file_name = argv[1];
    auto tape_file_name = argv[2];

    std::cout << "tape config file name = " << conf_file_name << '\n';
    std::cout << "tape content file name = " << tape_file_name << '\n';

    auto conf = tape_impl::configuration::from_file(conf_file_name);
    auto tape = tape_impl(tape_file_name, conf);

    auto sorter = tape_sorter_impl(2, conf);
    auto res = sorter.sort(&tape);

    std::cout << "sorted tape = ";
    while (!res->ended()) {
        std::cout << res->value() << ' ';
        res->right();
    }

    return 0;
}
