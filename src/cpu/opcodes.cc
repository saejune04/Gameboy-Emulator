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
void CPU::_opcode_bit(uint8_t bit_to_test, uint8_t val) {
    uint8_t test_bit = (val >> bit_to_test) & 0x1;
    F_.set_carry_flag(test_bit != 0);
F_.set_subtract_flag(false);
    F_.set_half_carry_flag(true);
}

void CPU::opcode_bit(uint8_t bit_to_test, const ByteRegister& reg) {
    _opcode_bit(bit_to_test, reg.get_val());
}

void CPU::opcode_bit(uint8_t bit_to_test, const Address& reg) {
    _opcode_bit(bit_to_test, gameboy.mmu.read(reg));
}

/* CALL */
void CPU::opcode_call() {
    uint8_t lsb = get_next_byte();
    uint8_t msb = get_next_byte();
    uint16_t nn = (msb << 8) + lsb;
    SP_.decrement();
    gameboy.mmu.write(Address(SP_), msb);
    SP_.decrement();
    gameboy.mmu.write(Address(SP_), lsb);
    PC_.set_val(nn);
}

void CPU::opcode_call(Condition condition) {
    uint8_t lsb = get_next_byte();
    uint8_t msb = get_next_byte();
    uint16_t nn = (msb << 8) + lsb;
    if (check_condition(condition)) {
        SP_.decrement();
        gameboy.mmu.write(Address(SP_), msb);
        SP_.decrement();
        gameboy.mmu.write(Address(SP_), lsb);
        PC_.set_val(nn);
    }
}

/* CCF */
void CPU::opcode_ccf() {
    F_.set_carry_flag(!F_.get_carry_flag());
    F_.set_half_carry_flag(false);
    F_.set_subtract_flag(false);
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
    uint8_t old_A_val = A_.get_val();
    A_.set_val(~old_A_val);
    F_.set_subtract_flag(true);
    F_.set_half_carry_flag(true);
}

/* DAA */
void CPU::opcode_daa() {
    // TODO
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
    reg.decrement();
} // R

/* DI */
void CPU::opcode_di() {
    //TODO
}

/* EI */
void CPU::opcode_ei() {
    //TODO
}

/* HALT */
void CPU::opcode_halt() {
    //TODO
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
    reg.increment();
} // R

/* JP */
void CPU::opcode_jp() {
    uint16_t nn = get_next_word();
    PC_.set_val(nn);
} // nn

void CPU::opcode_jp(PairRegister& reg) {
    PC_.set_val(reg.get_val());
} // rr

void CPU::opcode_jp(Condition condition) {
    uint16_t nn = get_next_word();
    if (check_condition(condition)) {
        PC_.set_val(nn);
    }
}


/* JR */
void CPU::opcode_jr() {
    // int should be 32 bit so hopefully this works :>
    int e = get_next_byte();
    int old_PC_val = PC_.get_val();
    PC_.set_val(old_PC_val + e);    
}

void CPU::opcode_jr(Condition condition) {
    int e = get_next_byte();
    int old_PC_val = PC_.get_val();
    if (check_condition(condition)) {
        PC_.set_val(old_PC_val + e);
    }

}

/* LD */
void CPU::opcode_ld(ByteRegister& to, const ByteRegister& from) {
    to.set_val(from.get_val());
} // r, r

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
    uint16_t nn = get_next_word();
    to.set_val(nn);
} // R, nn and rr, nn

void CPU::opcode_ld(const WordRegister& from) {
    uint16_t loc = get_next_word();
    gameboy.mmu.write(Address(loc), from.low_byte());
    gameboy.mmu.write(Address(loc), from.high_byte());
} // (nn), R

void CPU::opcode_ld(WordRegister& to, const WordRegister& from) {
    to.set_val(from.get_val());
} // R, R



// TODO: 0XC1 AND 0XF8
void CPU::opcode_ld_from_address() {
    //todo???
}
void CPU::opcode_ld_to_address() {
    // todo???
}

/* LDH */
void CPU::opcode_ldh(ByteRegister& to, const ByteRegister& from) {
    // todo
} // r, (r8)
void CPU::opcode_ldh() {
    // todo
} // (r8), r
void CPU::opcode_ldh() {
    // todo
} // r, (n8)

/* NOP */
void opcode_nop() {
    return;
}

/* OR */
void CPU::opcode_or_a(uint8_t val) {
    uint8_t old_A_val = A_.get_val();
    A_.set_val(old_A_val | val);

    F_.set_zero_flag(A_.get_val() == 0);
    F_.set_subtract_flag(false);
    F_.set_half_carry_flag(false);
    F_.set_carry_flag(false);
}

