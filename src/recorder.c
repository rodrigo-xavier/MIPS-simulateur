#include "../include/recorder.h"

/** @brief Função que lê palavra da memória
 *  @details Esta função lê uma instrução da memória,
 *  atribuindo a instrução à ri, e fazendo pc apontar para
 *  a próxima instrução.
*/
void fetch()
{
    ri = lw(0, pc);
    pc += 4;
}

/** @brief Função que decodifica uma instrução
 *  @details Esta função faz uso do registrador ri, atribuindo
 *  cada parte da instrução contida em ri, em um campo 
*/
void decode(void)
{
    op.value = (ri >> 26) & 0x3f;
    rs.value = (ri >> 21) & 0x1f;
    rt.value = (ri >> 16) & 0x1f;
    rd.value = (ri >> 11) & 0x1f;
    shamt.value = (ri >> 6) & 0x1f;
    funct.value = ri & 0x3f;
    k26.value = ri & 0x3ffffff;
    k16 = ri & 0xffff;
    signal_extension();
}

/** @brief Função que estende o sinal de k16
 *  @details Por padrão, k16 é preenchido com 0's nos primeiros
 *  16 bits e informação nos outros 16 bits. Se o sinal de k16
 *  for negativo, a função preenche os primeiros 16 bits com 1's,
 *  extendendo o sinal negativo.
*/
void signal_extension(void)
{
    if ((k16 >> 15) == 1)
        k16 |= 0xffff0000;
}

