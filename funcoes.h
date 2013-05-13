
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
  if (nomearquivo != NULL)
    if (G->carrega (nomearquivo) == FALSE)
    {
        printf ("Erro na abertura do arquivo.\n");
        return;
    }  
  
}

void exibe_menu_apresentacao(){
  printf ("         Construcao de GRAFOS           \n")    ;
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
    printf ("read\t<arq_grafo>,carrega um grafo onde arq_grafo corresponde a um arquivo de grafo.\n");
    printf ("gerar\t <max_vertices> <max_arestas> <max_pesos>, serve para gerar um grafo com valores aleatórios.\n");
    printf ("sobre\tserve para mostrar os dados do cabeçalho do aplicativo.\n");    
    printf ("help\t<comando_ou_subcomando> para mais informações sobre o item especificado.\n");
    
    printf ("\nSubcomandos de read/gerar/help conhecidos:\n");
    printf ("mza\t<sentido>, mostra a matriz de adjacencia onde sentido corresponde ao sentido da matriz de adjacencia\n");
    printf ("pesos\tserve para mostrar os vertices com suas arestas e pesos correspondentes\n");
    printf ("bfs\t<x>, realiza uma busca em largura onde x é um dos vértices do grafo lido\n");
    printf ("dfs\t<x>, realiza uma busca em profundidade onde x é um dos vértices do grafo lido\n");
    printf ("mst\t<arq_grafo_saida>, calcula e gera uma árvore mínima geradora onde arq_grafo_saida será um arquivo texto\n");
    printf ("sp\t<s> <t>, calcula e mostra o caminho mínimo entre s e t onde s e t são dois vértices do grafo lido\n");
    printf ("exporta\t <arquivo_saida>, exporta o grafo atual para um arquivo de saída onde arquivo_saida será o nome do arquivo a ser gerado\n");
    
}

void exibe_formatoArquivo(){
    printf("n\n");        
    printf("x\ty\tz\n...\t...\t..., onde\n");
    printf("n = número de vértices\n");        
    printf("x e y = arestas pertencentes a um conjunto V = {1,2,...,n} de vertices\n");        
    printf("z = peso de um aresta {x, y}\n"); 
}


