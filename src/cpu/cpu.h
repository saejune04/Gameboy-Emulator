#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include "registers.h"
#include "address.h"
#include "mmu.h"
#include "gameboy.h"

class CPU {
    public:
        CPU(GameBoy& gameboy);
        uint8_t get_next_byte();
        uint16_t get_next_word();
        void stack_push(const WordRegister& reg);
        void stack_pop(WordRegister& reg);
        void execute_opcode();
        
        GameBoy& gameboy;

        enum class Condition {
            Z,
            NZ,
            C,
            NC
        };

        bool check_condition(Condition condition);
        void tick();


    private:

        bool interrupts_enabled = false;
        bool halted = false;
    
        std::vector<uint8_t> rst_vectors = {0x00, 0x08, 0x10, 0x18, 0x20, 0x28, 0x30, 0x38};

        bool IME_;

        /* Registers */
        // Basic 8-bit registers
        ByteRegister A_, B_, C_, D_, E_, H_, L_;
        
        // Flags register
        FlagRegister F_;

        // Special 8-bit registers
        ByteRegister IR_; // Instruction Register
        ByteRegister IE_; // Interrupt Enable

        // 16-bit registers
        WordRegister PC_; // Program Counter
        WordRegister SP_; // Stack Pointer

        PairRegister AF_, BC_, DE_, HL_; // 

        // Opcodes
        /** Notation
         * r = 8-bit register
         * R = 16-bit register
         * rr = pair register
         * n = next byte in memory (as pointed to by the program counter)
         * nn = next word in memory
         * (x) = byte stored at location x in memory
         * (r8) = byte stored at location 0xFF00 + (r) in memory
         */

        /* ADC */
        void opcode_adc_a(uint8_t addend);
        void opcode_adc(const ByteRegister& addend); // r
        void opcode_adc(const Address& addend); // (rr)
        void opcode_adc(); // n

        /* ADD */
        void opcode_add_a(uint8_t addend);
        void opcode_add(const ByteRegister& addend); // r
        void opcode_add(const Address& addend); // (rr)
        void opcode_add(); // n

        void opcode_add_hl();
        void opcode_add(const WordRegister& addend); // R

        // TODO: 0xE8

        /* AND */
        void opcode_and_a(uint8_t val);
        
        void opcode_and(const ByteRegister& reg); // r
        void opcode_and(const Address& reg); // (rr)
        void opcode_and(); // n

        /* BIT */
        void _opcode_bit(uint8_t bit_to_test, uint8_t val);

        void opcode_bit(uint8_t bit_to_test, const ByteRegister& reg);
        void opcode_bit(uint8_t bit_to_test, const Address& reg);

        /* CALL */
        void opcode_call();
        void opcode_call(Condition condition);

        /* CCF */
        void opcode_ccf();

        /* CP */
        void opcode_cp_a(const uint8_t subtrahend);

        void opcode_cp(const ByteRegister& subtrahend); // r
        void opcode_cp(const Address& subtrahend); // (rr)
        void opcode_cp(); // n

        /* CPL */
        void opcode_cpl();

        /* DAA */
        void opcode_daa();

        /* DEC */
        void opcode_dec(ByteRegister& reg); // r
        void opcode_dec(Address& reg); // (rr)

        void opcode_dec(WordRegister& reg); // R

        /* DI */
        void opcode_di();

        /* EI */
        void opcode_ei();

        /* HALT */
        void opcode_halt();

        /* INC */
        void opcode_inc(ByteRegister& reg); // r
        void opcode_inc(Address& reg); // (rr)
        void opcode_inc(WordRegister& reg); // R

        /* JP */
        void opcode_jp(); // nn
        void opcode_jp(PairRegister& reg); // rr
        void opcode_jp(Condition condition); // cc nn

        /* JR */
        void opcode_jr(); // e
        void opcode_jr(Condition condition);

        /* LD */
        void opcode_ld(ByteRegister& to, const ByteRegister& from); // r, r
        void opcode_ld(ByteRegister& to, const Address& from); // r, (rr)
        void opcode_ld(const Address& to, const ByteRegister& from); // (rr), r
        void opcode_ld(const Address& to); // (rr), n
        void opcode_ld(ByteRegister& to); // r, n
        void opcode_ld_get_address(ByteRegister& to); // r, (nn)
        void opcode_ld(const ByteRegister& from); // (nn), r
        void opcode_ld(WordRegister& to); // R, nn and rr, nn
        void opcode_ld(const WordRegister& from); // (nn), R
        void opcode_ld(WordRegister& to, const WordRegister& from); // R, R

        void opcode_ld_hl(); // HL, SP + e

        /* LDH */
        void opcode_ldh_to_A(const ByteRegister& from);
        void opcode_ldh_from_A(const ByteRegister& to);
        void opcode_ldh_to_A();
        void opcode_ldh_from_A();

        /* NOP */
        void opcode_nop();

        /* OR */
        void opcode_or_a(uint8_t val);
        void opcode_or(const ByteRegister& reg); // r
        void opcode_or(const Address& reg); // (rr)
        void opcode_or(); // n

        /* POP */
        void opcode_pop(WordRegister& to); // R
        
        /* PUSH */
        void opcode_push(const WordRegister& from); // R

        /* RL */
        uint8_t _opcode_rl(uint8_t val);

        void opcode_rl(ByteRegister& reg);
        void opcode_rl(Address& reg);

        /* RLA */
        void opcode_rla();

        /* RLC */
        uint8_t _opcode_rlc(uint8_t val);
        
