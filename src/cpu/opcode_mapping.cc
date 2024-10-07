#include "cpu.h"

void CPU::opcode_00() { opcode_nop(); }
void CPU::opcode_01() { opcode_ld(BC_); }
void CPU::opcode_02() { opcode_ld(Address(BC_), A_); }
void CPU::opcode_03() { opcode_inc(BC_); }
void CPU::opcode_04() { opcode_inc(B_); }
void CPU::opcode_05() { opcode_dec(B_); }
void CPU::opcode_06() { opcode_ld(B_); }
void CPU::opcode_07() { opcode_rlca(); }
void CPU::opcode_08() { opcode_ld(SP_); }
void CPU::opcode_09() { opcode_add(BC_); }
void CPU::opcode_0a() { opcode_ld(A_, Address(BC_)); }
void CPU::opcode_0b() { opcode_dec(BC_); }
void CPU::opcode_0c() { opcode_inc(C_); }
void CPU::opcode_0d() { opcode_dec(C_); }
void CPU::opcode_0e() { opcode_ld(C_); }
void CPU::opcode_0f() { opcode_rrca(); }

void CPU::opcode_10() { opcode_stop(); }
void CPU::opcode_11() { opcode_ld(DE_); }
void CPU::opcode_12() { opcode_ld(Address(DE_), A_); }
void CPU::opcode_13() { opcode_inc(DE_); }
void CPU::opcode_14() { opcode_inc(D_); }
void CPU::opcode_15() { opcode_dec(D_); }
void CPU::opcode_16() { opcode_ld(D_); }
void CPU::opcode_17() { opcode_rla(); }
void CPU::opcode_18() { opcode_jr(); }
void CPU::opcode_19() { opcode_add(DE_); }
void CPU::opcode_1a() { opcode_ld(Address(DE_)); }
void CPU::opcode_1b() { opcode_dec(DE_); }
void CPU::opcode_1c() { opcode_inc(E_); }
void CPU::opcode_1d() { opcode_dec(E_); }
void CPU::opcode_1e() { opcode_ld(E_); }
void CPU::opcode_1f() { opcode_rra(); }

void CPU::opcode_20() { opcode_jr(Condition::NZ); }
void CPU::opcode_21() { opcode_ld(HL_); }
void CPU::opcode_22() { opcode_ld(Address(HL_), A_); HL_.increment(); }
void CPU::opcode_23() { opcode_inc(HL_); }
void CPU::opcode_24() { opcode_inc(H_); }
void CPU::opcode_25() { opcode_dec(H_); }
void CPU::opcode_26() { opcode_ld(H_); }
void CPU::opcode_27() { opcode_daa(); }
void CPU::opcode_28() { opcode_jr(Condition::Z); }
void CPU::opcode_29() { opcode_add(HL_); }
void CPU::opcode_2a() { opcode_ld(A_, Address(HL_)); HL_.increment(); }
void CPU::opcode_2b() { opcode_dec(HL_); }
void CPU::opcode_2c() { opcode_inc(L_); }
void CPU::opcode_2d() { opcode_dec(L_); }
void CPU::opcode_2e() { opcode_ld(L_); }
void CPU::opcode_2f() { opcode_cpl(); }

void CPU::opcode_30() { opcode_jr(Condition::NC); }
void CPU::opcode_31() { opcode_ld(SP_); }
void CPU::opcode_32() { opcode_ld(Address(HL_), A_); HL_.decrement(); }
void CPU::opcode_33() { opcode_inc(SP_); }
void CPU::opcode_34() { opcode_inc(Address(HL_)); }
void CPU::opcode_35() { opcode_dec(Address(HL_)); }
void CPU::opcode_36() { opcode_ld(Address(HL_)); }
void CPU::opcode_37() { opcode_scf(); }
void CPU::opcode_38() { opcode_jr(Condition::C); }
void CPU::opcode_39() { opcode_add(SP_); }
void CPU::opcode_3a() { opcode_ld(A_, Address(HL_)); HL_.decrement(); }
void CPU::opcode_3b() { opcode_dec(SP_); }
void CPU::opcode_3c() { opcode_inc(A_); }
void CPU::opcode_3d() { opcode_dec(A_); }
void CPU::opcode_3e() { opcode_ld(A_); }
void CPU::opcode_3f() { opcode_ccf(); }

