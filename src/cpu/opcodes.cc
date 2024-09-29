#include "cpu.h"
#include "registers.h"

/* ADC */
void CPU::opcode_adc_a(uint8_t addend) {
    uint8_t old_A_val = A_.get_val();
    bool carry_flag = F_.get_carry_flag();
    uint16_t res = old_A_val + carry_flag + addend;

    A_.set_val(static_cast<uint8_t>(res));

    F_.set_zero_flag(A_.get_val() == 0);
    F_.set_subtract_flag(false);
    F_.set_half_carry_flag(((old_A_val & 0xF) + (addend & 0xF) + carry_flag) > 0xF);
    F_.set_carry_flag((res & 0xFF00) != 0);
}

void CPU::opcode_adc(const ByteRegister& addend) {
    opcode_adc_a(addend.get_val());
} // r

void CPU::opcode_adc(const Address& addend) {
    opcode_adc_a(gameboy.mmu.read(addend));
} // (rr)

void CPU::opcode_adc() {
    opcode_adc_a(get_next_byte());
} // n

/* ADD */
void CPU::opcode_add_a(uint8_t addend) {
    uint8_t old_A_val = A_.get_val();
    uint16_t res = old_A_val + addend;

    A_.set_val(static_cast<uint8_t>(res));

    F_.set_zero_flag(A_.get_val() == 0);
    F_.set_subtract_flag(false);
    F_.set_half_carry_flag(((old_A_val & 0xF) + (addend & 0xF)) > 0xF);
    F_.set_carry_flag((res & 0xFF00) != 0);
}

void CPU::opcode_add(const ByteRegister& addend) {
    opcode_add_a(addend.get_val());
} // r

void CPU::opcode_add(const Address& addend) {
    opcode_add_a(gameboy.mmu.read(addend));
} // (rr)

void CPU::opcode_add() {
    opcode_add_a(get_next_byte());
} // n

void CPU::opcode_add_hl(uint16_t addend) {

}

void CPU::opcode_add(const WordRegister& addend) {
    
} // R

// TODO: 0xE8

/* AND */
void CPU::opcode_and_a(uint8_t val) {
    uint8_t old_A_val = A_.get_val();
    A_.set_val(old_A_val & val);

    F_.set_zero_flag(A_.get_val() == 0);
    F_.set_subtract_flag(false);
    F_.set_half_carry_flag(true);
    F_.set_carry_flag(false);
}

void CPU::opcode_and(const ByteRegister& reg) {
    opcode_and_a(reg.get_val());
} // r

void CPU::opcode_and(const Address& reg) {
    opcode_and_a(gameboy.mmu.read(reg));
} // (rr)

void CPU::opcode_and() {
    opcode_and_a(get_next_byte());
} // n

/* BIT */

/* CALL */

/* CCF */
void CPU::opcode_ccf() {
    
}

/* CP */
void CPU::opcode_cp_a(const uint8_t subtrahend) {
    uint8_t old_A_val = A_.get_val();
    int res = old_A_val - subtrahend;

    F_.set_zero_flag(res == 0);
    F_.set_subtract_flag(true);
    F_.set_half_carry_flag(((old_A_val & 0xF) - (subtrahend & 0xF)) < 0);
    F_.set_carry_flag(res < 0);
}

void CPU::opcode_cp(const ByteRegister& subtrahend) {
    opcode_cp_a(subtrahend.get_val());
} // r

void CPU::opcode_cp(const Address& subtrahend) {
    opcode_cp_a(gameboy.mmu.read(subtrahend));
} // (rr)

void CPU::opcode_cp() {
    opcode_cp_a(get_next_byte());
} // n

/* CPL */
void CPU::opcode_cpl() {
    
}

/* DAA */
void CPU::opcode_daa() {
    
}

/* DEC */
void CPU::opcode_dec(ByteRegister& reg) {
    uint8_t old_reg_val = reg.get_val();
    int res = old_reg_val - 1;
    reg.decrement();

    F_.set_zero_flag(res == 0);
    F_.set_subtract_flag(true);
    F_.set_half_carry_flag(((old_reg_val & 0xF) - 1) < 0);
} // r

void CPU::opcode_dec(Address& reg) {
    uint8_t old_reg_val = gameboy.mmu.read(reg);
    int res = old_reg_val - 1;
    gameboy.mmu.write(reg, static_cast<uint8_t>(res));  // TODO: check that this cast actually works lol (same with inc)

    F_.set_zero_flag(res == 0);
    F_.set_subtract_flag(true);
    F_.set_half_carry_flag(((old_reg_val & 0xF) - 1) < 0);
} // (rr)

void CPU::opcode_dec(WordRegister& reg) {
    
} // R

/* DI */
void CPU::opcode_di() {
    
}

/* EI */
void CPU::opcode_ei() {
    
}

/* HALT */
void CPU::opcode_halt() {
    
}

/* INC */
void CPU::opcode_inc(ByteRegister& reg) {
    uint8_t old_reg_val = reg.get_val();
    uint16_t res = old_reg_val + 1;
    reg.increment();

    F_.set_zero_flag(res == 0);
    F_.set_subtract_flag(false);
    F_.set_half_carry_flag(((old_reg_val & 0xF) + 1) > 0xF);
} // r

void CPU::opcode_inc(Address& reg) {
    uint8_t old_reg_val = gameboy.mmu.read(reg);
    uint16_t res = old_reg_val + 1;
    gameboy.mmu.write(reg, static_cast<uint8_t>(res));

    F_.set_zero_flag(res == 0);
    F_.set_subtract_flag(false);
    F_.set_half_carry_flag(((old_reg_val & 0xF) + 1) > 0xF);
} // (rr)

void CPU::opcode_inc(WordRegister& reg) {
    
} // R