        void opcode_rlc(ByteRegister& reg);
        void opcode_rlc(Address& reg);

        /* RLCA */
        void opcode_rlca();

        /* RES */
        uint8_t _opcode_res(uint8_t bit_to_reset, uint8_t val);

        void opcode_res(uint8_t bit_to_reset, ByteRegister& reg);
        void opcode_res(uint8_t bit_to_reset, Address& reg);

        /* RET */
        void opcode_ret();
        void opcode_ret(Condition condition);

        /* RETI */
        void opcode_reti();

        /* RR*/
        uint8_t _opcode_rr(uint8_t val);
        void opcode_rr(ByteRegister& reg);
        void opcode_rr(Address& reg);

        /* RRA */
        void opcode_rra();

        /* RRC */
        uint8_t _opcode_rrc(uint8_t val);

        void opcode_rrc(ByteRegister& reg);
        void opcode_rrc(Address& reg);

        /* RRCA */
        void opcode_rrca();

        /* RST */
        void opcode_rst(uint8_t index);

        /* SBC */
        void opcode_sbc_a(const uint8_t subtrahend);

        void opcode_sbc(const ByteRegister& subtrahend); // r
        void opcode_sbc(const Address& subtrahend); // (rr)
        void opcode_sbc(); // n

        /* SCF */
        void opcode_scf();

        /* SET */
        uint8_t _opcode_set(uint8_t bit_to_set, uint8_t val);

        void opcode_set(uint8_t bit_to_set, ByteRegister& reg);
        void opcode_set(uint8_t bit_to_set, Address& reg);

        /* SLA */
        uint8_t _opcode_sla(uint8_t val);
        void opcode_sla(ByteRegister& reg);
        void opcode_sla(Address& reg);

        /* SRA */
        uint8_t _opcode_sra(uint8_t val);
        void opcode_sra(ByteRegister& reg);
        void opcode_sra(Address& reg);

        /* SRL */
        uint8_t _opcode_srl(uint8_t val);
        void opcode_srl(ByteRegister& reg);
        void opcode_srl(Address& reg);

        /* STOP */
        void opcode_stop();

        /* SUB */
        void opcode_sub_a(const uint8_t subtrahend);

        void opcode_sub(const ByteRegister& subtrahend); // r
        void opcode_sub(const Address& subtrahend); // (rr)
        void opcode_sub(); // n

        /* SWAP */
        uint8_t _opcode_swap(uint8_t val);
        void opcode_swap(ByteRegister& reg);
        void opcode_swap(Address& reg);

        /* XOR */
        void opcode_xor_a(uint8_t val);
        void opcode_xor(const ByteRegister& reg); // r
        void opcode_xor(const Address& reg); // (rr)
        void opcode_xor(); // n


