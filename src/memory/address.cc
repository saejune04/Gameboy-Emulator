#include "address.h"
Address::Address(uint16_t address): address_(address) {}
Address::Address(const ByteRegister& reg): address_(0xFF00 + reg.get_val()) {}
Address::Address(const PairRegister& reg): address_(reg.get_val()) {}
Address::Address(const WordRegister& reg): address_(reg.get_val()) {}

uint16_t Address::get_address() const {
    return address_;
}