void CPU::opcode_40() { opcode_ld(B_, B_); }
void CPU::opcode_41() { opcode_ld(B_, C_); }
void CPU::opcode_42() { opcode_ld(B_, D_); }
void CPU::opcode_43() { opcode_ld(B_, E_); }
void CPU::opcode_44() { opcode_ld(B_, H_); }
void CPU::opcode_45() { opcode_ld(B_, L_); }
void CPU::opcode_46() { opcode_ld(B_, Address(HL_)); }
void CPU::opcode_47() { opcode_ld(B_, A_); }
void CPU::opcode_48() { opcode_ld(C_, B_); }
void CPU::opcode_49() { opcode_ld(C_, C_); }
void CPU::opcode_4a() { opcode_ld(C_, D_); }
void CPU::opcode_4b() { opcode_ld(C_, E_); }
void CPU::opcode_4c() { opcode_ld(C_, H_); }
void CPU::opcode_4d() { opcode_ld(C_, L_); }
void CPU::opcode_4e() { opcode_ld(C_, Address(HL_)); }
void CPU::opcode_4f() { opcode_ld(C_, A_); }

void CPU::opcode_50() { opcode_ld(D_, B_); }
void CPU::opcode_51() { opcode_ld(D_, C_); }
void CPU::opcode_52() { opcode_ld(D_, D_); }
void CPU::opcode_53() { opcode_ld(D_, E_); }
void CPU::opcode_54() { opcode_ld(D_, H_); }
void CPU::opcode_55() { opcode_ld(D_, L_); }
void CPU::opcode_56() { opcode_ld(D_, Address(HL_)); }
void CPU::opcode_57() { opcode_ld(B_, A_); }
void CPU::opcode_58() { opcode_ld(C_, B_); }
void CPU::opcode_59() { opcode_ld(C_, C_); }
void CPU::opcode_5a() { opcode_ld(C_, D_); }
void CPU::opcode_5b() { opcode_ld(C_, E_); }
void CPU::opcode_5c() { opcode_ld(C_, H_); }
void CPU::opcode_5d() { opcode_ld(C_, L_); }
void CPU::opcode_5e() { opcode_ld(C_, Address(HL_)); }
void CPU::opcode_5f() { opcode_ld(C_, A_); }
  
void CPU::opcode_60() { opcode_ld(H_, B_); }
void CPU::opcode_61() { opcode_ld(H_, C_); }
void CPU::opcode_62() { opcode_ld(H_, D_); }
void CPU::opcode_63() { opcode_ld(H_, E_); }
void CPU::opcode_64() { opcode_ld(H_, H_); }
void CPU::opcode_65() { opcode_ld(H_, L_); }
void CPU::opcode_66() { opcode_ld(H_, Address(HL_)); }
void CPU::opcode_67() { opcode_ld(H_, A_); }
void CPU::opcode_68() { opcode_ld(L_, B_); }
void CPU::opcode_69() { opcode_ld(L_, C_); }
void CPU::opcode_6a() { opcode_ld(L_, D_); }
void CPU::opcode_6b() { opcode_ld(L_, E_); }
void CPU::opcode_6c() { opcode_ld(L_, H_); }
void CPU::opcode_6d() { opcode_ld(L_, L_); }
void CPU::opcode_6e() { opcode_ld(L_, Address(HL_)); }
void CPU::opcode_6f() { opcode_ld(L_, A_); }
  
void CPU::opcode_70() { opcode_ld(Address(HL_), B_); }
void CPU::opcode_71() { opcode_ld(Address(HL_), C_); }
void CPU::opcode_72() { opcode_ld(Address(HL_), D_); }
void CPU::opcode_73() { opcode_ld(Address(HL_), E_); }
void CPU::opcode_74() { opcode_ld(Address(HL_), H_); }
void CPU::opcode_75() { opcode_ld(Address(HL_), L_); }
void CPU::opcode_76() { opcode_halt(); }
void CPU::opcode_77() { opcode_ld(Address(HL_), A_); }
void CPU::opcode_78() { opcode_ld(A_, B_); }
void CPU::opcode_79() { opcode_ld(A_, C_); }
void CPU::opcode_7a() { opcode_ld(A_, D_); }
void CPU::opcode_7b() { opcode_ld(A_, E_); }
void CPU::opcode_7c() { opcode_ld(A_, H_); }
void CPU::opcode_7d() { opcode_ld(A_, L_); }
void CPU::opcode_7e() { opcode_ld(A_, Address(HL_)); }
void CPU::opcode_7f() { opcode_ld(A_, A_); }

