#include "../include/memory.h"

/** @brief Função que mostra conteúdo da memória
 *  @details Esta função mostra o conteúdo da memória
 *  de um endereço inicial até um endereço de valor inicial
 *  somado a uma constante.
 *  @param uint32_t address, uint32_t size
 *  @return void
*/
void dump_mem(uint32_t address, uint32_t size)
{
    int i;

    for (i = address; i < ((address + size) / 4); i++)
    {
        printf("mem[%d] = %08x\n", i, mem[i]);
    }
}

/** @brief Função que lê uma palavra de 32 bits
 *  @details Esta função retorna o conteúdo da memória
 *  de um endereço somado a uma constante. Se o endereço
 *  estiver desalinhado da memória, ou seja não for divisível
 *  por 4, a função mostra uma menssagem de erro e retorna
 *  um valor que indica que há um erro.
 *  @param uint32_t address, int16_t kte
 *  @return int32_t mem[address]
*/
int32_t lw(uint32_t address, int16_t kte)
{
    if (((address + kte) % 4) == 0)
    {
        address = (address + kte) / 4;
        return mem[address];
    }
    else
    {
        printf("Non-aligned address\n");
    }

    // ASCII: 45 = E | 52 = R | 52 = R | 4F = O
    return 0x4552524F;
}

/** @brief Função que lê meia palavra de 32 bits
 *  @details Esta função retorna o conteúdo da memória
 *  de um endereço somado a uma constante. Se o endereço
 *  estiver desalinhado da memória, ou seja não for divisível
 *  por 2, a função mostra uma menssagem de erro e retorna
 *  um valor que indica que há um erro.
 *  A função utiliza máscaras para conseguir ler meia palavra
 *  tanto superior, quanto inferior.
 *  Em seguida, os valores lidos são deslocados para o inicio
 *  da palavra de retorno.
 *  @param uint32_t address, int16_t kte
 *  @return int32_t mem[address]
*/
int32_t lh(uint32_t address, int16_t kte)
{
    int32_t mask, word, rest;

    rest = (address + kte) % 4;

    if (((address + kte) % 2) == 0)
    {
        address = (address + kte) / 4;

        if (rest == 0)
        {
            mask = 0x0000ffff;
            word = mem[address] & mask;
            return word;
        }
        else if (rest == 2)
        {
            mask = 0xffff0000;
            word = mem[address] & mask;

            /** Aqui a meia palavra lida é deslocada para o endereço inicial de word*/
            word >>= 4 * 4;
            mask = 0x0000ffff;
            word &= mask;
            return word;
        }
    }
    else
    {
        printf("Non-aligned address\n");
    }

    // ASCII: 45 = E | 52 = R | 52 = R | 4F = O
    return 0x4552524F;
}

/** @brief Função que lê meia palavra de 32 bits sem sinal
 *  @details Esta função retorna o conteúdo da memória
 *  de um endereço somado a uma constante. Se o endereço
 *  estiver desalinhado da memória, ou seja não for divisível
 *  por 2, a função mostra uma menssagem de erro e retorna
 *  um valor que indica que há um erro.
 *  A função utiliza máscaras para conseguir ler meia palavra
 *  tanto superior, quanto inferior.
 *  Em seguida, os valores lidos são deslocados para o inicio
 *  da palavra de retorno.
 *  O valor retornado pela função, é um valor unsigned, ou seja,
 *  sem sinal.
 *  @param uint32_t address, int16_t kte
 *  @return int32_t mem[address]
*/
uint32_t lhu(uint32_t address, int16_t kte)
{
    uint32_t mask, word, rest;

    rest = (address + kte) % 4;

    if (((address + kte) % 2) == 0)
    {
        address = (address + kte) / 4;

        if (rest == 0)
        {
            mask = 0x0000ffff;
            word = mem[address] & mask;
            return word;
        }
        else if (rest == 2)
        {
            mask = 0xffff0000;
            word = mem[address] & mask;

            /** Aqui a meia palavra lida é deslocada para o endereço inicial de word*/
            word >>= 4 * 4;
            mask = 0x0000ffff;
            word &= mask;
            return word;
        }
    }
    else
    {
        printf("Non-aligned address\n");
    }

    // ASCII: 45 = E | 52 = R | 52 = R | 4F = O
    return 0x4552524F;
}

/** @brief Função que lê um byte
 *  @details Esta função retorna o conteúdo da memória
 *  de um endereço somado a uma constante.
 *  A função utiliza máscaras para conseguir ler o byte
 *  Em seguida, os valores lidos são deslocados para o inicio
 *  da palavra de retorno.
 *  @param uint32_t address, int16_t kte
 *  @return int32_t mem[address]
*/
int32_t lb(uint32_t address, int16_t kte)
{
    int32_t mask, word, rest;

    rest = (address + kte) % 4;
    address = (address + kte) / 4;

    if (rest == 0)
    {
        mask = 0x000000ff;
        word = mem[address] & mask;
        return word;
    }
    else if (rest == 1)
    {
        mask = 0x0000ff00;
        word = mem[address] & mask;

        /** Aqui o byte lido é deslocado para o inicio de word*/
        word >>= 4 * 2;
        return word;
    }
    else if (rest == 2)
    {
        mask = 0x00ff0000;
        word = mem[address] & mask;

        /** Aqui o byte lido é deslocado para o inicio de word*/
        word >>= 4 * 4;
        return word;
    }
    else if (rest == 3)
    {
        mask = 0xff000000;
        word = mem[address] & mask;

        /** Aqui o byte lido é deslocado para o inicio de word*/
        word >>= 4 * 6;
        mask = 0x000000ff;
        word &= mask;
        return word;
    }

    // ASCII: 45 = E | 52 = R | 52 = R | 4F = O
    return 0x4552524F;
}