/** @brief Função que executa as instruções de opcode e funct
 *  @details Depois de lidas e decodificadas as instruções do
 *  registrador de instruções (ri), os comandos opcode e funct
 *  são avaliados e selecionados para executar os comandos da
 *  instrução
*/
void execute(void)
{
    int64_t product;
    uint16_t kte = 0;
    int i;
    char character = ' ';

    switch (op.value)
    {
    case EXT:
        switch (funct.value)
        {
        case SLL:
            reg[rd.value] = reg[rt.value] << shamt.value;
            break;

        case SRL:
            if (shamt.value != 0)
            {
                reg[rd.value] = (reg[rt.value] & 0x7fffffff) >> (shamt.value - 1);
            }

            break;

        case SRA:
            if (reg[rt.value] >> 31 == 1)
            {
                reg[rd.value] = reg[rt.value];
                for (i = 0; i < shamt.value; i++)
                    reg[rd.value] = reg[rd.value] >> 1;
                reg[rd.value] = reg[rd.value] | 0x80000000;
            }
            else
            {
                reg[rd.value] = reg[rt.value] >> shamt.value;
            }
            break;

        case JR:
            pc = reg[rs.value];
            break;

        case SYSCALL:
            switch (reg[2])
            {
            case 1:
                if (!DEBUG)
                    printf("%d", reg[4]);
                break;

            case 4:
                while (character != '\0')
                {
                    if (!DEBUG)
                        printf("%c", character);

                    character = lb(reg[4], kte);

                    kte += 1;
                }
                break;

            case 10:
                epc = 1;
                break;

            default:
                printf("Invalid syscall");
                epc = 2;
            }
            break;

        case MFHI:
            reg[rd.value] = hi;
            break;

        case MFLO:
            reg[rd.value] = lo;
            break;

        case MULT:
            product = (int64_t)reg[rs.value] * (int64_t)reg[rt.value];
            hi = (uint32_t)((product >> 32) & 0xffffffff);
            lo = (int32_t)product & 0xffffffff;
            break;

        case DIV:
            hi = reg[rs.value] % reg[rt.value];
            lo = reg[rs.value] / reg[rt.value];
            break;

        case ADD:
            reg[rd.value] = reg[rs.value] + reg[rt.value];
            break;

        case ADDU:
            reg[rd.value] = (uint32_t)reg[rs.value] + reg[rt.value];
            break;

        case SUB:
            reg[rd.value] = reg[rs.value] - reg[rt.value];
            break;

        case AND:
            reg[rd.value] = reg[rs.value] & reg[rt.value];
            break;

        case OR:
            reg[rd.value] = reg[rs.value] | reg[rt.value];
            break;

        case XOR:
            reg[rd.value] = reg[rs.value] ^ reg[rt.value];
            break;

        case NOR:
            reg[rd.value] = ~(reg[rs.value] | reg[rt.value]);
            break;

        case SLT:
            reg[rd.value] = (reg[rs.value] < reg[rt.value]) ? 1 : 0;
            break;

        case SLTU:
            reg[rd.value] = (uint32_t)(reg[rs.value] < reg[rt.value]) ? 1 : 0;
            break;
        }
        break;

    case J:
        pc = (pc & 0xf0000000) | (k26.value << 2);
        break;

    case JAL:
        reg[31] = pc;
        pc = (pc & 0xf0000000) | (k26.value << 2);
        break;

    case BEQ:
        pc += (reg[rs.value] == reg[rt.value]) ? (k16 << 2) : 0;
        break;

    case BNE:
        pc += (reg[rs.value] != reg[rt.value]) ? (k16 << 2) : 0;
        break;

    case BLEZ:
        pc += (reg[rs.value] <= 0) ? (k16 << 2) : 0;
        break;

    case BGTZ:
        pc += (reg[rs.value] > 0) ? (k16 << 2) : 0;
        break;

    case ADDI:
        reg[rt.value] = reg[rs.value] + k16;
        break;

    case ADDIU:
        reg[rt.value] = (uint32_t)(reg[rs.value] + k16);
        break;

    case SLTI:
        reg[rt.value] = (reg[rs.value] < k16) ? 1 : 0;
        break;

    case SLTIU:
        reg[rt.value] = (((uint32_t)reg[rs.value]) < k16) ? 1 : 0;
        break;

    case ANDI:
        reg[rt.value] = reg[rs.value] & k16;
        break;

    case ORI:
        k16 &= 0x0000ffff;
        reg[rt.value] = reg[rs.value] | k16;
        break;

    case XORI:
        reg[rt.value] = reg[rs.value] ^ k16;
        break;

    case LUI:
        reg[rt.value] = (int32_t)k16 << 16;
        break;

    case LB:
        reg[rt.value] = lb(reg[rs.value], k16) | 0xffffff00;
        break;

    case LH:
        reg[rt.value] = lh(reg[rs.value], k16) | 0xffff0000;
        break;

    case LW:
        reg[rt.value] = lw(reg[rs.value], k16);
        break;

    case LBU:
        reg[rt.value] = lbu(reg[rs.value], k16);
        break;

    case LHU:
        reg[rt.value] = lhu(reg[rs.value], k16);
        break;

    case SB:
        sb(reg[rs.value], k16, reg[rt.value]);
        break;

    case SH:
        sh(reg[rs.value], k16, reg[rt.value]);
        break;

    case SW:
        sw(reg[rs.value], k16, reg[rt.value]);
        break;

    default:
        printf("Instruction not found\n");
        epc = 2;
        break;
    }
}

/** @brief Função que lê, decodifica, executa e debuga cada instrução
 *  @details Esta função chama outras funções, como um degrau
*/
void step(void)
{
    fetch();
    decode();
    execute();
    debug();
}

/** @brief Função que roda todas as instruções da memória
 *  @details Esta função roda todas as intruções da memória
 *  até acabarem as instruções, ou o bloco de instruções 
 *  exceder o limite
*/
void run(void)
{
    int i = 0;

    if (DEBUG)
        printf("Pressione enter para pular de instrução\n\n");
    while ((epc == 0) && (pc < (MEM_SIZE / 2)))
    {
        step();
    }

    if (epc == 1)
        printf("\n\nSucessfull!!! Closed by syscall\n");
    else
        printf("Error!!! Instruction not found\n");
}