void CPU::opcode_or(const ByteRegister& reg) {
    opcode_or_a(reg.get_val());    
} // r

void CPU::opcode_or(const Address& reg) {
    opcode_or_a(gameboy.mmu.read(reg));    
} // (rr)

void CPU::opcode_or() {
    opcode_or_a(get_next_byte());    
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
uint8_t CPU::_opcode_rl(uint8_t val) {
    uint8_t old_carry_bit = F_.get_carry_flag();
    uint8_t new_carry_bit = val & 0x80;
    uint8_t res = (val << 1) | old_carry_bit;

    F_.set_zero_flag(res == 0);
    F_.set_subtract_flag(false);
    F_.set_half_carry_flag(false);
    F_.set_carry_flag(new_carry_bit == 1);
    return res;
}

void CPU::opcode_rl(ByteRegister& reg) {
    reg.set_val(_opcode_rl(reg.get_val()));
}

void CPU::opcode_rl(Address& reg) {
    gameboy.mmu.write(reg, _opcode_rl(gameboy.mmu.read(reg)));
}

/* RLA */
void CPU::opcode_rla() {
    opcode_rl(A_);
    F_.set_zero_flag(false);
}

/* RLC */
uint8_t CPU::_opcode_rlc(uint8_t val) {
    uint8_t carry_flag = val & 0x80;
    uint8_t res = val << 1 | carry_flag;

    F_.set_carry_flag(carry_flag == 1);
    F_.set_zero_flag(res == 0);
    F_.set_subtract_flag(false);
    F_.set_half_carry_flag(false);

    return res;
}

void CPU::opcode_rlc(ByteRegister& reg) {
    reg.set_val(_opcode_rlc(reg.get_val()));
}

void CPU::opcode_rlc(Address& reg) {
    gameboy.mmu.write(reg, _opcode_rlc(gameboy.mmu.read(reg)));
}

/* RLCA */
void CPU::opcode_rlca() {
    opcode_rlc(A_);
    F_.set_zero_flag(false);
}

/* RES */
uint8_t CPU::_opcode_res(uint8_t bit_to_reset, uint8_t val) {
    // bit 7 is left, 0 is right
    uint8_t mask = ~(1 << bit_to_reset);
    uint8_t res = val & mask;
    return res;
}

void CPU::opcode_res(uint8_t bit_to_reset, ByteRegister& reg) {
    reg.set_val(_opcode_res(bit_to_reset, reg.get_val()));
}

void CPU::opcode_res(uint8_t bit_to_reset, Address& reg) {
    gameboy.mmu.write(reg, _opcode_res(bit_to_reset, gameboy.mmu.read(reg)));
}

/* RET */
void CPU::opcode_ret() {
    uint8_t lsb = gameboy.mmu.read(Address(SP_));
    SP_.increment();
    uint8_t msb = gameboy.mmu.read(Address(SP_));
    SP_.increment();
    
    uint16_t res = (msb << 8) + lsb;
    PC_.set_val(res);
}

void CPU::opcode_ret(Condition condition) {
    if (check_condition(condition)) {
        uint8_t lsb = gameboy.mmu.read(Address(SP_));
        SP_.increment();
        uint8_t msb = gameboy.mmu.read(Address(SP_));
        SP_.increment();
        
        uint16_t res = (msb << 8) + lsb;
        PC_.set_val(res);
    }
}

/* RETI */
void CPU::opcode_reti() {
    opcode_ret();
    IME_ = true;
}

/* RR*/
uint8_t CPU::_opcode_rr(uint8_t val) {
    uint8_t old_carry_bit = F_.get_carry_flag();
    uint8_t new_carry_bit = val & 0x01;
    uint8_t res = (val >> 1) | (old_carry_bit << 7);

    F_.set_zero_flag(res == 0);
    F_.set_subtract_flag(false);
    F_.set_half_carry_flag(false);
    F_.set_carry_flag(new_carry_bit == 1);
    return res;
}

void CPU::opcode_rr(ByteRegister& reg) {
    reg.set_val(_opcode_rr(reg.get_val()));
}

void CPU::opcode_rr(Address& reg) {
    gameboy.mmu.write(reg, _opcode_rr(gameboy.mmu.read(reg)));
}

/* RRA */
void CPU::opcode_rra() {
    opcode_rr(A_);
    F_.set_zero_flag(false);
}

/* RRC */
uint8_t CPU::_opcode_rrc(uint8_t val) {
    uint8_t carry_flag = val & 0x01;
    uint8_t res = val >> 1 | (carry_flag << 7);

    F_.set_carry_flag(carry_flag == 1);
    F_.set_zero_flag(res == 0);
    F_.set_subtract_flag(false);
    F_.set_half_carry_flag(false);

    return res;
}

void CPU::opcode_rrc(ByteRegister& reg) {
    reg.set_val(_opcode_rrc(reg.get_val()));
}

void CPU::opcode_rrc(Address& reg) {
    gameboy.mmu.write(reg, _opcode_rrc(gameboy.mmu.read(reg)));
}

/* RRCA */
void CPU::opcode_rrca() {
    opcode_rlc(A_);
    F_.set_zero_flag(false);
}

/* RST */
void opcode_rst(uint8_t val) {
    // TODO
}

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
    F_.set_carry_flag(true);
    F_.set_subtract_flag(false);
    F_.set_half_carry_flag(false);
}

