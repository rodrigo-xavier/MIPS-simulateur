#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <stdio.h>
#include <stdint.h>

#define MEM_SIZE 4096

/** @brief Opcodes assembly MIPS, e suas respectivas instruções
 *  @details Cada Opcode descrito neste enum, representa uma
 *  instrução no assembly MIPS
*/
enum OPCODES
{
    EXT = 0x00,
    J = 0x02,
    JAL = 0x03,
    BEQ = 0x04,
    BNE = 0x05,
    BLEZ = 0x06,
    BGTZ = 0x07,
    ADDI = 0x08,
    ADDIU = 0x09,
    SLTI = 0x0A,
    SLTIU = 0x0B,
    ANDI = 0x0C,
    ORI = 0x0D,
    XORI = 0x0E,
    LUI = 0x0F,
    LB = 0x20,
    LH = 0x21,
    LW = 0x23,
    LBU = 0x24,
    LHU = 0x25,
    SB = 0x28,
    SH = 0x29,
    SW = 0x2B,
};

/** @brief Funct do assembly MIPS, e suas respectivas instruções
 *  @details Cada Funct descrito neste enum, representa uma
 *  instrução no assembly MIPS
*/
enum FUNCT
{
    SLL = 0x00,
    SRL = 0x02,
    SRA = 0x03,
    JR = 0x08,
    SYSCALL = 0x0C,
    MFHI = 0x10,
    MFLO = 0x12,
    MULT = 0x18,
    DIV = 0x1A,
    ADD = 0x20,
    ADDU = 0x21,
    SUB = 0x22,
    AND = 0x24,
    OR = 0x25,
    XOR = 0x26,
    NOR = 0x27,
    SLT = 0x2A,
    SLTU = 0x2B,
};

/** @brief Struct que define o tipo uint5_t
 *  @details O tipo uint5_t é definido como um tipo que
 *  contém uma variável unsigned int value de 5 bits 
*/
typedef struct uint5_t
{
    unsigned int value : 5;
} uint5_t;

/** @brief Struct que define o tipo uint6_t
 *  @details O tipo uint6_t é definido como um tipo que
 *  contém uma variável unsigned int value de 6 bits 
*/
typedef struct uint6_t
{
    unsigned int value : 6;
} uint6_t;

/** @brief Struct que define o tipo uint26_t
 *  @details O tipo uint26_t é definido como um tipo que
 *  contém uma variável unsigned int value de 26 bits 
*/
typedef struct int26_t
{
    unsigned int value : 26;
} int26_t;

/** @brief Enum que define o tipo bool
 *  @details Como o tipo bool não existe em C99, houve
 *  a necessidade de criar um enum que representasse esse tipo
*/
typedef enum
{
    false,
    true
} bool;

/** @brief Variáveis globais
 *  @details Como são utilizadas muitas variáveis globais
 *  no projeto, houve a necessidade de criar um bloco de 
 *  código que contesse todas as definições desses tipos
 *  de variáveis
*/
uint5_t rs, rt, rd, shamt;
uint6_t op, funct;
int32_t k16;
int26_t k26;
uint32_t pc, ri, hi, lo, epc;
int32_t mem[MEM_SIZE], reg[32];

bool DEBUG;
int counter;
char DIR[100];

void debug(void);
void debug_opcode(int);
void debug_funct(int);

#endif