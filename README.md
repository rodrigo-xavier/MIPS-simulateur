# Simulador Assembly Mips


**Os arquivos estão organizados da seguinte forma:**

*	docs -> Contém os arquivos de documentação gerados pelo doxygen (Latex e Html) e os relatórios individuais de cada membro do grupo
*	include-> Contém os arquivos de cabeçalho do código como (.h)
*	obj-> Contém os objetos e arquivos gcov gerados pelo makefile
*	src-> Contém as funções dos arquivos de cabeçalho, a main e o makefile
*   	lib-> Contém os arquivos binários para rodar o programa

-----------

**Ambiente e Execução**

**Requirements:**
	
	Ubuntu version: 18:04
	gcc version: 7.3.0
	make version: 4.1
*	Caso necessário, instale os pacotes utilizando "sudo apt-get install make""

**Para compilar e executar: Acesse o diretório "src"**
	
*	Para compilar digite "make" e o projeto será compilado.
*	Para executar (somente se projeto já tiver sido compilado) digite "make project" e o arquivo "Project" será gerado na estrutura principal.
*	Para compilar e executar automaticamente digite "make all" no terminal e o arquivo "Project" será gerado na estrutura principal do projeto e executado automaticamente

**Comandos makefile:**
	
	make		 -	Compila o Projeto
	make project 	 -	Executa o projeto
	make clean	 -	Apaga arquivos objeto, binários, gcov e outros
	make all	 -	Compila, executa e gera Arquivos Gcov

-----------

**Observações:**

*	Na main, é possível alterar a variável DEBUG para true, ou para false, para debugar o código, mostrando informações úteis.
*	Na main, também é possível alterar o diretório em que o programa deve procurar os arquivos binários "text.bin e data.bin". Por padrão, o programa procura dentro da pasta lib. Ex:
*	strcpy(DIR, "teste") - procura arquivos text.bin e data.bin no diretório /lib/teste
*	strcpy(DIR, "primos") - procura arquivos text.bin e data.bin no diretório /lib/primos