void exibe_ajuda(char *option){
    limpa_tela();
    printf("comando usado: help %s\n", option);
    if (strcasecmp(option,"read") == 0){
        printf("\nÉ usado para carregar a configuração de um grafo a partir de um arquivo.\n"
                "Vale ressaltar que este comando não funciona em conjunto com o comando gerar.\n");
        printf("\nNo entando o formato do arquivo deve estar da seguinte forma:\n");        
        exibe_formatoArquivo();       
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
    else if (strcasecmp(option,"pesos") == 0){
        printf("\nÉ usado para exibir os vértices do grafo com seus respectivos pesos.\n");        
        printf("Sintaxe:\n");        
        printf("\t\t\t%s\n", option);
        printf("Parâmetro:\n");        
        printf("Não há parâmetro(s)\n");       
    }
    else if (strcasecmp(option,"bfs") == 0){
        printf("\nÉ usado para executar a tecnica de Busca em Largura, do ingles Breadth-first search.\n");
        printf("Sintaxe:\n");        
        printf("\t\t\t%s <x>\n", option);
        printf("Parâmetro:\n");        
        printf("<x>\n");
        printf("Indica o vertice inicial da busca.\n");
        printf("Saída:\n");        
        printf("Será exibido uma sequencia de vertices visitados, iniciando no vertice x.\n");
    }
    else if (strcasecmp(option,"dfs") == 0){
        printf("\nÉ usado para executar a tecnica de Busca em Profundidade, do ingles Depth-first search.\n");
        printf("Sintaxe:\n");        
        printf("\t\t\t%s <x>\n", option);
        printf("Parâmetro:\n");        
        printf("<x>\n");
        printf("Indica o vertice inicial da busca.\n");
        printf("Saída:\n");        
        printf("Será exibido uma sequencia de vertices visitados, iniciando no vertice x.\n");        
    }
    else if (strcasecmp(option,"mst") == 0){
        printf("\nÉ usado para calcular e gerar a árvore geradora mínima (Minimal Spanning Tree) por meio do algoritmo Prim.\n");
        printf("Sintaxe:\n");        
        printf("\t\t\t%s <arquivoSaida>\n", option);
        printf("Parâmetro:\n");        
        printf("<arquivoSaida>\n\n");
        printf("Nome do arquivo que será gerado pelo algoritmo com a árvore geradora mínima.\n");
        printf("Formato do arquivo:\n");        
        exibe_formatoArquivo();
    }
    else if (strcasecmp(option,"sp") == 0){
        printf("\nÉ usado para executar a tecnica do caminho mínimo (short path) por meio do algoritmo de Bellman Ford.\n");
        printf("Sintaxe:\n");        
        printf("\t\t\t%s <s> <p>\n", option);
        printf("Parâmetro:\n");        
        printf("<s>\n");
        printf("Indica o vertice inicial.\n");
        printf("<t>\n");
        printf("Indica o vertice final.\n");
        printf("Saída:\n");        
        printf("d\nx1\tx2\t...\txp\t, onde\nd = valor do caminho mínimo entre <s> e <t>\n"
                "cada x representa os vertices que formam o caminho mínimo entre x1 e xp.\n"
                "Lembrando que x1 = <s> e xp = <t>\n");
    }
    else if (strcasecmp(option,"exporta") == 0){
        printf("\nÉ usado para exportar o grafo atual em um arquivo de saída.\n");
        printf("Sintaxe:\n");        
        printf("\t\t\t%s <arquivo_saida>\n", option);
        printf("Parâmetro:\n");        
        printf("<arquivo_saida>\n");
        printf("Será o nome do arquivo a ser gerado com os dados do grafo.\n");        
        printf("O arquivo gerado possuirá o seguinte formato:\n");        
        exibe_formatoArquivo();
    }
    else if (strcasecmp(option,"gerar") == 0){
        printf("\nÉ usado para gerar um grafo sem o uso de um arquivo texto. Ele criará um grafo com dados aleatórios\n"
                "Vale ressaltar que este comando não funciona em conjunto com o comando read.\n\n");
        printf("Sintaxe:\n");        
        printf("\t\t\t%s <max_vertices> <max_arestas> <max_pesos>\n", option);
        printf("Parâmetros:\n");        
        printf("<max_vertices>\n");        
        printf("Determina o número máximo de vértices que o grafo poderá possuir.\n");        
        printf("<max_arestas>\n");        
        printf("Determina o número máximo de arestas que o grafo poderá possuir entre dois vértices\n");        
        printf("<max_pesos>\n");        
        printf("Determina o valor máximo de peso que uma determinada aresta poderá possuir.\n");        
    }
    else if (strcasecmp(option,"sobre") == 0){
        printf("\nÉ usado para exibir as informações sobre os desenvolvedores.\n");
        printf("Sintaxe:\n");        
        printf("\t\t\t%s\n", option);
        printf("Parâmetro:\n");        
        printf("Não há parâmetro:\n");        
    }
    else exibe_menu_erro(option);
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
        //exibe_menu_apresentacao();
        if ((strcasecmp(argv[1],"read") == 0) || (strcasecmp(argv[1],"gerar") == 0))           //OK, COMANDO DE LEITURA                              
        for (arg=2;arg < argc;arg++){            
                if (strcasecmp(argv[arg],"mza") == 0){                   
                    int sentido = atoi(argv[++arg]);  
                    G->gera_matrizAdjacencia(sentido);     //LE O PARAMETRO (itera a repetição para evitar engano de parametro)
                    G->exibe_matrizAdjacencia(); 
                }
                else if (strcasecmp(argv[arg],"pesos") == 0)
                    G->exibe_matrizComPesos();
                else if (strcasecmp(argv[arg],"bfs") == 0){
                    int x = atoi(argv[++arg]);  
                    G->bfs(x);     //LE O PARAMETRO (itera a repetição para evitar engano de parametro)                   
                }
                else if (strcasecmp(argv[arg],"dfs") == 0){
                    int x = atoi(argv[++arg]);  
                    G->dfs(x);     //LE O PARAMETRO (itera a repetição para evitar engano de parametro)                   
                }
                else if (strcasecmp(argv[arg],"mst") == 0){
                    PCHAR nomeArq = argv[++arg];  
                    G->mst(nomeArq);     //LE O PARAMETRO (itera a repetição para evitar engano de parametro)                   
                }
                else if (strcasecmp(argv[arg],"exporta") == 0){
                    PCHAR nomeArq = argv[++arg];  
                    G->exportar(nomeArq);     //LE O PARAMETRO (itera a repetição para evitar engano de parametro)                   
                }
                else if (strcasecmp(argv[arg],"sp") == 0){
                    int s = atoi(argv[++arg]);  
                    int t = atoi(argv[++arg]);  
                    G->sp(s,t);     //LE O PARAMETRO (itera DUAS VEZES a repetição para evitar engano de parametro)                   
                }               
                else                                      //Parametro(s) para leitura (instâncias) do comando read
                    if (strcasecmp(argv[1],"read") == 0)
                        carrega_grafo (argv[arg]);
                    else
                        if (strcasecmp(argv[1],"gerar") == 0){                   //verifica o primeiro argumento se NAO eh o comando read
                            int maxV = atoi(argv[arg++]);                  
                            int maxA = atoi(argv[arg++]);  
                            int maxP = atoi(argv[arg]);  
                            carrega_grafo(NULL);
                            G->gera_instancia_aleatoria(maxV, maxA, maxP);
                        }
        }
    }  
}

#endif
