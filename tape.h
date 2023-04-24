//
// Created by Roman Teriaev on 24.04.2023.
//

#ifndef TAPE_TAPE_H
#define TAPE_TAPE_H

template<typename T>
class Tape {
public:
    virtual void left() = 0;

    virtual void right() = 0;

    virtual T read() = 0;
};

#endif //TAPE_TAPE_H
