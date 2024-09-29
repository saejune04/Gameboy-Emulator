#ifndef MMU_H
#define MMU_H

#include <vector>
#include <cstdint>
#include "address.h"

class MMU {
    public:
        MMU();
        uint8_t read(const Address& location);
        void write(const Address& location, uint8_t value);
    private:
        std::vector<uint8_t> ram_;
};

#endif