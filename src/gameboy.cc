#include "gameboy.h"

GameBoy::GameBoy():
    mmu(),
    cpu(*this)
{
}