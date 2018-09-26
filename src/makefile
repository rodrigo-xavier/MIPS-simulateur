####################################### Diretórios #########################################
# Aqui estão listados os diretórios do projeto

# Nomes dos executáveis
PROJECT_EXE = ../Project

# Nomes dos diretórios
DIR_HEADERS = ../include
DIR_SOURCES = ../src
DIR_OBJECTS = ../obj



########################################## FLAGS ###########################################
# Especifica o compilador, a versão do C++ e as flags utilizadas para compilar o código

CC = gcc

# Flags que vou precisar para o SDL (o usuário terá que instalar esses 4 pacotes)
# Descomentar quando interface tiver pronta
#LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer



########################## Listas com nomes dos arquivos de código ##########################
# Define o local dos arquivos de código e arquivos de cabeçalho de código

_HEADERS =  memory.h recorder.h recorder.h init.h global.h
HEADERS = $(patsubst %,$(DIR_HEADERS)/%,$(_HEADERS))

_OBJECTS = main.o memory.o recorder.o init.o global.o
OBJECTS = $(patsubst %,$(DIR_OBJECTS)/%,$(_OBJECTS))



############################################ Make ############################################
# Aqui são definidas as regras para compilar o código gerando arquivos objetos e binários

# Gera arquivos objeto para todos os .cpp que estão localizados no mesmo diretório do makefile e em seguida compila
$(DIR_OBJECTS)/%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $<

# Chama todos os arquivos objeto, gerando binários e criando o executável
$(PROJECT_EXE): $(OBJECTS)
	$(CC) -o $@ $^

# MiniTutorial
# all: library.cpp main.cpp
# $@ - Chama o nome da regra 			- all
# $< - Chama o primeiro pré-requisito 	- libray.cpp
# $^ - Chama todos os pré-requisitos 	- library.cpp main.cpp



################################## Outras Regras de Make ####################################
# Aqui estão listadas algumas regras úteis de make para facilitar o trabalho

# make project
# Limpa a tela e executa automaticamente o software
project:
	clear
	./$(PROJECT_EXE)


# make all
# Chama todas as regras de make
all: $(PROJECT_EXE) project



########################################## Clean ###########################################
# Deleta alguns arquivos do projeto (binários, objetos, gcov e gcda)

.PHONY: clean 

# make clean

clean:
	rm -f $(DIR_OBJECTS)/*.o *~ core $(INCDIR)/*~ *.gcda *.gcno *.gcov *.o ../obj/*.gcno ../obj/*.gcda $(PROJECT_EXE) $(DIR_OBJECTS)/*. $(TEST_EXE)
