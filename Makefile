compila: grafo.cpp tipos.h funcoes.h Grafo.h Grafo.cpp Vertice.h Vertice.cpp Lista.h Lista.cpp Fila.h Fila.cpp
	g++ grafo.cpp tipos.h funcoes.h Grafo.h Grafo.cpp Vertice.h Vertice.cpp Lista.h Lista.cpp Fila.h Fila.cpp -o grafo.o
	@echo Compilacao concluida. Arquivo binario gerado: grafo.o 

executa: compila
	@echo Para executar voce deve usar o comando ./grafo.o

limpa: 
	rm *.o