void CPU::opcode_80() { opcode_add(B_); }
void CPU::opcode_81() { opcode_add(C_); }
void CPU::opcode_82() { opcode_add(D_); }
void CPU::opcode_83() { opcode_add(E_); }
void CPU::opcode_84() { opcode_add(H_); }
void CPU::opcode_85() { opcode_add(L_); }
void CPU::opcode_86() { opcode_add(Address(HL_)); }
void CPU::opcode_87() { opcode_add(A_); }
void CPU::opcode_88() { opcode_adc(B_); }
void CPU::opcode_89() { opcode_adc(C_); }
void CPU::opcode_8a() { opcode_adc(D_); }
void CPU::opcode_8b() { opcode_adc(E_); }
void CPU::opcode_8c() { opcode_adc(H_); }
void CPU::opcode_8d() { opcode_adc(L_); }
void CPU::opcode_8e() { opcode_adc(Address(HL_)); }
void CPU::opcode_8f() { opcode_adc(A_); }

void CPU::opcode_90() { opcode_sub(B_); }
void CPU::opcode_91() { opcode_sub(C_); }
void CPU::opcode_92() { opcode_sub(D_); }
void CPU::opcode_93() { opcode_sub(E_); }
void CPU::opcode_94() { opcode_sub(H_); }
void CPU::opcode_95() { opcode_sub(L_); }
void CPU::opcode_96() { opcode_sub(Address(HL_)); }
void CPU::opcode_97() { opcode_sub(A_); }
void CPU::opcode_98() { opcode_sbc(B_); }
void CPU::opcode_99() { opcode_sbc(C_); }
void CPU::opcode_9a() { opcode_sbc(D_); }
void CPU::opcode_9b() { opcode_sbc(E_); }
void CPU::opcode_9c() { opcode_sbc(H_); }
void CPU::opcode_9d() { opcode_sbc(L_); }
void CPU::opcode_9e() { opcode_sbc(Address(HL_)); }
void CPU::opcode_9f() { opcode_sbc(A_); }

void CPU::opcode_a0() { opcode_and(B_); }
void CPU::opcode_a1() { opcode_and(C_); }
void CPU::opcode_a2() { opcode_and(D_); }
void CPU::opcode_a3() { opcode_and(E_); }
void CPU::opcode_a4() { opcode_and(H_); }
void CPU::opcode_a5() { opcode_and(L_); }
void CPU::opcode_a6() { opcode_and(Address(HL_)); }
void CPU::opcode_a7() { opcode_and(A_); }
void CPU::opcode_a8() { opcode_xor(B_); }
void CPU::opcode_a9() { opcode_xor(C_); }
void CPU::opcode_aa() { opcode_xor(D_); }
void CPU::opcode_ab() { opcode_xor(E_); }
void CPU::opcode_ac() { opcode_xor(H_); }
void CPU::opcode_ad() { opcode_xor(L_); }
void CPU::opcode_ae() { opcode_xor(Address(HL_)); }
void CPU::opcode_af() { opcode_xor(A_); }

void CPU::opcode_b0() { opcode_or(B_); }
void CPU::opcode_b1() { opcode_or(C_); }
void CPU::opcode_b2() { opcode_or(D_); }
void CPU::opcode_b3() { opcode_or(E_); }
void CPU::opcode_b4() { opcode_or(H_); }
void CPU::opcode_b5() { opcode_or(L_); }
void CPU::opcode_b6() { opcode_or(Address(HL_)); }
void CPU::opcode_b7() { opcode_or(A_); }
void CPU::opcode_b8() { opcode_cp(B_); }
void CPU::opcode_b9() { opcode_cp(C_); }
void CPU::opcode_ba() { opcode_cp(D_); }
void CPU::opcode_bb() { opcode_cp(E_); }
void CPU::opcode_bc() { opcode_cp(H_); }
void CPU::opcode_bd() { opcode_cp(L_); }
void CPU::opcode_be() { opcode_cp(Address(HL_)); }
void CPU::opcode_bf() { opcode_cp(A_); }

