#ifndef REGISTERS_H
#define REGISTERS_H

#include <cstdint>

// General Register template
template <typename T>
class Register {
    public:
        Register() = default;
        virtual ~Register() = default;
        
        virtual void set_val(T value) = 0;
        virtual T get_val() const = 0;
        virtual void increment() = 0;
        virtual void decrement() = 0;
};

// 8-bit register
class ByteRegister : public Register<uint8_t> {
    public:
        void set_val(uint8_t value) override;
        uint8_t get_val() const override;
        void increment() override;
        void decrement() override;

    protected:
        uint8_t val_ = 0x0;
};

// Flag register
// Z, N, H, C, 0, 0, 0, 0
// Z: Zero Flag, N: Subtract Flag, H: Half-Carry Flag, C: Carry Flag
class FlagRegister : public ByteRegister {
    public:
        void set_zero_flag(bool val);
        void set_subtract_flag(bool val);
        void set_half_carry_flag(bool val);
        void set_carry_flag(bool val);

        uint8_t get_zero_flag() const;
        uint8_t get_subtract_flag() const;
        uint8_t get_half_carry_flag() const;
        uint8_t get_carry_flag() const;

    private:
        
};

// 16-bit register
class WordRegister : public Register<uint16_t> {
    public:
        virtual void set_val(uint16_t value) override;
        virtual uint16_t get_val() const override;
        virtual void increment() override;
        virtual void decrement() override;
        virtual uint8_t high_byte() const;
        virtual uint8_t low_byte() const;

    private:
        uint16_t val_ = 0x0;

};

// Pair of two 8-bit registers
class PairRegister : public WordRegister {
    public:
        PairRegister() = delete;
        PairRegister(ByteRegister& high_byte, ByteRegister& low_byte): high_byte_(high_byte), low_byte_(low_byte) {};
        
        void set_val(uint16_t value) override;
        uint16_t get_val() const override;
        void increment() override;
        void decrement() override;
        uint8_t high_byte() const override;
        uint8_t low_byte() const override;

    private:
        ByteRegister& high_byte_;
        ByteRegister& low_byte_;
};


#endif