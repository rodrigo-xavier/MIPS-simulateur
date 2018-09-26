#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include <stdio.h>
#include <stdint.h>

#include "global.h"

/** @brief Memória
 *  @details Aqui são definidos os cabeçalhos de todas as
 *  funções da memória
*/

void dump_mem(uint32_t, uint32_t);
int32_t lw(uint32_t, int16_t);
int32_t lh(uint32_t, int16_t);
uint32_t lhu(uint32_t, int16_t);
int32_t lb(uint32_t, int16_t);
uint32_t lbu(uint32_t, int16_t);
void sw(uint32_t, int16_t, int32_t);
void sh(uint32_t, int16_t, int16_t);
void sb(uint32_t, int16_t, int8_t);

#endif