        void execute_non_CB_opcode(uint8_t opcode) {
            switch(opcode) {
                case 0x00: opcode_00(); break; case 0x01: opcode_01(); break; case 0x02: opcode_02(); break; case 0x03: opcode_03(); break; case 0x04: opcode_04(); break; case 0x05: opcode_05(); break; case 0x06: opcode_06(); break; case 0x07: opcode_07(); break; case 0x08: opcode_08(); break; case 0x09: opcode_09(); break; case 0x0A: opcode_0a(); break; case 0x0B: opcode_0b(); break; case 0x0C: opcode_0c(); break; case 0x0D: opcode_0d(); break; case 0x0E: opcode_0e(); break; case 0x0F: opcode_0f(); break;
                case 0x10: opcode_10(); break; case 0x11: opcode_11(); break; case 0x12: opcode_12(); break; case 0x13: opcode_13(); break; case 0x14: opcode_14(); break; case 0x15: opcode_15(); break; case 0x16: opcode_16(); break; case 0x17: opcode_17(); break; case 0x18: opcode_18(); break; case 0x19: opcode_19(); break; case 0x1A: opcode_1a(); break; case 0x1B: opcode_1b(); break; case 0x1C: opcode_1c(); break; case 0x1D: opcode_1d(); break; case 0x1E: opcode_1e(); break; case 0x1F: opcode_1f(); break;
                case 0x20: opcode_20(); break; case 0x21: opcode_21(); break; case 0x22: opcode_22(); break; case 0x23: opcode_23(); break; case 0x24: opcode_24(); break; case 0x25: opcode_25(); break; case 0x26: opcode_26(); break; case 0x27: opcode_27(); break; case 0x28: opcode_28(); break; case 0x29: opcode_29(); break; case 0x2A: opcode_2a(); break; case 0x2B: opcode_2b(); break; case 0x2C: opcode_2c(); break; case 0x2D: opcode_2d(); break; case 0x2E: opcode_2e(); break; case 0x2F: opcode_2f(); break;
                case 0x30: opcode_30(); break; case 0x31: opcode_31(); break; case 0x32: opcode_32(); break; case 0x33: opcode_33(); break; case 0x34: opcode_34(); break; case 0x35: opcode_35(); break; case 0x36: opcode_36(); break; case 0x37: opcode_37(); break; case 0x38: opcode_38(); break; case 0x39: opcode_39(); break; case 0x3A: opcode_3a(); break; case 0x3B: opcode_3b(); break; case 0x3C: opcode_3c(); break; case 0x3D: opcode_3d(); break; case 0x3E: opcode_3e(); break; case 0x3F: opcode_3f(); break;
                case 0x40: opcode_40(); break; case 0x41: opcode_41(); break; case 0x42: opcode_42(); break; case 0x43: opcode_43(); break; case 0x44: opcode_44(); break; case 0x45: opcode_45(); break; case 0x46: opcode_46(); break; case 0x47: opcode_47(); break; case 0x48: opcode_48(); break; case 0x49: opcode_49(); break; case 0x4A: opcode_4a(); break; case 0x4B: opcode_4b(); break; case 0x4C: opcode_4c(); break; case 0x4D: opcode_4d(); break; case 0x4E: opcode_4e(); break; case 0x4F: opcode_4f(); break;
                case 0x50: opcode_50(); break; case 0x51: opcode_51(); break; case 0x52: opcode_52(); break; case 0x53: opcode_53(); break; case 0x54: opcode_54(); break; case 0x55: opcode_55(); break; case 0x56: opcode_56(); break; case 0x57: opcode_57(); break; case 0x58: opcode_58(); break; case 0x59: opcode_59(); break; case 0x5A: opcode_5a(); break; case 0x5B: opcode_5b(); break; case 0x5C: opcode_5c(); break; case 0x5D: opcode_5d(); break; case 0x5E: opcode_5e(); break; case 0x5F: opcode_5f(); break;
                case 0x60: opcode_60(); break; case 0x61: opcode_61(); break; case 0x62: opcode_62(); break; case 0x63: opcode_63(); break; case 0x64: opcode_64(); break; case 0x65: opcode_65(); break; case 0x66: opcode_66(); break; case 0x67: opcode_67(); break; case 0x68: opcode_68(); break; case 0x69: opcode_69(); break; case 0x6A: opcode_6a(); break; case 0x6B: opcode_6b(); break; case 0x6C: opcode_6c(); break; case 0x6D: opcode_6d(); break; case 0x6E: opcode_6e(); break; case 0x6F: opcode_6f(); break;
                case 0x70: opcode_70(); break; case 0x71: opcode_71(); break; case 0x72: opcode_72(); break; case 0x73: opcode_73(); break; case 0x74: opcode_74(); break; case 0x75: opcode_75(); break; case 0x76: opcode_76(); break; case 0x77: opcode_77(); break; case 0x78: opcode_78(); break; case 0x79: opcode_79(); break; case 0x7A: opcode_7a(); break; case 0x7B: opcode_7b(); break; case 0x7C: opcode_7c(); break; case 0x7D: opcode_7d(); break; case 0x7E: opcode_7e(); break; case 0x7F: opcode_7f(); break;
                case 0x80: opcode_80(); break; case 0x81: opcode_81(); break; case 0x82: opcode_82(); break; case 0x83: opcode_83(); break; case 0x84: opcode_84(); break; case 0x85: opcode_85(); break; case 0x86: opcode_86(); break; case 0x87: opcode_87(); break; case 0x88: opcode_88(); break; case 0x89: opcode_89(); break; case 0x8A: opcode_8a(); break; case 0x8B: opcode_8b(); break; case 0x8C: opcode_8c(); break; case 0x8D: opcode_8d(); break; case 0x8E: opcode_8e(); break; case 0x8F: opcode_8f(); break;
                case 0x90: opcode_90(); break; case 0x91: opcode_91(); break; case 0x92: opcode_92(); break; case 0x93: opcode_93(); break; case 0x94: opcode_94(); break; case 0x95: opcode_95(); break; case 0x96: opcode_96(); break; case 0x97: opcode_97(); break; case 0x98: opcode_98(); break; case 0x99: opcode_99(); break; case 0x9A: opcode_9a(); break; case 0x9B: opcode_9b(); break; case 0x9C: opcode_9c(); break; case 0x9D: opcode_9d(); break; case 0x9E: opcode_9e(); break; case 0x9F: opcode_9f(); break;
                case 0xA0: opcode_a0(); break; case 0xA1: opcode_a1(); break; case 0xA2: opcode_a2(); break; case 0xA3: opcode_a3(); break; case 0xA4: opcode_a4(); break; case 0xA5: opcode_a5(); break; case 0xA6: opcode_a6(); break; case 0xA7: opcode_a7(); break; case 0xA8: opcode_a8(); break; case 0xA9: opcode_a9(); break; case 0xAA: opcode_aa(); break; case 0xAB: opcode_ab(); break; case 0xAC: opcode_ac(); break; case 0xAD: opcode_ad(); break; case 0xAE: opcode_ae(); break; case 0xAF: opcode_af(); break;
                case 0xB0: opcode_b0(); break; case 0xB1: opcode_b1(); break; case 0xB2: opcode_b2(); break; case 0xB3: opcode_b3(); break; case 0xB4: opcode_b4(); break; case 0xB5: opcode_b5(); break; case 0xB6: opcode_b6(); break; case 0xB7: opcode_b7(); break; case 0xB8: opcode_b8(); break; case 0xB9: opcode_b9(); break; case 0xBA: opcode_ba(); break; case 0xBB: opcode_bb(); break; case 0xBC: opcode_bc(); break; case 0xBD: opcode_bd(); break; case 0xBE: opcode_be(); break; case 0xBF: opcode_bf(); break;
                case 0xC0: opcode_c0(); break; case 0xC1: opcode_c1(); break; case 0xC2: opcode_c2(); break; case 0xC3: opcode_c3(); break; case 0xC4: opcode_c4(); break; case 0xC5: opcode_c5(); break; case 0xC6: opcode_c6(); break; case 0xC7: opcode_c7(); break; case 0xC8: opcode_c8(); break; case 0xC9: opcode_c9(); break; case 0xCA: opcode_ca(); break; case 0xCB: opcode_cb(); break; case 0xCC: opcode_cc(); break; case 0xCD: opcode_cd(); break; case 0xCE: opcode_ce(); break; case 0xCF: opcode_cf(); break;
                case 0xD0: opcode_d0(); break; case 0xD1: opcode_d1(); break; case 0xD2: opcode_d2(); break; case 0xD3: opcode_d3(); break; case 0xD4: opcode_d4(); break; case 0xD5: opcode_d5(); break; case 0xD6: opcode_d6(); break; case 0xD7: opcode_d7(); break; case 0xD8: opcode_d8(); break; case 0xD9: opcode_d9(); break; case 0xDA: opcode_da(); break; case 0xDB: opcode_db(); break; case 0xDC: opcode_dc(); break; case 0xDD: opcode_dd(); break; case 0xDE: opcode_de(); break; case 0xDF: opcode_df(); break;
                case 0xE0: opcode_e0(); break; case 0xE1: opcode_e1(); break; case 0xE2: opcode_e2(); break; case 0xE3: opcode_e3(); break; case 0xE4: opcode_e4(); break; case 0xE5: opcode_e5(); break; case 0xE6: opcode_e6(); break; case 0xE7: opcode_e7(); break; case 0xE8: opcode_e8(); break; case 0xE9: opcode_e9(); break; case 0xEA: opcode_ea(); break; case 0xEB: opcode_eb(); break; case 0xEC: opcode_ec(); break; case 0xED: opcode_ed(); break; case 0xEE: opcode_ee(); break; case 0xEF: opcode_ef(); break;
                case 0xF0: opcode_f0(); break; case 0xF1: opcode_f1(); break; case 0xF2: opcode_f2(); break; case 0xF3: opcode_f3(); break; case 0xF4: opcode_f4(); break; case 0xF5: opcode_f5(); break; case 0xF6: opcode_f6(); break; case 0xF7: opcode_f7(); break; case 0xF8: opcode_f8(); break; case 0xF9: opcode_f9(); break; case 0xFA: opcode_fa(); break; case 0xFB: opcode_fb(); break; case 0xFC: opcode_fc(); break; case 0xFD: opcode_fd(); break; case 0xFE: opcode_fe(); break; case 0xFF: opcode_ff(); break;
            }
        }        

