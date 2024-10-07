#include "cpu.h"

CPU::CPU(GameBoy& gameboy): 
    gameboy(gameboy),
    AF_(A_, F_),
    BC_(B_, C_),
    DE_(D_ ,E_),
    HL_(H_, L_)
{
}

uint8_t CPU::get_next_byte() {
    uint8_t next_byte = gameboy.mmu.read(Address(PC_));
    PC_.increment();
    return next_byte;
}

uint16_t CPU::get_next_word() {
    uint8_t lsb = get_next_byte();
    uint8_t msb = get_next_byte();
    uint16_t res = (msb << 8) + lsb;
    return res;
}

bool CPU::check_condition(Condition condition) {
    switch (condition) {
        case Z: return F_.get_zero_flag() == 1;
        case NZ: return F_.get_zero_flag() == 0;
        case C: return F_.get_carry_flag() == 1;
        case NC: return F_.get_carry_flag() == 0;
        default: return false;
    }
}

auto CPU::execute_opcode() {
    
}