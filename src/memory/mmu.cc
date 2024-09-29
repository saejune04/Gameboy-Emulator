#include "mmu.h"

MMU::MMU() {
    ram_ = std::vector<uint8_t>(0xFFFF);
}

uint8_t MMU::read(const Address& location) {
    return ram_.at(location.get_address());
}

void MMU::write(const Address& location, uint8_t value) {
    ram_.at(location.get_address()) = value;
}