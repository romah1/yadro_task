//
// Created by Roman Teriaev on 24.04.2023.
//

#ifndef TAPE_TAPE_H
#define TAPE_TAPE_H

template<typename T>
class tape {
public:
    virtual void left() = 0;

    virtual void right() = 0;

    virtual bool has_left() = 0;

    virtual bool has_right() = 0;

    virtual bool ended() = 0;

    virtual T value() = 0;

    virtual void write(T value) = 0;

    virtual ~tape() = default;
};

#endif //TAPE_TAPE_H