void CPU::opcode_c0() { opcode_ret(Condition::NZ); }
void CPU::opcode_c1() { opcode_pop(BC_); }
void CPU::opcode_c2() { opcode_jp(Condition::NZ); }
void CPU::opcode_c3() { opcode_jp(); }
void CPU::opcode_c4() { opcode_call(Condition::NZ); }
void CPU::opcode_c5() { opcode_push(BC_); }
void CPU::opcode_c6() { opcode_add(); }
void CPU::opcode_c7() { opcode_rst(0); }
void CPU::opcode_c8() { opcode_ret(Condition::Z); }
void CPU::opcode_c9() { opcode_ret(); }
void CPU::opcode_ca() { opcode_jp(Condition::Z); }
void CPU::opcode_cb() {  }
void CPU::opcode_cc() { opcode_call(Condition::Z); }
void CPU::opcode_cd() { opcode_call(); }
void CPU::opcode_ce() { opcode_adc(); }
void CPU::opcode_cf() { opcode_rst(1); }

void CPU::opcode_d0() { opcode_ret(Condition::NC); }
void CPU::opcode_d1() { opcode_pop(DE_); }
void CPU::opcode_d2() { opcode_jp(Condition::NC); }
void CPU::opcode_d3() {  }
void CPU::opcode_d4() { opcode_call(Condition::NC); }
void CPU::opcode_d5() { opcode_push(DE_); }
void CPU::opcode_d6() { opcode_sub(); }
void CPU::opcode_d7() { opcode_rst(2); }
void CPU::opcode_d8() { opcode_ret(Condition::C); }
void CPU::opcode_d9() { opcode_reti(); }
void CPU::opcode_da() { opcode_jp(Condition::C); }
void CPU::opcode_db() {  }
void CPU::opcode_dc() { opcode_call(Condition::C); }
void CPU::opcode_dd() {  }
void CPU::opcode_de() { opcode_sbc(); }
void CPU::opcode_df() { opcode_rst(3); }

void CPU::opcode_e0() { opcode_ldh_from_A(); }
void CPU::opcode_e1() { opcode_pop(HL_); }
void CPU::opcode_e2() { opcode_ldh_from_A(C_); }
void CPU::opcode_e3() {  }
void CPU::opcode_e4() {  }
void CPU::opcode_e5() { opcode_push(HL_); }
void CPU::opcode_e6() { opcode_and(); }
void CPU::opcode_e7() { opcode_rst(4); }
void CPU::opcode_e8() { opcode_add_hl(); }
void CPU::opcode_e9() { opcode_jp(HL_); }
void CPU::opcode_ea() { opcode_ld(A_); }
void CPU::opcode_eb() {  }
void CPU::opcode_ec() {  }
void CPU::opcode_ed() {  }
void CPU::opcode_ee() { opcode_xor(); }
void CPU::opcode_ef() { opcode_rst(5); }

void CPU::opcode_f0() { opcode_ldh_to_A(); }
void CPU::opcode_f1() { opcode_pop(AF_); }
void CPU::opcode_f2() { opcode_ldh_to_A(C_); }
void CPU::opcode_f3() { opcode_di(); }
void CPU::opcode_f4() {  }
void CPU::opcode_f5() { opcode_push(AF_); }
void CPU::opcode_f6() { opcode_or(); }
void CPU::opcode_f7() { opcode_rst(6); }
void CPU::opcode_f8() { opcode_ld_hl(); }
void CPU::opcode_f9() { opcode_ld(SP_, HL_); }
void CPU::opcode_fa() { opcode_ld_get_address(A_); }
void CPU::opcode_fb() { opcode_ei(); }
void CPU::opcode_fc() {  }
void CPU::opcode_fd() {  }
void CPU::opcode_fe() { opcode_cp(); }
void CPU::opcode_ff() { opcode_rst(7); }



// Implementing functions from opcode_cb_00 to opcode_cb_ff in CPU namespace
void CPU::opcode_cb_00() { opcode_rlc(B_); }
void CPU::opcode_cb_01() { opcode_rlc(C_); }
void CPU::opcode_cb_02() { opcode_rlc(D_); }
void CPU::opcode_cb_03() { opcode_rlc(E_); }
void CPU::opcode_cb_04() { opcode_rlc(H_); }
void CPU::opcode_cb_05() { opcode_rlc(L_); }
void CPU::opcode_cb_06() { opcode_rlc(Address(HL_)); }
void CPU::opcode_cb_07() { opcode_rlc(A_); }
void CPU::opcode_cb_08() { opcode_rrc(B_); }
void CPU::opcode_cb_09() { opcode_rrc(C_); }
void CPU::opcode_cb_0a() { opcode_rrc(D_); }
void CPU::opcode_cb_0b() { opcode_rrc(E_); }
void CPU::opcode_cb_0c() { opcode_rrc(H_); }
void CPU::opcode_cb_0d() { opcode_rrc(L_); }
void CPU::opcode_cb_0e() { opcode_rrc(Address(HL_)); }
void CPU::opcode_cb_0f() { opcode_rrc(A_); }

