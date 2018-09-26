#include "../include/global.h"

/** @brief Função que chama as funções de depuração
 *  @details Se op for 0x00, mostra o conteúdo de funct,
 *  caso contrário, mostra o conteúdo de op.
*/
void debug(void)
{
    if (DEBUG)
    {
        if (op.value == EXT)
            debug_funct(funct.value);
        else
            debug_opcode(op.value);

        getchar();
    }
}

/** @brief Função que mostra informações uteis das instruções de opcode
*/
void debug_opcode(int instruction)
{
    switch (instruction)
    {
    case J:
        printf("j \t\t [pc] = \t d [%d] \t h [%08x]", pc, pc);
        break;

    case JAL:
        printf("jal \t\t [pc] = \t d [%d] \t h [%08x]", pc, pc);
        break;

    case BEQ:
        printf("beq \t\t [pc] = \t d [%d] \t h [%08x]", pc, pc);
        break;

    case BNE:
        printf("bne \t\t [pc] = \t d [%d] \t h [%08x]", pc, pc);
        break;

    case BLEZ:
        printf("blez \t\t [pc] = \t d [%d] \t h [%08x]", pc, pc);
        break;

    case BGTZ:
        printf("bgtz \t\t [pc] = \t d [%d] \t h [%08x]", pc, pc);
        break;

    case ADDI:
        printf("addi \t\t reg[%d] = \t d [%d] \t h [%08x]", rt.value, reg[rt.value], reg[rt.value]);
        break;

    case ADDIU:
        printf("addiu \t\t reg[%d] = \t d [%d] \t\t h [%08x]", rt.value, reg[rt.value], reg[rt.value]);
        break;

    case SLTI:
        printf("slti \t\t reg[%d] = \t d [%d] \t h [%08x]", rt.value, reg[rt.value], reg[rt.value]);
        break;

    case SLTIU:
        printf("sltiu \t\t reg[%d] = \t d [%d] \t\t h [%08x]", rt.value, reg[rt.value], reg[rt.value]);
        break;

    case ANDI:
        printf("andi \t\t reg[%d] = \t d [%d] \t h [%08x]", rt.value, reg[rt.value], reg[rt.value]);
        break;

    case ORI:
        printf("ori \t\t reg[%d] = \t d [%d] \t\t h [%08x]", rt.value, reg[rt.value], reg[rt.value]);
        break;

    case XORI:
        printf("xori \t\t reg[%d] = \t d [%d] \t h [%08x]", rt.value, reg[rt.value], reg[rt.value]);
        break;

    case LUI:
        printf("lui \t\t reg[%d] = \t d [%d] \t h [%08x]", rt.value, reg[rt.value], reg[rt.value]);
        break;

    case LB:
        printf("lb \t\t reg[%d] = \t d [%d] \t h [%08x]", rt.value, reg[rt.value], reg[rt.value]);
        break;

    case LH:
        printf("lh \t\t reg[%d] = \t d [%d] \t h [%08x]", rt.value, reg[rt.value], reg[rt.value]);
        break;

    case LW:
        printf("lw \t\t reg[%d] = \t d [%d] \t h [%08x]", rt.value, reg[rt.value], reg[rt.value]);
        break;

    case LBU:
        printf("lbu \t\t reg[%d] = \t d [%d] \t h [%08x]", rt.value, reg[rt.value], reg[rt.value]);
        break;

    case LHU:
        printf("lhu \t\t reg[%d] = \t d [%d] \t h [%08x]", rt.value, reg[rt.value], reg[rt.value]);
        break;

    case SB:
        printf("sb \t\t reg[%d] = \t d [%d] \t h [%08x]", k16, reg[rt.value], reg[rt.value]);
        break;

    case SH:
        printf("sh \t\t reg[%d] = \t d [%d] \t h [%08x]", rs.value, reg[rs.value], reg[rs.value]);
        break;

    case SW:
        printf("sw \t\t reg[%d] = \t d [%d] \t h [%08x]", rs.value, reg[rs.value], reg[rs.value]);
        break;
    }
}

/** @brief Função que mostra informações úteis de funct
*/
void debug_funct(int instruction)
{
    switch (instruction)
    {
    case SLL:
        printf("sll \t\t [rd] = \t d [%d] \t\t h [%08x]", rd.value, rd.value);
        break;

    case SRL:
        printf("srl \t\t [rd] = \t d [%d] \t h [%08x]", rd.value, rd.value);
        break;

    case SRA:
        printf("sra \t\t reg[%d] = \t d [%d] \t h [%08x]", rd.value, reg[rd.value], reg[rd.value]);
        break;

    case JR:
        printf("sra \t\t [pc] = \t d [%d] \t h [%08x]", pc, pc);
        break;

    case SYSCALL:
        printf("syscall \t reg[2] = \t d [%d] \t\t h [%08x]", reg[2], reg[2]);
        break;

    case MFHI:
        printf("mfhi \t\t reg[%d] = \t d [%d] \t h [%08x]", rd.value, reg[rd.value], reg[rd.value]);
        break;

    case MFLO:
        printf("mflo \t\t reg[%d] = \t d [%d] \t h [%08x]", rd.value, reg[rd.value], reg[rd.value]);
        break;

    case MULT:
        printf("mult \t\t [hi] = \t d [%d] \t h [%08x]\n", hi, hi);
        printf("mult \t\t [lo] = \t d [%d] \t h [%08x]", lo, lo);
        break;

    case DIV:
        printf("div \t\t [hi] = \t d [%d] \t h [%08x]\n", hi, hi);
        printf("div \t\t [lo] = \t d [%d] \t h [%08x]", lo, lo);
        break;

    case ADD:
        printf("add \t\t reg[%d] = \t d [%d] \t\t h [%08x]", rd.value, reg[rd.value], reg[rd.value]);
        break;

    case ADDU:
        printf("addu \t\t reg[%d] = \t d [%d] \t h [%08x]", rd.value, reg[rd.value], reg[rd.value]);
        break;

    case SUB:
        printf("sub \t\t reg[%d] = \t d [%d] \t h [%08x]", rd.value, reg[rd.value], reg[rd.value]);
        break;

    case AND:
        printf("and \t\t reg[%d] = \t d [%d] \t h [%08x]", rd.value, reg[rd.value], reg[rd.value]);
        break;

    case OR:
        printf("or \t\t reg[%d] = \t d [%d] \t h [%08x]", rd.value, reg[rd.value], reg[rd.value]);
        break;

    case XOR:
        printf("xor \t\t reg[%d] = \t d [%d] \t h [%08x]", rd.value, reg[rd.value], reg[rd.value]);
        break;

    case NOR:
        printf("nor \t\t reg[%d] = \t d [%d] \t h [%08x]", rd.value, reg[rd.value], reg[rd.value]);
        break;

    case SLT:
        printf("slt \t\t reg[%d] = \t d [%d] \t h [%08x]", rd.value, reg[rd.value], reg[rd.value]);
        break;

    case SLTU:
        printf("sltu \t\t reg[%d] = \t d [%d] \t h [%08x]", rd.value, reg[rd.value], reg[rd.value]);
        break;
    }
}