#include "Vertice.h"
#include "tipos.h"
#include <stdio.h>
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
    valor       = 2147483647;     //INFINITO
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
    }
    
    libera();

    ptr_arestas = arestas;
    return TRUE;
    
}

BOOL VERTICE::associa_aresta(ULONG id_v2, LONG peso){
  
  if (ptr_arestas[id_v2].adjacencia != TRUE){ //garantir que não será contabilizada a mesma aresta
     ptr_arestas[id_v2].adjacencia = TRUE;
     ptr_arestas[id_v2].peso = peso;     
     num_arestas++;
     return TRUE;    
  }  
  return FALSE;
  
}


void VERTICE::exibe (PCHAR prompt)
{
  
}

void VERTICE::exibe_arestas(PCHAR prompt){
  
}