void CPU::opcode_cb_10() { opcode_rl(B_); }
void CPU::opcode_cb_11() { opcode_rl(C_);}
void CPU::opcode_cb_12() { opcode_rl(D_); }
void CPU::opcode_cb_13() { opcode_rl(E_); }
void CPU::opcode_cb_14() { opcode_rl(H_); }
void CPU::opcode_cb_15() { opcode_rl(L_); }
void CPU::opcode_cb_16() { opcode_rl(Address(HL_)); }
void CPU::opcode_cb_17() { opcode_rl(A_); }
void CPU::opcode_cb_18() { opcode_rr(B_); }
void CPU::opcode_cb_19() { opcode_rr(C_); }
void CPU::opcode_cb_1a() { opcode_rr(D_); }
void CPU::opcode_cb_1b() { opcode_rr(E_); }
void CPU::opcode_cb_1c() { opcode_rr(H_); }
void CPU::opcode_cb_1d() { opcode_rr(L_); }
void CPU::opcode_cb_1e() { opcode_rr(Address(HL_)); }
void CPU::opcode_cb_1f() { opcode_rr(A_); }

void CPU::opcode_cb_20() { opcode_sla(B_); } 
void CPU::opcode_cb_21() { opcode_sla(C_); } 
void CPU::opcode_cb_22() { opcode_sla(D_); } 
void CPU::opcode_cb_23() { opcode_sla(E_); } 
void CPU::opcode_cb_24() { opcode_sla(H_); } 
void CPU::opcode_cb_25() { opcode_sla(L_); } 
void CPU::opcode_cb_26() { opcode_sla(Address(HL_)); }
void CPU::opcode_cb_27() { opcode_sla(A_); } 
void CPU::opcode_cb_28() { opcode_sra(B_); } 
void CPU::opcode_cb_29() { opcode_sra(C_); } 
void CPU::opcode_cb_2a() { opcode_sra(D_); } 
void CPU::opcode_cb_2b() { opcode_sra(E_); } 
void CPU::opcode_cb_2c() { opcode_sra(H_); } 
void CPU::opcode_cb_2d() { opcode_sra(L_); } 
void CPU::opcode_cb_2e() { opcode_sra(Address(HL_)); } 
void CPU::opcode_cb_2f() { opcode_sra(A_); } 

void CPU::opcode_cb_30() { opcode_swap(B_); }
void CPU::opcode_cb_31() { opcode_swap(C_); }
void CPU::opcode_cb_32() { opcode_swap(D_); }
void CPU::opcode_cb_33() { opcode_swap(E_); }
void CPU::opcode_cb_34() { opcode_swap(H_); }
void CPU::opcode_cb_35() { opcode_swap(L_); }
void CPU::opcode_cb_36() { opcode_swap(Address(HL_)); }
void CPU::opcode_cb_37() { opcode_swap(A_); }
void CPU::opcode_cb_38() { opcode_srl(B_); }
void CPU::opcode_cb_39() { opcode_srl(C_); }
void CPU::opcode_cb_3a() { opcode_srl(D_); }
void CPU::opcode_cb_3b() { opcode_srl(E_); }
void CPU::opcode_cb_3c() { opcode_srl(H_); }
void CPU::opcode_cb_3d() { opcode_srl(L_); }
void CPU::opcode_cb_3e() { opcode_srl(Address(HL_)); }
void CPU::opcode_cb_3f() { opcode_srl(A_); }

void CPU::opcode_cb_40() { opcode_bit(0, B_); }
void CPU::opcode_cb_41() { opcode_bit(0, C_); }
void CPU::opcode_cb_42() { opcode_bit(0, D_); }
void CPU::opcode_cb_43() { opcode_bit(0, E_); }
void CPU::opcode_cb_44() { opcode_bit(0, H_); }
void CPU::opcode_cb_45() { opcode_bit(0, L_); }
void CPU::opcode_cb_46() { opcode_bit(0, Address(HL_)); }
void CPU::opcode_cb_47() { opcode_bit(0, A_); }
void CPU::opcode_cb_48() { opcode_bit(1, B_); }
void CPU::opcode_cb_49() { opcode_bit(1, C_); }
void CPU::opcode_cb_4a() { opcode_bit(1, D_); }
void CPU::opcode_cb_4b() { opcode_bit(1, E_); }
void CPU::opcode_cb_4c() { opcode_bit(1, H_); }
void CPU::opcode_cb_4d() { opcode_bit(1, L_); }
void CPU::opcode_cb_4e() { opcode_bit(1, Address(HL_)); }
void CPU::opcode_cb_4f() { opcode_bit(1, A_); }

