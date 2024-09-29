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
        auto execute_opcode();
        uint8_t get_next_byte();
        uint16_t get_next_word();
        
        GameBoy& gameboy;
    private:
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

        void opcode_add_hl(uint16_t addend);
        void opcode_add(const WordRegister& addend); // R

        // TODO: 0xE8

        /* AND */
        void opcode_and_a(uint8_t val);
        
        void opcode_and(const ByteRegister& reg); // r
        void opcode_and(const Address& reg); // (rr)
        void opcode_and(); // n

        /* BIT */

        /* CALL */

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
        void opcode_jp(Address& loc); // nn
        void opcode_jp(PairRegister& loc); // rr
        void opcode_jp(); // e

        /* JR */

        /* LD */
        void opcode_ld(ByteRegister& to, const ByteRegister& from); // r, r'
        void opcode_ld(ByteRegister& to, const Address& from); // r, (rr)
        void opcode_ld(const Address& to, const ByteRegister& from); // (rr), r
        void opcode_ld(const Address& to); // (rr), n
        void opcode_ld(ByteRegister& to); // r, n
        void opcode_ld_get_address(ByteRegister& to); // r, (nn)
        void opcode_ld(const ByteRegister& from); // (nn), r
        void opcode_ld(WordRegister& to); // rr, nn
        void opcode_ld(const WordRegister& from); // (nn), R
        void opcode_ld(WordRegister& to, const WordRegister& from); // R, R

        // TODO: 0XC1 AND 0XF8
        void opcode_ld_from_address();
        void opcode_ld_to_address();

        /* LDH */
        void opcode_ldh(ByteRegister& to, const ByteRegister& from); // r, (r8)
        void opcode_ldh(); // (r8), r
        void opcode_ldh(); // r, (n8)

        /* NOP */
        void opcode_nop();

        /* OR */
        void opcode_or(const ByteRegister& reg); // r
        void opcode_or(const Address& reg); // (rr)
        void opcode_or(); // n

        /* POP */
        void opcode_pop(WordRegister& to); // R
        
        /* PUSH */
        void opcode_push(const WordRegister& from); // R

        /* RL */

        /* RLA */
        void opcode_rla();

        /* RLC */

        /* RLCA */
        void opcode_rlca();

        /* RES */

        /* RET */
        

        /* RETI */
        void opcode_reti();

        /* RR*/

        /* RRA */
        void opcode_rra();

        /* RRC */

        /* RRCA */
        void opcode_rrca();

        /* RST */

        /* SBC */
        void opcode_sbc_a(const uint8_t subtrahend);

        void opcode_sbc(const ByteRegister& subtrahend); // r
        void opcode_sbc(const Address& subtrahend); // (rr)
        void opcode_sbc(); // n

        /* SCF */
        void opcode_scf();

        /* SET */

        /* SLA */

        /* SRA */

        /* SRL */

        /* STOP */
        void opcode_stop();

        /* SUB */
        void opcode_sub_a(const uint8_t subtrahend);

        void opcode_sub(const ByteRegister& subtrahend); // r
        void opcode_sub(const Address& subtrahend); // (rr)
        void opcode_sub(); // n

        /* SWAP */

        /* XOR */
        void opcode_xor(const ByteRegister& reg); // r
        void opcode_xor(const Address& reg); // (rr)
        void opcode_xor(); // n



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