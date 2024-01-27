#include <stdio.h>
#include <stdlib.h>

using Byte = unsigned char;
using Word = unsigned short;
using u32 = unsigned int;

struct Memory {
    static constexpr u32 MAX_MEM = 1024*64;
    Byte Data[MAX_MEM];

    void Initialize() {
        for (u32 i = 0; i < MAX_MEM; i++) {
            Data[i] = 0;
        }
    }

    //Read byte
    Byte operator[] (u32 Address) const {
        return Data[Address];
    }
    //Write byte
    Byte& operator[] (u32 Address) {
        return Data[Address];
    }
};

struct CPU {
    
    Word PC; //program counter
    Word SP; //stack pointer
    
    Byte A, X, Y; //Registers X, Y, and Accumulator

    //Processor Status:
    // As instruction are executed, set of processor flags are set or clear
    // to record the result of each operation. Special status register hold
    // some control flags. Each flag has one single bit within the reg.
    Byte C : 1; //Carry Flag: Last operation caused an overflow from bit 7 to 0
    Byte Z : 1; //Zero Flag: Last operation was zero
    Byte I : 1; //Interrupt Disable: "Set Interrupt Disable" is set 
    Byte D : 1; //Decimal Mode: Obeys rules of binary coded decimal arithmetic
    Byte B : 1; //Break Command: BRK instruction is executed
    Byte V : 1; //Overflow : Set when aruthmetic operation result has yield invalid complements
    Byte N : 1; //Negative
    
    void Reset( Memory& memory) {
        SP = 0x0100;
        PC = 0xFFFC;
        C = Z = I = B = V = N = D = 0;
        A = X = Y = 0;

    }
    Byte Fetch (u32& Cycles, Memory& memory) {
        Byte Data = memory[PC];
        PC++;
        Cycles--; 
        return Data;
    }
    //OPCODES
    static constexpr Byte
        LDA_IMMEDIATE = 0xA9;
    void Execute(u32 Cycles, Memory& memory) {
        while (Cycles > 0) {
            Byte Instruction = Fetch(Cycles, memory);
            switch (Instruction) {
                case LDA_IMMEDIATE:{
                    Byte Value = Fetch(Cycles, memory);
                    A = Value;
                    if (A == 0) {
                        Z = 1; 
                    }
                    if (A & 0b10000000 != 0) {
                        N = 1;
                    }
                }
                break;
                default: {
                    printf("Instruction is not handled");
                } break;
            }
        }
    }
};

int main() {
    CPU cpu; //instance of cpu
    Memory mem; 
    cpu.Reset(mem);
    mem[0xFFFC] = CPU::LDA_IMMEDIATE;
    mem[0xFFFD] = 0x42;
    cpu.Execute(3, mem);
    return 0;
}