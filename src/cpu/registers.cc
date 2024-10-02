#include "registers.h"

/* Byte Register */

void ByteRegister::set_val(uint8_t value) {
    val_ = value;
}

uint8_t ByteRegister::get_val() const {
    return val_;
}

void ByteRegister::increment() {
    val_ += 1;
}

void ByteRegister::decrement() {
    val_ -= 1;
}

/* Flag Register */
void FlagRegister::set_zero_flag(bool val){
    uint8_t mask = (val << 7);
    val_ |= mask;
}

void FlagRegister::set_subtract_flag(bool val) {
    uint8_t mask = (val << 6);
    val_ |= mask;
}

void FlagRegister::set_half_carry_flag(bool val) {
    uint8_t mask = (val << 5);
    val_ |= mask;
}

void FlagRegister::set_carry_flag(bool val) {
    uint8_t mask = (val << 4);
    val_ |= mask;
}

uint8_t FlagRegister::get_zero_flag() const {
   return (val_ >> 7) & 0x1; 
}

uint8_t FlagRegister::get_subtract_flag() const {
    return (val_ >> 6) & 0x1;
}

uint8_t FlagRegister::get_half_carry_flag() const {
    return (val_ >> 5) & 0x1;
}

uint8_t FlagRegister::get_carry_flag() const {
    return (val_ >> 4) & 0x1;
}


/* Word Register*/
void WordRegister::set_val(uint16_t value) {
    val_ = value;
}

uint16_t WordRegister::get_val() const {
    return val_;
}

void WordRegister::increment() {
    val_ += 1;
}

void WordRegister::decrement() {
    val_ -= 1;
}

uint8_t WordRegister::high_byte() const {
    uint8_t res = (val_ & 0xff00) >> 8;
    return res;
}

uint8_t WordRegister::low_byte() const {
    uint8_t res = val_ & 0xff;
    return res;
}

/* Pair Register */
void PairRegister::set_val(uint16_t value) {
    uint8_t msb = (value >> 8);
    uint8_t lsb = (value & 0xff);
    high_byte_.set_val(msb);
    low_byte_.set_val(lsb);
}

uint16_t PairRegister::get_val() const {
    return (high_byte_.get_val() << 8) + low_byte_.get_val();
}

void PairRegister::increment() {
    uint16_t curr_val = get_val();
    set_val(curr_val + 1);
}

void PairRegister::decrement() {
    uint16_t curr_val = get_val();
    set_val(curr_val - 1);
}

uint8_t PairRegister::high_byte() const {
    return high_byte_.get_val();
}

uint8_t PairRegister::low_byte() const {
    return low_byte_.get_val();
}