void CPU::opcode_cb_50() { opcode_bit(2, B_); }
void CPU::opcode_cb_51() { opcode_bit(2, C_); }
void CPU::opcode_cb_52() { opcode_bit(2, D_); }
void CPU::opcode_cb_53() { opcode_bit(2, E_); }
void CPU::opcode_cb_54() { opcode_bit(2, H_); }
void CPU::opcode_cb_55() { opcode_bit(2, L_); }
void CPU::opcode_cb_56() { opcode_bit(2, Address(HL_)); }
void CPU::opcode_cb_57() { opcode_bit(2, A_); }
void CPU::opcode_cb_58() { opcode_bit(3, B_); }
void CPU::opcode_cb_59() { opcode_bit(3, C_); }
void CPU::opcode_cb_5a() { opcode_bit(3, D_); }
void CPU::opcode_cb_5b() { opcode_bit(3, E_); }
void CPU::opcode_cb_5c() { opcode_bit(3, H_); }
void CPU::opcode_cb_5d() { opcode_bit(3, L_); }
void CPU::opcode_cb_5e() { opcode_bit(3, Address(HL_)); }
void CPU::opcode_cb_5f() { opcode_bit(3, A_); }

void CPU::opcode_cb_60() { opcode_bit(4, B_); }
void CPU::opcode_cb_61() { opcode_bit(4, C_); }
void CPU::opcode_cb_62() { opcode_bit(4, D_); }
void CPU::opcode_cb_63() { opcode_bit(4, E_); }
void CPU::opcode_cb_64() { opcode_bit(4, H_); }
void CPU::opcode_cb_65() { opcode_bit(4, L_); }
void CPU::opcode_cb_66() { opcode_bit(4, Address(HL_)); }
void CPU::opcode_cb_67() { opcode_bit(4, A_); }
void CPU::opcode_cb_68() { opcode_bit(5, B_); }
void CPU::opcode_cb_69() { opcode_bit(5, C_); }
void CPU::opcode_cb_6a() { opcode_bit(5, D_); }
void CPU::opcode_cb_6b() { opcode_bit(5, E_); }
void CPU::opcode_cb_6c() { opcode_bit(5, H_); }
void CPU::opcode_cb_6d() { opcode_bit(5, L_); }
void CPU::opcode_cb_6e() { opcode_bit(5, Address(HL_)); }
void CPU::opcode_cb_6f() { opcode_bit(5, A_); }

void CPU::opcode_cb_70() { opcode_bit(6, B_); }
void CPU::opcode_cb_71() { opcode_bit(6, C_); }
void CPU::opcode_cb_72() { opcode_bit(6, D_); }
void CPU::opcode_cb_73() { opcode_bit(6, E_); }
void CPU::opcode_cb_74() { opcode_bit(6, H_); }
void CPU::opcode_cb_75() { opcode_bit(6, L_); }
void CPU::opcode_cb_76() { opcode_bit(6, Address(HL_)); }
void CPU::opcode_cb_77() { opcode_bit(6, A_); }
void CPU::opcode_cb_78() { opcode_bit(7, B_); }
void CPU::opcode_cb_79() { opcode_bit(7, C_); }
void CPU::opcode_cb_7a() { opcode_bit(7, D_); }
void CPU::opcode_cb_7b() { opcode_bit(7, E_); }
void CPU::opcode_cb_7c() { opcode_bit(7, H_); }
void CPU::opcode_cb_7d() { opcode_bit(7, L_); }
void CPU::opcode_cb_7e() { opcode_bit(7, Address(HL_)); }
void CPU::opcode_cb_7f() { opcode_bit(7, A_); }