/** @brief Função que mostra conteúdo da memória
 *  @details Esta função recebe um endereço inicial, e um endereço
 *  final e mostra o conteúdo da memória contido nestes endereços 
 *  nos formatos hexadecimal ou decimal 
 *  @param  int start, int end, char format
*/
void dump_mem_recorder(int start, int end, char format)
{
    int i;

    if (start < end && ((start + end) % 4) == 0)
    {
        if (format == 'h')
        {
            for (i = start / 4; i < end / 4; i++)
            {
                printf("mem[%d] =\t\t %08x\n", i, mem[i]);
            }
        }
        else if (format == 'd')
        {
            for (i = start / 4; i < end / 4; i++)
            {
                printf("mem[%d] =\t\t %d\n", i, mem[i]);
            }
        }
        else
        {
            printf("Invalid Format\n");
        }
    }
    else
    {
        printf("Non-aligned address\n");
    }
}

/** @brief Função que mostra o conteúdo dos registradores
 *  @details Esta função percorre todos os registradores,
 *  mostrando o conteúdo de cada um
 *  @param char format
*/
void dump_reg(char format)
{
    int i;

    if (format == 'h')
    {
        printf("\nregister ($zero):\t %08x\n", reg[0]);
        printf("register ($at):\t\t %08x\n", reg[1]);
        printf("register ($v0):\t\t %08x\n", reg[2]);
        printf("register ($v1):\t\t %08x\n", reg[3]);

        for (i = 4; i < 8; i++)
            printf("register ($a%d):\t\t %08x\n", (i - 4), reg[i]);
        for (i = 8; i < 16; i++)
            printf("register ($t%d):\t\t %08x\n", (i - 8), reg[i]);
        for (i = 16; i < 26; i++)
            printf("register ($s%d):\t\t %08x\n", (i - 16), reg[i]);

        printf("register ($k0):\t\t %08x\n", reg[26]);
        printf("register ($k1):\t\t %08x\n", reg[27]);
        printf("register ($gp):\t\t %08x\n", reg[28]);
        printf("register ($sp):\t\t %08x\n", reg[29]);
        printf("register ($fp):\t\t %08x\n", reg[30]);
        printf("register ($ra):\t\t %08x\n", reg[31]);
        printf("register (pc):\t\t %08x\n", pc);
        printf("register (hi):\t\t %08x\n", hi);
        printf("register (lo):\t\t %08x\n\n", lo);
        printf("rs.value:\t\t %08x\n", rs.value);
        printf("rt.value:\t\t %08x\n", rt.value);
        printf("rd.value:\t\t %08x\n", rd.value);
        printf("shamt:\t\t\t %08x\n", shamt.value);
        printf("op:\t\t\t %08x\n", op.value);
        printf("funct:\t\t\t %08x\n", funct.value);
        printf("k16:\t\t\t %08x\n", k16);
        printf("k26:\t\t\t %08x\n\n", k26);
    }
    else if (format == 'd')
    {
        printf("\nregister ($zero):\t %d\n", reg[0]);
        printf("register ($at):\t\t %d\n", reg[1]);
        printf("register ($v0):\t\t %d\n", reg[2]);
        printf("register ($v1):\t\t %d\n", reg[3]);

        for (i = 4; i < 8; i++)
            printf("register ($a%d):\t\t %d\n", (i - 4), reg[i]);
        for (i = 8; i < 16; i++)
            printf("register ($t%d):\t\t %d\n", (i - 8), reg[i]);
        for (i = 16; i < 26; i++)
            printf("register ($s%d):\t\t %d\n", (i - 16), reg[i]);

        printf("register ($k0):\t\t %d\n", reg[26]);
        printf("register ($k1):\t\t %d\n", reg[27]);
        printf("register ($gp):\t\t %d\n", reg[28]);
        printf("register ($sp):\t\t %d\n", reg[29]);
        printf("register ($fp):\t\t %d\n", reg[30]);
        printf("register ($ra):\t\t %d\n", reg[31]);
        printf("register (pc):\t\t %d\n", pc);
        printf("register (hi):\t\t %d\n", hi);
        printf("register (lo):\t\t %d\n\n", lo);
    }
    else
    {
        printf("Invalid Format\n");
    }
}