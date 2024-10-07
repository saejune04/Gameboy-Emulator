#include "cpu.h"

CPU::CPU(GameBoy& gameboy): 
    gameboy(gameboy),
    AF_(A_, F_),
    BC_(B_, C_),
    DE_(D_ ,E_),
    HL_(H_, L_)
{
}

void CPU::tick() {
    execute_opcode();
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

void CPU::stack_push(const WordRegister& reg) {
    SP_.decrement();
    gameboy.mmu.write(Address(SP_), reg.high_byte());
    SP_.decrement();
    gameboy.mmu.write(Address(SP_), reg.low_byte());
}

void CPU::stack_pop(WordRegister& reg) {
    uint8_t lsb = gameboy.mmu.read(Address(SP_));
    SP_.increment();
    uint8_t msb = gameboy.mmu.read(Address(SP_));
    SP_.increment();
    uint16_t res = msb << 8 + lsb;
    reg.set_val(res);
}


bool CPU::check_condition(Condition condition) {
    switch (condition) {
        case Condition::Z: return F_.get_zero_flag() == 1;
        case Condition::NZ: return F_.get_zero_flag() == 0;
        case Condition::C: return F_.get_carry_flag() == 1;
        case Condition::NC: return F_.get_carry_flag() == 0;
        default: return false;
    }
}

void CPU::execute_opcode() {
    uint8_t opcode = get_next_byte();
    if (opcode != 0xCB) {
        uint8_t cb_opcode = get_next_byte();
        execute_CB_opcode(cb_opcode);
    } else {
        execute_non_CB_opcode(opcode);
    }
}