void CPU::opcode_cb_80() { opcode_res(0, B_); }
void CPU::opcode_cb_81() { opcode_res(0, C_); }
void CPU::opcode_cb_82() { opcode_res(0, D_); }
void CPU::opcode_cb_83() { opcode_res(0, E_); }
void CPU::opcode_cb_84() { opcode_res(0, H_); }
void CPU::opcode_cb_85() { opcode_res(0, L_); }
void CPU::opcode_cb_86() { opcode_res(0, Address(HL_)); }
void CPU::opcode_cb_87() { opcode_res(0, A_); }
void CPU::opcode_cb_88() { opcode_res(1, B_); }
void CPU::opcode_cb_89() { opcode_res(1, C_); }
void CPU::opcode_cb_8a() { opcode_res(1, D_); }
void CPU::opcode_cb_8b() { opcode_res(1, E_); }
void CPU::opcode_cb_8c() { opcode_res(1, H_); }
void CPU::opcode_cb_8d() { opcode_res(1, L_); }
void CPU::opcode_cb_8e() { opcode_res(1, Address(HL_)); }
void CPU::opcode_cb_8f() { opcode_res(1, A_); }

void CPU::opcode_cb_90() { opcode_res(2, B_); }
void CPU::opcode_cb_91() { opcode_res(2, C_); }
void CPU::opcode_cb_92() { opcode_res(2, D_); }
void CPU::opcode_cb_93() { opcode_res(2, E_); }
void CPU::opcode_cb_94() { opcode_res(2, H_); }
void CPU::opcode_cb_95() { opcode_res(2, L_); }
void CPU::opcode_cb_96() { opcode_res(2, Address(HL_)); }
void CPU::opcode_cb_97() { opcode_res(2, A_); }
void CPU::opcode_cb_98() { opcode_res(3, B_); }
void CPU::opcode_cb_99() { opcode_res(3, C_); }
void CPU::opcode_cb_9a() { opcode_res(3, D_); }
void CPU::opcode_cb_9b() { opcode_res(3, E_); }
void CPU::opcode_cb_9c() { opcode_res(3, H_); }
void CPU::opcode_cb_9d() { opcode_res(3, L_); }
void CPU::opcode_cb_9e() { opcode_res(3, Address(HL_)); }
void CPU::opcode_cb_9f() { opcode_res(3, A_); }

void CPU::opcode_cb_a0() { opcode_res(4, B_); }
void CPU::opcode_cb_a1() { opcode_res(4, C_); }
void CPU::opcode_cb_a2() { opcode_res(4, D_); }
void CPU::opcode_cb_a3() { opcode_res(4, E_); }
void CPU::opcode_cb_a4() { opcode_res(4, H_); }
void CPU::opcode_cb_a5() { opcode_res(4, L_); }
void CPU::opcode_cb_a6() { opcode_res(4, Address(HL_)); }
void CPU::opcode_cb_a7() { opcode_res(4, A_); }
void CPU::opcode_cb_a8() { opcode_res(5, B_); }
void CPU::opcode_cb_a9() { opcode_res(5, C_); }
void CPU::opcode_cb_aa() { opcode_res(5, D_); }
void CPU::opcode_cb_ab() { opcode_res(5, E_); }
void CPU::opcode_cb_ac() { opcode_res(5, H_); }
void CPU::opcode_cb_ad() { opcode_res(5, L_); }
void CPU::opcode_cb_ae() { opcode_res(5, Address(HL_)); }
void CPU::opcode_cb_af() { opcode_res(5, A_); }

void CPU::opcode_cb_b0() { opcode_res(6, B_); }
void CPU::opcode_cb_b1() { opcode_res(6, C_); }
void CPU::opcode_cb_b2() { opcode_res(6, D_); }
void CPU::opcode_cb_b3() { opcode_res(6, E_); }
void CPU::opcode_cb_b4() { opcode_res(6, H_); }
void CPU::opcode_cb_b5() { opcode_res(6, L_); }
void CPU::opcode_cb_b6() { opcode_res(6, Address(HL_)); }
void CPU::opcode_cb_b7() { opcode_res(6, A_); }
void CPU::opcode_cb_b8() { opcode_res(7, B_); }
void CPU::opcode_cb_b9() { opcode_res(7, C_); }
void CPU::opcode_cb_ba() { opcode_res(7, D_); }
void CPU::opcode_cb_bb() { opcode_res(7, E_); }
void CPU::opcode_cb_bc() { opcode_res(7, H_); }
void CPU::opcode_cb_bd() { opcode_res(7, L_); }
void CPU::opcode_cb_be() { opcode_res(7, Address(HL_)); }
void CPU::opcode_cb_bf() { opcode_res(7, A_); }

