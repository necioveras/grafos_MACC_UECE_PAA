#include "Vertice.h"
#include "tipos.h"
#include <stdio.h>
#include <math.h>
/*==========================================================================
  =                                                                        =
  =                                                                        =
  =                 IMPLEMENTACAO DOS METODOS DA CLASSE VERTICE            =
  =                                                                        =
  =                                                                        =
  ==========================================================================
*/


VERTICE::VERTICE()
{
    ptr_arestas = NULL;
    num_arestas = 0   ;
    valor       = INFINITO;
    pi          = 0;
}

void VERTICE::libera ()
{
  if (assigned (ptr_arestas))
  {
    delete[] ptr_arestas;
  }

  ptr_arestas  = NULL;
  num_arestas  = 0   ;
}


VERTICE::~VERTICE ()
{
  libera();
}


BOOL VERTICE::cria_linhaAdjencia(CARDINAL tamanho){
    PARESTA   arestas ;
    
    // aloca espaco para as arestas do vertice
    arestas = new TARESTA[tamanho];
    if (isnull (arestas))
    {
      printf ("\nSem memoria para gerar arestas!\n");
      return FALSE;
    }
    
    for (CARDINAL i; i < tamanho; i++){
        arestas[i].adjacencia = FALSE;
        arestas[i].peso       = 0;
        arestas[i].selecionada= FALSE;
    }
    
    libera();

    ptr_arestas = arestas;
    return TRUE;
    
}

BOOL VERTICE::associa_aresta(ULONG id_v2, REAL peso){
  
  if (ptr_arestas[id_v2].adjacencia != TRUE){ //garantir que não será contabilizada a mesma aresta
     ptr_arestas[id_v2].adjacencia = TRUE;
     ptr_arestas[id_v2].peso = peso;     
     num_arestas++;
     return TRUE;    
  }  
  return FALSE;
  
}

ULONG VERTICE::identifica_arestaMinima(){
    REAL minimo = ptr_arestas[0].peso;
    for (int i = 1; i < num_arestas; i++)
        if (minimo < ptr_arestas[i].peso)
            minimo = ptr_arestas[i].peso;
    return minimo;
}


void VERTICE::exibe (PCHAR prompt)
{
  
}

void VERTICE::exibe_arestas(PCHAR prompt){
  
}
