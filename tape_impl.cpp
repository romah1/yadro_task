//
// Created by Roman Teriaev on 24.04.2023.
//

#include "tape_impl.h"

TapeImpl::TapeImpl(std::string &fileName) : fin_(fileName, std::fstream::in) {}

// Tape
void TapeImpl::left() {

}

void TapeImpl::right() {

}

char TapeImpl::read() {
    return 0;
}