/** @brief Função que lê um byte sem sinal
 *  @details Esta função retorna o conteúdo da memória
 *  de um endereço somado a uma constante.
 *  A função utiliza máscaras para conseguir ler o byte
 *  Em seguida, os valores lidos são deslocados para o inicio
 *  da palavra de retorno.
 *  O valor retornado pela função, é um valor unsigned, ou seja,
 *  sem sinal.
 *  @param uint32_t address, int16_t kte
 *  @return int32_t mem[address]
*/
uint32_t lbu(uint32_t address, int16_t kte)
{
    int32_t mask, word, rest;

    rest = (address + kte) % 4;
    address = (address + kte) / 4;

    if (rest == 0)
    {
        mask = 0x000000ff;
        word = mem[address] & mask;
        return word;
    }
    else if (rest == 1)
    {
        mask = 0x0000ff00;
        word = mem[address] & mask;

        /** Aqui o byte lido é deslocado para o endereço inicial de word*/
        word >>= 4 * 2;
        return word;
    }
    else if (rest == 2)
    {
        mask = 0x00ff0000;
        word = mem[address] & mask;

        /** Aqui o byte lido é deslocado para o endereço inicial de word*/
        word >>= 4 * 4;
        return word;
    }
    else if (rest == 3)
    {
        mask = 0xff000000;
        word = mem[address] & mask;

        /** Aqui o byte lido é deslocado para o endereço inicial de word*/
        word >>= 4 * 6;
        mask = 0x000000ff;
        word &= mask;
        return word;
    }

    // ASCII: 45 = E | 52 = R | 52 = R | 4F = O
    return 0x4552524F;
}

/** @brief Função que salva uma palavra de 32 bits na memória
 *  @details Esta função recebe um endereço de memória somado 
 *  a uma constante. Se o endereço estiver desalinhado da memória, 
 *  ou seja não for divisível por 4, a função mostra uma menssagem
 *  de erro. Caso contrário, ela salva o dado recebido na memória
 *  @param uint32_t address, int16_t kte, int32_t dado
 *  @return void
*/
void sw(uint32_t address, int16_t kte, int32_t dado)
{
    if (((address + kte) % 4) == 0)
    {
        address = (address + kte) / 4;
        mem[address] = dado;
    }
    else
    {
        printf("Non-aligned address\n");
    }
}

/** @brief Função que salva meia palavra de 32 bits na memória
 *  @details Esta função recebe um endereço de memória somado 
 *  a uma constante. Se o endereço estiver desalinhado da memória, 
 *  ou seja não for divisível por 2, a função mostra uma menssagem
 *  de erro. Caso contrário, ela salva o dado recebido na memória
 *  nos limites superior ou inferior do endereço utilizando máscaras.
 *  @param uint32_t address, int16_t kte, int32_t dado
 *  @return void
*/
void sh(uint32_t address, int16_t kte, int16_t dado)
{
    int32_t content, mask, word, rest;
    uint32_t mask_dado;

    rest = (address + kte) % 4;

    if (((address + kte) % 2) == 0)
    {
        address = (address + kte) / 4;

        if (rest == 0)
        {
            mask = 0xffff0000;
            mask_dado = 0x0000ffff;
            word = mem[address] & mask;
            content = dado & mask_dado;
            mem[address] = word | content;
        }
        else if (rest == 2)
        {
            mask = 0x0000ffff;
            mask_dado = 0xffff0000;
            word = mem[address] & mask;
            content = (dado << 16) & mask_dado;
            mem[address] = word | content;
        }
    }
    else
    {
        printf("Non-aligned address\n");
    }
}

/** @brief Função que salva um byte na memória
 *  @details Esta função recebe um endereço de memória somado 
 *  a uma constante. E salva o dado recebido na memória utilizando máscaras.
 *  @param uint32_t address, int16_t kte, int32_t dado
 *  @return void
*/
void sb(uint32_t address, int16_t kte, int8_t dado)
{
    int32_t content, mask, word, rest;
    uint32_t mask_dado;

    rest = (address + kte) % 4;

    address = (address + kte) / 4;

    if (rest == 0)
    {
        mask = 0xffffff00;
        mask_dado = 0x000000ff;
        word = mem[address] & mask;
        content = dado & mask_dado;
        mem[address] = word | content;
    }
    else if (rest == 1)
    {
        mask = 0xffff00ff;
        mask_dado = 0x0000ff00;
        word = mem[address] & mask;
        content = (dado << 8) & mask_dado;
        mem[address] = word | content;
    }
    else if (rest == 2)
    {
        mask = 0xff00ffff;
        mask_dado = 0x00ff0000;
        word = mem[address] & mask;
        content = (dado << 16) & mask_dado;
        mem[address] = word | content;
    }
    else if (rest == 3)
    {
        mask = 0x00ffffff;
        mask_dado = 0xff000000;
        word = mem[address] & mask;
        content = (dado << 24) & mask_dado;
        mem[address] = word | content;
    }
}