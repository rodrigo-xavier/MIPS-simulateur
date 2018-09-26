#include "../include/init.h"

/** @brief Inicializador
 *  @details Chama todas as funções de inicialização,
 *  que inicializam variáveis e leem os arquivos text.bin
 *  e data.bin. Se DEBUG for true, ele mostra informações
 *  dos registradores e da memória
 *  @param void
 *  @return void
*/
void init(void)
{
    init_variables();
    read_data();
    read_text();
    run();

    if (DEBUG)
    {
        dump_reg('h');
        dump_reg('d');
        dump_mem_recorder(0, 72, 'h');
        printf("\n");
        dump_mem_recorder(0, 72, 'd');
    }
}

/** @brief Inicializador de Variáveis
 *  @details Aqui são setados os valores iniciais de todas
 *  as variáveis globais do projeto
 *  @param void
 *  @return void
*/
void init_variables(void)
{
    int i;

    k16 = 0;
    k26.value = 0;
    rs.value = 0;
    rt.value = 0;
    rd.value = 0;
    shamt.value = 0;
    op.value = 0;
    funct.value = 0;
    pc = 0;
    ri = 0;
    epc = 0;
    counter = 0;

    for (i = 0; i < 32; i++)
        reg[i] = 0;
}

/** @brief Leitor de data.bin
 *  @details Função que lê os dados do arquivo data.bin para
 *  a memória a partir do endereço (MEM_SIZE / 2)
 *  @param void
 *  @return void
*/
void read_data(void)
{
    FILE *data;
    int i = 0;
    char lib[] = "../lib/";
    char bin[] = "/data.bin";
    char directory[200];

    strcpy(directory, lib);
    strcat(directory, DIR);
    strcat(directory, bin);

    data = fopen(directory, "rb");

    if (!data)
    {
        printf("Error reading\n");
    }
    else
    {
        while (fread(&mem[i + (MEM_SIZE / 2)], 4, 1, data) != 0)
        {
            i++;
        }
    }

    fclose(data);
}

/** @brief Leitor de text.bin
 *  @details Função que lê os dados do arquivo text.bin para
 *  a memória a partir do endereço 0.
 *  @param void
 *  @return void
*/
void read_text(void)
{
    FILE *text;
    int i = 0;
    char lib[] = "../lib/";
    char bin[] = "/text.bin";
    char directory[200];

    strcpy(directory, lib);
    strcat(directory, DIR);
    strcat(directory, bin);

    text = fopen(directory, "rb");

    if (!text)
    {
        printf("Error reading\n");
    }
    else
    {
        while (fread(&mem[i], 4, 1, text) != 0)
        {
            i++;
        }
    }

    fclose(text);
}