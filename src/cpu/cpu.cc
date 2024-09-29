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

auto CPU::execute_opcode() {
    
}