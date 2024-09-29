#ifndef ADDRESS_H
#define ADDRESS_H

#include <cstdint>
#include "registers.h"

class Address {
    public:
        explicit Address(uint16_t address);
        explicit Address(const ByteRegister& reg);
        explicit Address(const PairRegister& reg);
        explicit Address(const WordRegister& reg);
        uint16_t get_address() const;

    private:
        uint16_t address_ = 0x0;
};

#endif