
/**********************************************************************************
 * Arquivo  : funcoes.h                                                           *
 * Criacao  : 24/04/2013                                                          *
 * Autor    : Nécio Veras                                                         *
 * Descricao: Funcoes especificas para auxiliar em um trabalho de implementacao   *
 *            da disciplina de PAA no programa de MACC da UECE.                   *
 **********************************************************************************/

#ifndef __funcoes_h__
#define __funcoes_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tipos.h"
#include "Grafo.h"

PGRAFO G;   //Variável GLOBAL p/ manipular o grafo

void carrega_grafo (PCHAR nomearquivo)
{
  // mostra nome da instancia  

  G = new GRAFO();

  // carrega grafo do arquivo
  if (G->carrega (nomearquivo) == FALSE)
  {
    printf ("Erro na abertura do arquivo.\n");
    return;
  }  
  else
      printf ("\n Instancia : %s carregada com sucesso.\n",nomearquivo);
}

void exibe_menu_apresentacao(){
  printf ("         Construcao de GRAFO           \n")    ;
  printf ("         Mestrado Academico em Ciencia da Computacao\n")    ;
  printf ("         Universidade Estadual do Ceara\n")    ;
  printf ("         Projeto e Analise de algoritmos\n");
  printf ("         Alunos:\n");
  printf ("         \t\tNecio de Lima Veras\n");
  printf ("         \t\tRobert Marinho\n");    
}

void limpa_tela(){
    #ifdef __WIN32__
    system("cls");
    #endif
    #ifdef __linux__
    system("clear");
    #endif
}

void exibe_menu_erro(PCHAR app){       
    
    limpa_tela();

    printf ("Error: comandos não especificados\n");
    printf ("Sintaxe de uso:\n\t %s read <arq_grafo> <comando1> <parametro1> [... <comandoN> <parametroN>]\n\n", app);
    
    printf ("Comandos conhecidos:\n");
    printf ("read\t<arq_grafo>, onde arq_grafo corresponde a um arquivo texto\n");
    printf ("mza\t<sentido>, mostra a matriz de adjacencia onde sentido corresponde ao sentido da matriz de adjacencia\n");
    printf ("pesos\tserve para mostrar os vertices com suas arestas e pesos correspondentes\n");
    printf ("bfs\t<x>, onde x é um dos vértices do grafo lido\n");
    printf ("dfs\t<x>, onde x é um dos vértices do grafo lido\n");
    printf ("mst\t<arq_grafo_saida>, onde arq_grafo_saida será um arquivo texto\n");
    printf ("sp\t<s> <t>, onde s e t são dois vértices do grafo lido\n");
    printf ("\nUse help <comando> para mais informações sobre um item.");
    printf ("\nUse help all para informações sobre todos os item.\n\n");    
}


void exibe_ajuda(char *option){
    limpa_tela();
    printf("comando usado: help %s\n", option);
    if (strcasecmp(option,"all") == 0)
        printf("\nTodos ....\n");
    else if (strcasecmp(option,"read") == 0){
        printf("\nÉ usado para carregar a configuração de um grafo a partir de um arquivo.");
        printf("\nNo entando o formato do arquivo deve estar da seguinte forma:\n");        
        printf("n\n");        
        printf("x\ty\tz\n...\t...\t..., onde\n");
        printf("n = número de vértices\n");        
        printf("x e y = arestas pertencentes a um conjunto V = {1,2,...,n} de vertices\n");        
        printf("z = peso de um aresta {x, y}\n");        
    }
    else if (strcasecmp(option,"mza") == 0){
        printf("\nÉ usado para exibir o resultado da leitura promovida pelo comando read.");
        printf("\nA visualização se dá por uma matriz de adjacência onde os vértices são representados\n"
                "por uma matriz de 0 e 1 (lógica) indicando a presença ou não de uma aresta entre os vértices envolvidos.\n");               
        printf("Sintaxe:\n");        
        printf("\t\t\t%s <sentido>\n", option);
        printf("Parâmetro:\n");        
        printf("<sentido>\n");
        printf("Pode receber os valores 0, 1 e 2, onde:\n");        
        printf("0 = grafo direcionado. Sentido de IDA\n");
        printf("1 = grafo direcionado. Sentido de VOLTA\n");
        printf("2 = grafo não direcionado.\n");
    }
}

/*==========================================================================
=                                                                          =
=                                                                          =
=		          FUNCAO  GERENCIADORA DOS COMANDOS LIDOS          =
=                                                                          =
=                                                                          =
============================================================================
*/


void gerencia_comando(int argc, char *argv[]){
    int      arg;
    if (strcasecmp(argv[1],"help") == 0){           //AJUDA          
        if (argc >= 3)            
            exibe_ajuda(argv[2]);
        else                                        //AJUDA SEM ARGUMENTO                
            exibe_menu_erro(argv[0]);
        }
    else {
        exibe_menu_apresentacao();
        if (strcasecmp(argv[1],"read") == 0)           //OK, COMANDO DE LEITURA                              
           for (arg=2;arg < argc;arg++){
               if (strcasecmp(argv[arg],"mza") == 0){                   
                  int sentido = atoi(argv[++arg]);  
                  G->gera_matrizAdjacencia(sentido);     //LE O PARAMETRO (itera a repetição para evitar engano de parametro)
                  G->exibe_matrizAdjacencia(); 
               }
               else if (strcasecmp(argv[arg],"pesos") == 0){                   
                   G->exibe_matrizComPesos();
               }
               else                                      //Parametro(s) para leitura (instâncias)
                  carrega_grafo (argv[arg]);
           }
    }  
}

#endif