        void execute_CB_opcode(uint8_t opcode) {
            switch(opcode) {
                case 0x00: opcode_cb_00(); break; case 0x01: opcode_cb_01(); break; case 0x02: opcode_cb_02(); break; case 0x03: opcode_cb_03(); break; case 0x04: opcode_cb_04(); break; case 0x05: opcode_cb_05(); break; case 0x06: opcode_cb_06(); break; case 0x07: opcode_cb_07(); break; case 0x08: opcode_cb_08(); break; case 0x09: opcode_cb_09(); break; case 0x0A: opcode_cb_0a(); break; case 0x0B: opcode_cb_0b(); break; case 0x0C: opcode_cb_0c(); break; case 0x0D: opcode_cb_0d(); break; case 0x0E: opcode_cb_0e(); break; case 0x0F: opcode_cb_0f(); break;
                case 0x10: opcode_cb_10(); break; case 0x11: opcode_cb_11(); break; case 0x12: opcode_cb_12(); break; case 0x13: opcode_cb_13(); break; case 0x14: opcode_cb_14(); break; case 0x15: opcode_cb_15(); break; case 0x16: opcode_cb_16(); break; case 0x17: opcode_cb_17(); break; case 0x18: opcode_cb_18(); break; case 0x19: opcode_cb_19(); break; case 0x1A: opcode_cb_1a(); break; case 0x1B: opcode_cb_1b(); break; case 0x1C: opcode_cb_1c(); break; case 0x1D: opcode_cb_1d(); break; case 0x1E: opcode_cb_1e(); break; case 0x1F: opcode_cb_1f(); break;
                case 0x20: opcode_cb_20(); break; case 0x21: opcode_cb_21(); break; case 0x22: opcode_cb_22(); break; case 0x23: opcode_cb_23(); break; case 0x24: opcode_cb_24(); break; case 0x25: opcode_cb_25(); break; case 0x26: opcode_cb_26(); break; case 0x27: opcode_cb_27(); break; case 0x28: opcode_cb_28(); break; case 0x29: opcode_cb_29(); break; case 0x2A: opcode_cb_2a(); break; case 0x2B: opcode_cb_2b(); break; case 0x2C: opcode_cb_2c(); break; case 0x2D: opcode_cb_2d(); break; case 0x2E: opcode_cb_2e(); break; case 0x2F: opcode_cb_2f(); break;
                case 0x30: opcode_cb_30(); break; case 0x31: opcode_cb_31(); break; case 0x32: opcode_cb_32(); break; case 0x33: opcode_cb_33(); break; case 0x34: opcode_cb_34(); break; case 0x35: opcode_cb_35(); break; case 0x36: opcode_cb_36(); break; case 0x37: opcode_cb_37(); break; case 0x38: opcode_cb_38(); break; case 0x39: opcode_cb_39(); break; case 0x3A: opcode_cb_3a(); break; case 0x3B: opcode_cb_3b(); break; case 0x3C: opcode_cb_3c(); break; case 0x3D: opcode_cb_3d(); break; case 0x3E: opcode_cb_3e(); break; case 0x3F: opcode_cb_3f(); break;
                case 0x40: opcode_cb_40(); break; case 0x41: opcode_cb_41(); break; case 0x42: opcode_cb_42(); break; case 0x43: opcode_cb_43(); break; case 0x44: opcode_cb_44(); break; case 0x45: opcode_cb_45(); break; case 0x46: opcode_cb_46(); break; case 0x47: opcode_cb_47(); break; case 0x48: opcode_cb_48(); break; case 0x49: opcode_cb_49(); break; case 0x4A: opcode_cb_4a(); break; case 0x4B: opcode_cb_4b(); break; case 0x4C: opcode_cb_4c(); break; case 0x4D: opcode_cb_4d(); break; case 0x4E: opcode_cb_4e(); break; case 0x4F: opcode_cb_4f(); break;
                case 0x50: opcode_cb_50(); break; case 0x51: opcode_cb_51(); break; case 0x52: opcode_cb_52(); break; case 0x53: opcode_cb_53(); break; case 0x54: opcode_cb_54(); break; case 0x55: opcode_cb_55(); break; case 0x56: opcode_cb_56(); break; case 0x57: opcode_cb_57(); break; case 0x58: opcode_cb_58(); break; case 0x59: opcode_cb_59(); break; case 0x5A: opcode_cb_5a(); break; case 0x5B: opcode_cb_5b(); break; case 0x5C: opcode_cb_5c(); break; case 0x5D: opcode_cb_5d(); break; case 0x5E: opcode_cb_5e(); break; case 0x5F: opcode_cb_5f(); break;
                case 0x60: opcode_cb_60(); break; case 0x61: opcode_cb_61(); break; case 0x62: opcode_cb_62(); break; case 0x63: opcode_cb_63(); break; case 0x64: opcode_cb_64(); break; case 0x65: opcode_cb_65(); break; case 0x66: opcode_cb_66(); break; case 0x67: opcode_cb_67(); break; case 0x68: opcode_cb_68(); break; case 0x69: opcode_cb_69(); break; case 0x6A: opcode_cb_6a(); break; case 0x6B: opcode_cb_6b(); break; case 0x6C: opcode_cb_6c(); break; case 0x6D: opcode_cb_6d(); break; case 0x6E: opcode_cb_6e(); break; case 0x6F: opcode_cb_6f(); break;
                case 0x70: opcode_cb_70(); break; case 0x71: opcode_cb_71(); break; case 0x72: opcode_cb_72(); break; case 0x73: opcode_cb_73(); break; case 0x74: opcode_cb_74(); break; case 0x75: opcode_cb_75(); break; case 0x76: opcode_cb_76(); break; case 0x77: opcode_cb_77(); break; case 0x78: opcode_cb_78(); break; case 0x79: opcode_cb_79(); break; case 0x7A: opcode_cb_7a(); break; case 0x7B: opcode_cb_7b(); break; case 0x7C: opcode_cb_7c(); break; case 0x7D: opcode_cb_7d(); break; case 0x7E: opcode_cb_7e(); break; case 0x7F: opcode_cb_7f(); break;
                case 0x80: opcode_cb_80(); break; case 0x81: opcode_cb_81(); break; case 0x82: opcode_cb_82(); break; case 0x83: opcode_cb_83(); break; case 0x84: opcode_cb_84(); break; case 0x85: opcode_cb_85(); break; case 0x86: opcode_cb_86(); break; case 0x87: opcode_cb_87(); break; case 0x88: opcode_cb_88(); break; case 0x89: opcode_cb_89(); break; case 0x8A: opcode_cb_8a(); break; case 0x8B: opcode_cb_8b(); break; case 0x8C: opcode_cb_8c(); break; case 0x8D: opcode_cb_8d(); break; case 0x8E: opcode_cb_8e(); break; case 0x8F: opcode_cb_8f(); break;
                case 0x90: opcode_cb_90(); break; case 0x91: opcode_cb_91(); break; case 0x92: opcode_cb_92(); break; case 0x93: opcode_cb_93(); break; case 0x94: opcode_cb_94(); break; case 0x95: opcode_cb_95(); break; case 0x96: opcode_cb_96(); break; case 0x97: opcode_cb_97(); break; case 0x98: opcode_cb_98(); break; case 0x99: opcode_cb_99(); break; case 0x9A: opcode_cb_9a(); break; case 0x9B: opcode_cb_9b(); break; case 0x9C: opcode_cb_9c(); break; case 0x9D: opcode_cb_9d(); break; case 0x9E: opcode_cb_9e(); break; case 0x9F: opcode_cb_9f(); break;
                case 0xA0: opcode_cb_a0(); break; case 0xA1: opcode_cb_a1(); break; case 0xA2: opcode_cb_a2(); break; case 0xA3: opcode_cb_a3(); break; case 0xA4: opcode_cb_a4(); break; case 0xA5: opcode_cb_a5(); break; case 0xA6: opcode_cb_a6(); break; case 0xA7: opcode_cb_a7(); break; case 0xA8: opcode_cb_a8(); break; case 0xA9: opcode_cb_a9(); break; case 0xAA: opcode_cb_aa(); break; case 0xAB: opcode_cb_ab(); break; case 0xAC: opcode_cb_ac(); break; case 0xAD: opcode_cb_ad(); break; case 0xAE: opcode_cb_ae(); break; case 0xAF: opcode_cb_af(); break;
                case 0xB0: opcode_cb_b0(); break; case 0xB1: opcode_cb_b1(); break; case 0xB2: opcode_cb_b2(); break; case 0xB3: opcode_cb_b3(); break; case 0xB4: opcode_cb_b4(); break; case 0xB5: opcode_cb_b5(); break; case 0xB6: opcode_cb_b6(); break; case 0xB7: opcode_cb_b7(); break; case 0xB8: opcode_cb_b8(); break; case 0xB9: opcode_cb_b9(); break; case 0xBA: opcode_cb_ba(); break; case 0xBB: opcode_cb_bb(); break; case 0xBC: opcode_cb_bc(); break; case 0xBD: opcode_cb_bd(); break; case 0xBE: opcode_cb_be(); break; case 0xBF: opcode_cb_bf(); break;
                case 0xC0: opcode_cb_c0(); break; case 0xC1: opcode_cb_c1(); break; case 0xC2: opcode_cb_c2(); break; case 0xC3: opcode_cb_c3(); break; case 0xC4: opcode_cb_c4(); break; case 0xC5: opcode_cb_c5(); break; case 0xC6: opcode_cb_c6(); break; case 0xC7: opcode_cb_c7(); break; case 0xC8: opcode_cb_c8(); break; case 0xC9: opcode_cb_c9(); break; case 0xCA: opcode_cb_ca(); break; case 0xCB: opcode_cb_cb(); break; case 0xCC: opcode_cb_cc(); break; case 0xCD: opcode_cb_cd(); break; case 0xCE: opcode_cb_ce(); break; case 0xCF: opcode_cb_cf(); break;
                case 0xD0: opcode_cb_d0(); break; case 0xD1: opcode_cb_d1(); break; case 0xD2: opcode_cb_d2(); break; case 0xD3: opcode_cb_d3(); break; case 0xD4: opcode_cb_d4(); break; case 0xD5: opcode_cb_d5(); break; case 0xD6: opcode_cb_d6(); break; case 0xD7: opcode_cb_d7(); break; case 0xD8: opcode_cb_d8(); break; case 0xD9: opcode_cb_d9(); break; case 0xDA: opcode_cb_da(); break; case 0xDB: opcode_cb_db(); break; case 0xDC: opcode_cb_dc(); break; case 0xDD: opcode_cb_dd(); break; case 0xDE: opcode_cb_de(); break; case 0xDF: opcode_cb_df(); break;
                case 0xE0: opcode_cb_e0(); break; case 0xE1: opcode_cb_e1(); break; case 0xE2: opcode_cb_e2(); break; case 0xE3: opcode_cb_e3(); break; case 0xE4: opcode_cb_e4(); break; case 0xE5: opcode_cb_e5(); break; case 0xE6: opcode_cb_e6(); break; case 0xE7: opcode_cb_e7(); break; case 0xE8: opcode_cb_e8(); break; case 0xE9: opcode_cb_e9(); break; case 0xEA: opcode_cb_ea(); break; case 0xEB: opcode_cb_eb(); break; case 0xEC: opcode_cb_ec(); break; case 0xED: opcode_cb_ed(); break; case 0xEE: opcode_cb_ee(); break; case 0xEF: opcode_cb_ef(); break;
                case 0xF0: opcode_cb_f0(); break; case 0xF1: opcode_cb_f1(); break; case 0xF2: opcode_cb_f2(); break; case 0xF3: opcode_cb_f3(); break; case 0xF4: opcode_cb_f4(); break; case 0xF5: opcode_cb_f5(); break; case 0xF6: opcode_cb_f6(); break; case 0xF7: opcode_cb_f7(); break; case 0xF8: opcode_cb_f8(); break; case 0xF9: opcode_cb_f9(); break; case 0xFA: opcode_cb_fa(); break; case 0xFB: opcode_cb_fb(); break; case 0xFC: opcode_cb_fc(); break; case 0xFD: opcode_cb_fd(); break; case 0xFE: opcode_cb_fe(); break; case 0xFF: opcode_cb_ff(); break;
            }
        }

