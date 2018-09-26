#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "memory.h"
#include "global.h"
#include "recorder.h"

/** @brief Inicialização
 *  @details Aqui são definidos os cabeçalhos de todas as
 *  funções de inicialização, tais como setar o valor inicial
 *  das variáveis, ler os arquivos text.bin e data.bin
*/
void init(void);
void init_variables(void);
void set_values(void);
void read_data(void);
void read_text(void);
// void init_menu(void);

#endif