#ifndef RECORDER_H_INCLUDED
#define RECORDER_H_INCLUDED

#include <stdio.h>
#include <stdint.h>

#include "memory.h"
#include "global.h"

/** @brief Registrador
 *  @details Aqui são definidos os cabeçalhos de todas as
 *  funções de registrador
*/
void fetch(void);
void decode(void);
void execute(void);
void step(void);
void run(void);
void dump_mem_recorder(int, int, char);
void dump_reg(char);
void signal_extension(void);

#endif