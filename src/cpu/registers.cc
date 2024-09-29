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

}

void FlagRegister::set_subtract_flag(bool val) {
    
}

void FlagRegister::set_half_carry_flag(bool val) {
    
}

void FlagRegister::set_carry_flag(bool val) {
    
}

uint8_t FlagRegister::get_zero_flag() const {
    
}

uint8_t FlagRegister::get_subtract_flag() const {
    
}

uint8_t FlagRegister::get_half_carry_flag() const {
    
}

uint8_t FlagRegister::get_carry_flag() const {
    
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
    // TODO
}

uint16_t PairRegister::get_val() const {
    // TODO
}

void PairRegister::increment() {
    // TODO
}

void PairRegister::decrement() {
    // TODO
}

uint8_t PairRegister::high_byte() const {
    return high_byte_.get_val();
}

uint8_t PairRegister::low_byte() const {
    return low_byte_.get_val();
}
