#include <stdio.h>
#include <stdlib.h>


struct CPU {
    using Byte = unsigned char;
    using Word = unsigned short;
    
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

};

int main() {
    CPU cpu; //instance of cpu
    return 0;
}