/* SET */
uint8_t CPU::_opcode_set(uint8_t bit_to_set, uint8_t val) {
    // same as res but sets to 1 instead 0
    uint8_t mask = 1 << bit_to_set;
    uint8_t res = val | mask;
    return res; 
}

void CPU::opcode_set(uint8_t bit_to_set, ByteRegister& reg) {
    reg.set_val(_opcode_set(bit_to_set, reg.get_val()));
}

void CPU::opcode_set(uint8_t bit_to_set, Address& reg) {
    gameboy.mmu.write(reg, _opcode_set(bit_to_set, gameboy.mmu.read(reg)));
}


/* SLA */
uint8_t CPU::_opcode_sla(uint8_t val) {
    uint8_t carry_flag = val & 0x80;
    uint8_t res = val << 1;

    F_.set_zero_flag(res == 0);
    F_.set_subtract_flag(false);
    F_.set_half_carry_flag(false);
    F_.set_carry_flag(carry_flag == 1);
    return res;
}

void CPU::opcode_sla(ByteRegister& reg) {
    reg.set_val(reg.get_val());
}

void CPU::opcode_sla(Address& reg) {
    gameboy.mmu.write(reg, _opcode_sla(gameboy.mmu.read(reg)));
}


/* SRA */
uint8_t CPU::_opcode_sra(uint8_t val) {
    uint8_t carry_flag = val & 0x01;
    uint8_t msb = val & 0x80;
    uint8_t res = (val >> 1) | (msb << 7);

    F_.set_zero_flag(res == 0);
    F_.set_subtract_flag(false);
    F_.set_half_carry_flag(false);
    F_.set_carry_flag(carry_flag == 1);
    return res;
}

void CPU::opcode_sra(ByteRegister& reg) {
    reg.set_val(reg.get_val());
}

void CPU::opcode_sra(Address& reg) {
    gameboy.mmu.write(reg, _opcode_sra(gameboy.mmu.read(reg)));
}



/* SRL */
uint8_t CPU::_opcode_srl(uint8_t val) {
    uint8_t lsb = val & 0x01;
    uint8_t res = val >> 1;
    F_.set_zero_flag(res == 0);
    F_.set_subtract_flag(false);
    F_.set_half_carry_flag(false);
    F_.set_carry_flag(lsb == 1);
    return res;
}

void CPU::opcode_srl(ByteRegister& reg) {
    reg.set_val(_opcode_srl(reg.get_val()));
}

void CPU::opcode_srl(Address& reg) {
    gameboy.mmu.write(reg, _opcode_srl(gameboy.mmu.read(reg)));
}

/* STOP */
void CPU::opcode_stop() {
    // TODO 
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
uint8_t CPU::_opcode_swap(uint8_t val) {
    uint8_t res = ((val & 0xF0) >> 4) | ((val & 0x0F) << 4);
    F_.set_zero_flag(res == 0);
    F_.set_subtract_flag(false);
    F_.set_half_carry_flag(false);
    F_.set_carry_flag(false);
    return res;
}

void CPU::opcode_swap(ByteRegister& reg) {
    reg.set_val(_opcode_swap(reg.get_val()));
}

void CPU::opcode_swap(Address& reg) {
    gameboy.mmu.write(reg, _opcode_swap(gameboy.mmu.read(reg)));
}

/* XOR */
void CPU::opcode_xor_a(uint8_t val) {
    uint8_t old_A_val = A_.get_val();
    A_.set_val(old_A_val ^ val);

    F_.set_zero_flag(A_.get_val() == 0);
    F_.set_subtract_flag(false);
    F_.set_half_carry_flag(false);
    F_.set_carry_flag(false);
}

void CPU::opcode_xor(const ByteRegister& reg) {
    opcode_xor_a(reg.get_val());
} // r

void CPU::opcode_xor(const Address& reg) {
    opcode_xor_a(gameboy.mmu.read(reg));
} // (rr)

void CPU::opcode_xor() {
    opcode_xor_a(get_next_byte());
} // n