/* JP */
void CPU::opcode_jp(Address& loc) {
    
} // nn
void CPU::opcode_jp(PairRegister& loc) {
    
} // rr
void CPU::opcode_jp() {
    
} // e

/* JR */

/* LD */
void CPU::opcode_ld(ByteRegister& to, const ByteRegister& from) {
    to.set_val(from.get_val());
} // r, r'

void CPU::opcode_ld(ByteRegister& to, const Address& from) {
    to.set_val(gameboy.mmu.read(from));
} // r, (rr)

void CPU::opcode_ld(const Address& to, const ByteRegister& from) {
    gameboy.mmu.write(to, from.get_val());
} // (rr), r

void CPU::opcode_ld(const Address& to) {
    gameboy.mmu.write(to, get_next_byte());
} // (rr), n

void CPU::opcode_ld(ByteRegister& to) {
    to.set_val(get_next_byte());
} // r, n

void CPU::opcode_ld_get_address(ByteRegister& to) {
   to.set_val(gameboy.mmu.read(Address(get_next_word()))); 
} // r, (nn)

void CPU::opcode_ld(const ByteRegister& from) {
    uint16_t loc = get_next_word();
    gameboy.mmu.write(Address(loc), from.get_val());
} // (nn), r

void CPU::opcode_ld(WordRegister& to) {
    uint16_t loc = get_next_word();
    to.set_val(gameboy.mmu.read(Address(loc)));
} // R, nn

void CPU::opcode_ld(const WordRegister& from) {
    uint16_t loc = get_next_word();
    gameboy.mmu.write(Address(loc), from.get_val());
} // (nn), R

void CPU::opcode_ld(WordRegister& to, const WordRegister& from) {
    to.set_val(from.get_val());
} // R, R

// TODO: 0XC1 AND 0XF8
void CPU::opcode_ld_from_address() {
    
}
void CPU::opcode_ld_to_address() {
    
}

/* LDH */
void CPU::opcode_ldh(ByteRegister& to, const ByteRegister& from) {
    
} // r, (r8)
void CPU::opcode_ldh() {
    
} // (r8), r
void CPU::opcode_ldh() {
    
} // r, (n8)

/* NOP */
void opcode_nop() {
    
}

/* OR */
void CPU::opcode_or() {
    
}

void CPU::opcode_or(const ByteRegister& reg) {
    
} // r
void CPU::opcode_or(const Address& reg) {
    
} // (rr)
void CPU::opcode_or() {
    
} // n

/* POP */
void CPU::opcode_pop(WordRegister& to) {
    uint8_t lsb = gameboy.mmu.read(Address(SP_));
    SP_.increment();
    uint8_t msb = gameboy.mmu.read(Address(SP_));
    SP_.increment();
    uint16_t res = msb << 8 + lsb;
    to.set_val(res);
} // R

/* PUSH */
void CPU::opcode_push(const WordRegister& from) {
    SP_.decrement();
    gameboy.mmu.write(Address(SP_), from.high_byte());
    SP_.decrement();
    gameboy.mmu.write(Address(SP_), from.low_byte());
} // R

/* RL */

/* RLA */
void CPU::opcode_rla() {
    
}

/* RLC */

/* RLCA */
void CPU::opcode_rlca() {
    
}

/* RES */

/* RET */


/* RETI */
void CPU::opcode_reti() {
    
}

/* RR*/

/* RRA */
void CPU::opcode_rra() {
    
}

/* RRC */

/* RRCA */
void CPU::opcode_rrca() {
    
}

/* RST */

/* SBC */
void CPU::opcode_sbc_a(const uint8_t subtrahend) {
    uint8_t old_A_val = A_.get_val();
    bool carry_flag = F_.get_carry_flag();
    int res = old_A_val - subtrahend - carry_flag;

    A_.set_val(static_cast<uint8_t>(res));

    F_.set_zero_flag(A_.get_val() == 0);
    F_.set_subtract_flag(true);
    F_.set_half_carry_flag(((old_A_val & 0xF) - (subtrahend & 0xF) - carry_flag) < 0);
    F_.set_carry_flag(res < 0);
}

void CPU::opcode_sbc(const ByteRegister& subtrahend) {
    opcode_sbc_a(subtrahend.get_val());
} // r

void CPU::opcode_sbc(const Address& subtrahend) {
    opcode_sbc_a(gameboy.mmu.read(subtrahend));
} // (rr)

void CPU::opcode_sbc() {
    opcode_sbc_a(get_next_byte());
} // n

/* SCF */
void CPU::opcode_scf() {
    
}

/* SET */

/* SLA */

/* SRA */

/* SRL */

/* STOP */
void CPU::opcode_stop() {
    
}

/* SUB */
void CPU::opcode_sub_a(const uint8_t subtrahend) {
    uint8_t old_A_val = A_.get_val();
    int res = old_A_val - subtrahend;

    A_.set_val(static_cast<uint8_t>(res));

    F_.set_zero_flag(A_.get_val() == 0);
    F_.set_subtract_flag(true);
    F_.set_half_carry_flag(((old_A_val & 0xF) - (subtrahend & 0xF)) < 0);
    F_.set_carry_flag(res < 0);
}

void CPU::opcode_sub(const ByteRegister& subtrahend) {
    opcode_sub_a(subtrahend.get_val());
} // r

void CPU::opcode_sub(const Address& subtrahend) {
    opcode_sub_a(gameboy.mmu.read(subtrahend));
} // (rr)

void CPU::opcode_sub() {
    opcode_sub_a(get_next_byte());
} // n

/* SWAP */

/* XOR */
void CPU::opcode_xor(const ByteRegister& reg) {
    
} // r
void CPU::opcode_xor(const Address& reg) {
    
} // (rr)
void CPU::opcode_xor() {
    
} // n