        // Declaring functions from opcode_00 to opcode_ff (GPT lol)
        void opcode_00(); void opcode_01(); void opcode_02(); void opcode_03(); void opcode_04(); void opcode_05(); void opcode_06(); void opcode_07(); void opcode_08(); void opcode_09(); void opcode_0a(); void opcode_0b(); void opcode_0c(); void opcode_0d(); void opcode_0e(); void opcode_0f();
        void opcode_10(); void opcode_11(); void opcode_12(); void opcode_13(); void opcode_14(); void opcode_15(); void opcode_16(); void opcode_17(); void opcode_18(); void opcode_19(); void opcode_1a(); void opcode_1b(); void opcode_1c(); void opcode_1d(); void opcode_1e(); void opcode_1f();
        void opcode_20(); void opcode_21(); void opcode_22(); void opcode_23(); void opcode_24(); void opcode_25(); void opcode_26(); void opcode_27(); void opcode_28(); void opcode_29(); void opcode_2a(); void opcode_2b(); void opcode_2c(); void opcode_2d(); void opcode_2e(); void opcode_2f();
        void opcode_30(); void opcode_31(); void opcode_32(); void opcode_33(); void opcode_34(); void opcode_35(); void opcode_36(); void opcode_37(); void opcode_38(); void opcode_39(); void opcode_3a(); void opcode_3b(); void opcode_3c(); void opcode_3d(); void opcode_3e(); void opcode_3f();
        void opcode_40(); void opcode_41(); void opcode_42(); void opcode_43(); void opcode_44(); void opcode_45(); void opcode_46(); void opcode_47(); void opcode_48(); void opcode_49(); void opcode_4a(); void opcode_4b(); void opcode_4c(); void opcode_4d(); void opcode_4e(); void opcode_4f();
        void opcode_50(); void opcode_51(); void opcode_52(); void opcode_53(); void opcode_54(); void opcode_55(); void opcode_56(); void opcode_57(); void opcode_58(); void opcode_59(); void opcode_5a(); void opcode_5b(); void opcode_5c(); void opcode_5d(); void opcode_5e(); void opcode_5f();
        void opcode_60(); void opcode_61(); void opcode_62(); void opcode_63(); void opcode_64(); void opcode_65(); void opcode_66(); void opcode_67(); void opcode_68(); void opcode_69(); void opcode_6a(); void opcode_6b(); void opcode_6c(); void opcode_6d(); void opcode_6e(); void opcode_6f();
        void opcode_70(); void opcode_71(); void opcode_72(); void opcode_73(); void opcode_74(); void opcode_75(); void opcode_76(); void opcode_77(); void opcode_78(); void opcode_79(); void opcode_7a(); void opcode_7b(); void opcode_7c(); void opcode_7d(); void opcode_7e(); void opcode_7f();
        void opcode_80(); void opcode_81(); void opcode_82(); void opcode_83(); void opcode_84(); void opcode_85(); void opcode_86(); void opcode_87(); void opcode_88(); void opcode_89(); void opcode_8a(); void opcode_8b(); void opcode_8c(); void opcode_8d(); void opcode_8e(); void opcode_8f();
        void opcode_90(); void opcode_91(); void opcode_92(); void opcode_93(); void opcode_94(); void opcode_95(); void opcode_96(); void opcode_97(); void opcode_98(); void opcode_99(); void opcode_9a(); void opcode_9b(); void opcode_9c(); void opcode_9d(); void opcode_9e(); void opcode_9f();
        void opcode_a0(); void opcode_a1(); void opcode_a2(); void opcode_a3(); void opcode_a4(); void opcode_a5(); void opcode_a6(); void opcode_a7(); void opcode_a8(); void opcode_a9(); void opcode_aa(); void opcode_ab(); void opcode_ac(); void opcode_ad(); void opcode_ae(); void opcode_af();
        void opcode_b0(); void opcode_b1(); void opcode_b2(); void opcode_b3(); void opcode_b4(); void opcode_b5(); void opcode_b6(); void opcode_b7(); void opcode_b8(); void opcode_b9(); void opcode_ba(); void opcode_bb(); void opcode_bc(); void opcode_bd(); void opcode_be(); void opcode_bf();
        void opcode_c0(); void opcode_c1(); void opcode_c2(); void opcode_c3(); void opcode_c4(); void opcode_c5(); void opcode_c6(); void opcode_c7(); void opcode_c8(); void opcode_c9(); void opcode_ca(); void opcode_cb(); void opcode_cc(); void opcode_cd(); void opcode_ce(); void opcode_cf();
        void opcode_d0(); void opcode_d1(); void opcode_d2(); void opcode_d3(); void opcode_d4(); void opcode_d5(); void opcode_d6(); void opcode_d7(); void opcode_d8(); void opcode_d9(); void opcode_da(); void opcode_db(); void opcode_dc(); void opcode_dd(); void opcode_de(); void opcode_df();
        void opcode_e0(); void opcode_e1(); void opcode_e2(); void opcode_e3(); void opcode_e4(); void opcode_e5(); void opcode_e6(); void opcode_e7(); void opcode_e8(); void opcode_e9(); void opcode_ea(); void opcode_eb(); void opcode_ec(); void opcode_ed(); void opcode_ee(); void opcode_ef();
        void opcode_f0(); void opcode_f1(); void opcode_f2(); void opcode_f3(); void opcode_f4(); void opcode_f5(); void opcode_f6(); void opcode_f7(); void opcode_f8(); void opcode_f9(); void opcode_fa(); void opcode_fb(); void opcode_fc(); void opcode_fd(); void opcode_fe(); void opcode_ff();