void CPU::opcode_cb_c0() { opcode_set(0, B_); }
void CPU::opcode_cb_c1() { opcode_set(0, C_); }
void CPU::opcode_cb_c2() { opcode_set(0, D_); }
void CPU::opcode_cb_c3() { opcode_set(0, E_); }
void CPU::opcode_cb_c4() { opcode_set(0, H_); }
void CPU::opcode_cb_c5() { opcode_set(0, L_); }
void CPU::opcode_cb_c6() { opcode_set(0, Address(HL_)); }
void CPU::opcode_cb_c7() { opcode_set(0, A_); }
void CPU::opcode_cb_c8() { opcode_set(1, B_); }
void CPU::opcode_cb_c9() { opcode_set(1, C_); }
void CPU::opcode_cb_ca() { opcode_set(1, D_); }
void CPU::opcode_cb_cb() { opcode_set(1, E_); }
void CPU::opcode_cb_cc() { opcode_set(1, H_); }
void CPU::opcode_cb_cd() { opcode_set(1, L_); }
void CPU::opcode_cb_ce() { opcode_set(1, Address(HL_)); }
void CPU::opcode_cb_cf() { opcode_set(1, A_); }

void CPU::opcode_cb_d0() { opcode_set(2, B_); }
void CPU::opcode_cb_d1() { opcode_set(2, C_); }
void CPU::opcode_cb_d2() { opcode_set(2, D_); }
void CPU::opcode_cb_d3() { opcode_set(2, E_); }
void CPU::opcode_cb_d4() { opcode_set(2, H_); }
void CPU::opcode_cb_d5() { opcode_set(2, L_); }
void CPU::opcode_cb_d6() { opcode_set(2, Address(HL_)); }
void CPU::opcode_cb_d7() { opcode_set(2, A_); }
void CPU::opcode_cb_d8() { opcode_set(3, B_); }
void CPU::opcode_cb_d9() { opcode_set(3, C_); }
void CPU::opcode_cb_da() { opcode_set(3, D_); }
void CPU::opcode_cb_db() { opcode_set(3, E_); }
void CPU::opcode_cb_dc() { opcode_set(3, H_); }
void CPU::opcode_cb_dd() { opcode_set(3, L_); }
void CPU::opcode_cb_de() { opcode_set(3, Address(HL_)); }
void CPU::opcode_cb_df() { opcode_set(3, A_); }

void CPU::opcode_cb_e0() { opcode_set(4, B_); }
void CPU::opcode_cb_e1() { opcode_set(4, C_); }
void CPU::opcode_cb_e2() { opcode_set(4, D_); }
void CPU::opcode_cb_e3() { opcode_set(4, E_); }
void CPU::opcode_cb_e4() { opcode_set(4, H_); }
void CPU::opcode_cb_e5() { opcode_set(4, L_); }
void CPU::opcode_cb_e6() { opcode_set(4, Address(HL_)); }
void CPU::opcode_cb_e7() { opcode_set(5, A_); }
void CPU::opcode_cb_e8() { opcode_set(5, B_); }
void CPU::opcode_cb_e9() { opcode_set(5, C_); }
void CPU::opcode_cb_ea() { opcode_set(5, D_); }
void CPU::opcode_cb_eb() { opcode_set(5, E_); }
void CPU::opcode_cb_ec() { opcode_set(5, H_); }
void CPU::opcode_cb_ed() { opcode_set(5, L_); }
void CPU::opcode_cb_ee() { opcode_set(5, Address(HL_)); }
void CPU::opcode_cb_ef() { opcode_set(5, A_); }

void CPU::opcode_cb_f0() { opcode_set(6, B_); }
void CPU::opcode_cb_f1() { opcode_set(6, C_); }
void CPU::opcode_cb_f2() { opcode_set(6, D_); }
void CPU::opcode_cb_f3() { opcode_set(6, E_); }
void CPU::opcode_cb_f4() { opcode_set(6, H_); }
void CPU::opcode_cb_f5() { opcode_set(6, L_); }
void CPU::opcode_cb_f6() { opcode_set(6, Address(HL_)); }
void CPU::opcode_cb_f7() { opcode_set(6, A_); }
void CPU::opcode_cb_f8() { opcode_set(7, B_); }
void CPU::opcode_cb_f9() { opcode_set(7, C_); }
void CPU::opcode_cb_fa() { opcode_set(7, D_); }
void CPU::opcode_cb_fb() { opcode_set(7, E_); }
void CPU::opcode_cb_fc() { opcode_set(7, H_); }
void CPU::opcode_cb_fd() { opcode_set(7, L_); }
void CPU::opcode_cb_fe() { opcode_set(7, Address(HL_)); }
void CPU::opcode_cb_ff() { opcode_set(7, A_); }
