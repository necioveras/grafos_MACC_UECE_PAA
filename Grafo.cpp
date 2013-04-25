#include "Grafo.h"
#include "tipos.h"
#include <stdio.h>
/*==========================================================================
  =                                                                        =
  =                                                                        =
  =                 IMPLEMENTACAO DOS METODOS DA CLASSE GRAFO              =
  =                                                                        =
  =                                                                        =
  ==========================================================================
*/

GRAFO::GRAFO ()
{
   ptr_vertices = NULL;
   num_vertices = 0;
}


void GRAFO::libera()
{
  if (assigned (ptr_vertices))
  {
    ptr_vertices->libera();
    delete[] ptr_vertices;
  }    

  ptr_vertices = NULL;
  num_vertices = 0   ;
}


GRAFO::~GRAFO()
{
  libera();
}


BOOL GRAFO::carrega (PCHAR nomearquivo)
{
  FILE     *ptr_file              ;
  PVERTICE  vertices              ;
  ULONG     i,id_v1, id_v2, peso  ;  //Armazenar localmente todos as arestas com seus pesos do arquivo
  ULONG     n                     ;  //Numero de Vertices

  if ((ptr_file = fopen (nomearquivo,"rt")) == NULL)
    return FALSE;

  // le no. de vertices - primeira linha do arquivo
  fscanf (ptr_file,"%lu",&n);

  vertices = new VERTICE[n];  //Aloca os Vertices !!!!!!
  if (isnull (vertices))
  {
    fclose (ptr_file);
    printf ("\nSem memoria para a construcao do GRAFO!\n");
    return FALSE     ;
  }

  for (int i = 0 ; i < n; i++)
      vertices[i].cria_linhaAdjencia(n);             //Cria, para cada vertice, a linha de adjacencia 

  int retorno = 0;
  // le informacoes sobre os vertices - a partir da segunda linha do arquivo
  while (retorno != EOF) {
     retorno = fscanf (ptr_file,"%lu",&id_v1); 
     retorno = fscanf (ptr_file,"%lu",&id_v2); //Uma aresta é formada por DOIS VERTICES
     retorno = fscanf (ptr_file,"%lu",&peso); 
     //Associa a aresta lida para o vértice atual
     vertices[id_v1-1].associa_aresta(id_v2-1, peso);
  }

  fclose (ptr_file);

  // libera arestas anteriores, se existirem
  libera ();

  // atualiza dados da mochila
  ptr_vertices = vertices;
  num_vertices = n       ;
  
  gera_matrizAdjacencia(2);   //gera a matriz de adjacencia NAO DIRECIONADA com os vertices carregados.

  return TRUE            ;
}


void GRAFO::exibe ()
{
  ULONG i;

  for (i=0 ; i < num_vertices ; i++)
  {
    printf ("\nVertice: %lu",i+1)      ;
    printf ("\tGrau direcionado   : %lu",ptr_vertices[i].grau_direcionado());
    ptr_vertices[i].exibe_arestas((PCHAR)"\tArestas:");
  }
}

void GRAFO::gera_matrizAdjacencia(CARDINAL sentido){
/*.......................................................................
  funcao compativel com grafo direcionado e/ou grafo nao-direcionado, onde:
  0 -> Corresponde ao sentido de IDA  , ou seja V1 para V2
  1 -> Corresponde ao sentido de VOLTa, ou seja V2 para V1
  2 -> Funciona para ambas as direcoes (grafo nao-direcionado)
  .......................................................................
*/
  ULONG i, j;
  BOOL m[num_vertices][num_vertices];
  
  for (i=0 ; i < num_vertices ; i++)
    for (j = 0; j < num_vertices; j++)
        m[i][j] = FALSE;    
        
  
  switch (sentido){
      case 0:   //direcionado (IDA)          
      case 1:   //direcionado (VOLTA) 
          for (i=0 ; i < num_vertices ; i++){
              for (j = 0; j < num_vertices; j++){
                    if (ptr_vertices[i].adjacencia_aresta(j) == TRUE){
                        m[i][j] = ptr_vertices[i].adjacencia_aresta(j);
                    }
              }          
          }          
          break;          
      case 2:   //nao direcionado
          for (i=0 ; i < num_vertices ; i++){
              for (j = 0; j < num_vertices; j++){
                    if (ptr_vertices[i].adjacencia_aresta(j) == TRUE){
                        m[i][j] = ptr_vertices[i].adjacencia_aresta(j);
                        m[j][i] = m[i][j];        //constroi a matriz completa com ida e volta, ou seja, sem direcao
                    }
              }          
          }          
          break;
  }
  
  //zerar a matriz antiga
  if (assigned(*matriz_adjacencia)){
      delete[] *matriz_adjacencia;
  }  
  
  //tirar da estrutura local e carregar para o atributo generico (privado) de matriz do GRAFO
  
  *matriz_adjacencia = new BOOL[num_vertices];
  for (i=0 ; i < num_vertices ; i++){
    matriz_adjacencia[i] = new BOOL[num_vertices];
    for (j = 0; j < num_vertices; j++){
        matriz_adjacencia[i][j] = m[i][j];
    }
  }    
}

void GRAFO::exibe_matrizAdjacencia(){
  ULONG i, j;
  //imprimir a matriz gerada
  if (assigned(*matriz_adjacencia)){
      for (i=0 ; i < num_vertices ; i++){
            printf("\nVertice: %lu Arestas: [", i+1);
            for (j = 0; j < num_vertices; j++)
                printf("%d,", matriz_adjacencia[i][j]);              
            printf("%c%c%c]", 8,32,8);
        }
      printf("\nTotal de arestas: %lu\n", qtde_arestas());
  }
  else
      printf("\nMatriz não gerada ou nula\n");
 
}

void GRAFO::exibe_matrizComPesos(){
  ULONG i, j;
  
  if (assigned(*matriz_adjacencia)){
      for (i=0 ; i < num_vertices ; i++){            
          printf("\nVertice: %lu ", i+1);
            for (j = 0; j < num_vertices; j++)
                if (ptr_vertices[i].adjacencia_aresta(j) == TRUE)
                    printf("\tAresta com: %lu\tPeso: %lu ", j+1, ptr_vertices[i].peso_aresta(j));
        }
      printf("\nTotal de arestas: %lu\n", qtde_arestas());
  }
  else
      printf("\nMatriz não gerada ou nula\n");
   
}

ULONG GRAFO::qtde_arestas ()
{
  ULONG i,soma;

  soma = 0;

  for (i = 0 ; i < num_vertices ; i++)
    soma = soma + ptr_vertices[i].grau_direcionado();

  return soma;
}


BOOL GRAFO::existe_aresta (ULONG v1, ULONG v2, CARDINAL sentido)
{
/*.......................................................................
  funcao compativel com grafo direcionado e/ou grafo nao-direcionado, onde:
  0 -> Corresponde ao sentido de IDA  , ou seja V1 para V2
  1 -> Corresponde ao sentido de VOLTa, ou seja V2 para V1
  2 -> Funciona para ambas as direcoes (grafo nao-direcionado)
  .......................................................................
*/

  ULONG i,grau,aresta; //Grau do vertice


  switch (sentido)
  {
  case 0:
  case 2:
	  
  case 1:
      break;
	  
  }

  /////////////////////////
  return FALSE;
}