        // Declaring functions from opcode_cb_00 to opcode_cb_ff
        void opcode_cb_00(); void opcode_cb_01(); void opcode_cb_02(); void opcode_cb_03(); void opcode_cb_04(); void opcode_cb_05(); void opcode_cb_06(); void opcode_cb_07(); void opcode_cb_08(); void opcode_cb_09(); void opcode_cb_0a(); void opcode_cb_0b(); void opcode_cb_0c(); void opcode_cb_0d(); void opcode_cb_0e(); void opcode_cb_0f();
        void opcode_cb_10(); void opcode_cb_11(); void opcode_cb_12(); void opcode_cb_13(); void opcode_cb_14(); void opcode_cb_15(); void opcode_cb_16(); void opcode_cb_17(); void opcode_cb_18(); void opcode_cb_19(); void opcode_cb_1a(); void opcode_cb_1b(); void opcode_cb_1c(); void opcode_cb_1d(); void opcode_cb_1e(); void opcode_cb_1f();
        void opcode_cb_20(); void opcode_cb_21(); void opcode_cb_22(); void opcode_cb_23(); void opcode_cb_24(); void opcode_cb_25(); void opcode_cb_26(); void opcode_cb_27(); void opcode_cb_28(); void opcode_cb_29(); void opcode_cb_2a(); void opcode_cb_2b(); void opcode_cb_2c(); void opcode_cb_2d(); void opcode_cb_2e(); void opcode_cb_2f();
        void opcode_cb_30(); void opcode_cb_31(); void opcode_cb_32(); void opcode_cb_33(); void opcode_cb_34(); void opcode_cb_35(); void opcode_cb_36(); void opcode_cb_37(); void opcode_cb_38(); void opcode_cb_39(); void opcode_cb_3a(); void opcode_cb_3b(); void opcode_cb_3c(); void opcode_cb_3d(); void opcode_cb_3e(); void opcode_cb_3f();
        void opcode_cb_40(); void opcode_cb_41(); void opcode_cb_42(); void opcode_cb_43(); void opcode_cb_44(); void opcode_cb_45(); void opcode_cb_46(); void opcode_cb_47(); void opcode_cb_48(); void opcode_cb_49(); void opcode_cb_4a(); void opcode_cb_4b(); void opcode_cb_4c(); void opcode_cb_4d(); void opcode_cb_4e(); void opcode_cb_4f();
        void opcode_cb_50(); void opcode_cb_51(); void opcode_cb_52(); void opcode_cb_53(); void opcode_cb_54(); void opcode_cb_55(); void opcode_cb_56(); void opcode_cb_57(); void opcode_cb_58(); void opcode_cb_59(); void opcode_cb_5a(); void opcode_cb_5b(); void opcode_cb_5c(); void opcode_cb_5d(); void opcode_cb_5e(); void opcode_cb_5f();
        void opcode_cb_60(); void opcode_cb_61(); void opcode_cb_62(); void opcode_cb_63(); void opcode_cb_64(); void opcode_cb_65(); void opcode_cb_66(); void opcode_cb_67(); void opcode_cb_68(); void opcode_cb_69(); void opcode_cb_6a(); void opcode_cb_6b(); void opcode_cb_6c(); void opcode_cb_6d(); void opcode_cb_6e(); void opcode_cb_6f();
        void opcode_cb_70(); void opcode_cb_71(); void opcode_cb_72(); void opcode_cb_73(); void opcode_cb_74(); void opcode_cb_75(); void opcode_cb_76(); void opcode_cb_77(); void opcode_cb_78(); void opcode_cb_79(); void opcode_cb_7a(); void opcode_cb_7b(); void opcode_cb_7c(); void opcode_cb_7d(); void opcode_cb_7e(); void opcode_cb_7f();
        void opcode_cb_80(); void opcode_cb_81(); void opcode_cb_82(); void opcode_cb_83(); void opcode_cb_84(); void opcode_cb_85(); void opcode_cb_86(); void opcode_cb_87(); void opcode_cb_88(); void opcode_cb_89(); void opcode_cb_8a(); void opcode_cb_8b(); void opcode_cb_8c(); void opcode_cb_8d(); void opcode_cb_8e(); void opcode_cb_8f();
        void opcode_cb_90(); void opcode_cb_91(); void opcode_cb_92(); void opcode_cb_93(); void opcode_cb_94(); void opcode_cb_95(); void opcode_cb_96(); void opcode_cb_97(); void opcode_cb_98(); void opcode_cb_99(); void opcode_cb_9a(); void opcode_cb_9b(); void opcode_cb_9c(); void opcode_cb_9d(); void opcode_cb_9e(); void opcode_cb_9f();
        void opcode_cb_a0(); void opcode_cb_a1(); void opcode_cb_a2(); void opcode_cb_a3(); void opcode_cb_a4(); void opcode_cb_a5(); void opcode_cb_a6(); void opcode_cb_a7(); void opcode_cb_a8(); void opcode_cb_a9(); void opcode_cb_aa(); void opcode_cb_ab(); void opcode_cb_ac(); void opcode_cb_ad(); void opcode_cb_ae(); void opcode_cb_af();
        void opcode_cb_b0(); void opcode_cb_b1(); void opcode_cb_b2(); void opcode_cb_b3(); void opcode_cb_b4(); void opcode_cb_b5(); void opcode_cb_b6(); void opcode_cb_b7(); void opcode_cb_b8(); void opcode_cb_b9(); void opcode_cb_ba(); void opcode_cb_bb(); void opcode_cb_bc(); void opcode_cb_bd(); void opcode_cb_be(); void opcode_cb_bf();
        void opcode_cb_c0(); void opcode_cb_c1(); void opcode_cb_c2(); void opcode_cb_c3(); void opcode_cb_c4(); void opcode_cb_c5(); void opcode_cb_c6(); void opcode_cb_c7(); void opcode_cb_c8(); void opcode_cb_c9(); void opcode_cb_ca(); void opcode_cb_cb(); void opcode_cb_cc(); void opcode_cb_cd(); void opcode_cb_ce(); void opcode_cb_cf();
        void opcode_cb_d0(); void opcode_cb_d1(); void opcode_cb_d2(); void opcode_cb_d3(); void opcode_cb_d4(); void opcode_cb_d5(); void opcode_cb_d6(); void opcode_cb_d7(); void opcode_cb_d8(); void opcode_cb_d9(); void opcode_cb_da(); void opcode_cb_db(); void opcode_cb_dc(); void opcode_cb_dd(); void opcode_cb_de(); void opcode_cb_df();
        void opcode_cb_e0(); void opcode_cb_e1(); void opcode_cb_e2(); void opcode_cb_e3(); void opcode_cb_e4(); void opcode_cb_e5(); void opcode_cb_e6(); void opcode_cb_e7(); void opcode_cb_e8(); void opcode_cb_e9(); void opcode_cb_ea(); void opcode_cb_eb(); void opcode_cb_ec(); void opcode_cb_ed(); void opcode_cb_ee(); void opcode_cb_ef();
        void opcode_cb_f0(); void opcode_cb_f1(); void opcode_cb_f2(); void opcode_cb_f3(); void opcode_cb_f4(); void opcode_cb_f5(); void opcode_cb_f6(); void opcode_cb_f7(); void opcode_cb_f8(); void opcode_cb_f9(); void opcode_cb_fa(); void opcode_cb_fb(); void opcode_cb_fc(); void opcode_cb_fd(); void opcode_cb_fe(); void opcode_cb_ff();

};

#endif