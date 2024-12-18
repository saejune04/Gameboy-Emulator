#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "memory/mmu.h"
#include "cpu/cpu.h"

class GameBoy {
    public:
        GameBoy();

    private:
        friend class MMU;
        MMU mmu;

        friend class CPU;
        CPU cpu;
    
};

#endif