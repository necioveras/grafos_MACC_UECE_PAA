/**********************************************************************************
 * Arquivo  : Vertice.h                                                           *
 * Criacao  : 24/04/2013                                                          *
 * Autor    : Nécio Veras                                                         *
 * Descricao: Classe Vertice composta por arestas armazenadas sob a forma de      *
 *            matriz de adjacencia. Cada objeto possui uma linha que define as    *
 *            adjacencias de suas arestas.                                        *
 **********************************************************************************/

#ifndef __Vertice_h__
#define __Vertice_h__

#include "tipos.h"

/*==========================================================================
=                                                                          =
=                                                                          =
=		              CLASSE VERTICE                               =
=                                                                          =
=                                                                          =
============================================================================
*/

class VERTICE
{
  public:

    typedef struct TARESTA          //Estrutura para Aresta
    {
	    BOOL    adjacencia;       //Define a adjacencia com um vertice (o 'outro lado' da aresta) definido pelo índice
            REAL    peso;             //Peso associado à aresta 
            BOOL    selecionada;      //Usado no algoritmo de de MST
    }ARESTA[], *PARESTA;              //Matriz e ponteiro para aresta

  private:

    PARESTA   ptr_arestas;
    ULONG     num_arestas;
    LONG      valor;
    CARDINAL  pi;                    //valor usado para o calculo do caminho minimo (armazenamento do vertice anterior)

  public:

    VERTICE (); //Construtor - é chamado sempre que um objeto for criado
   ~VERTICE (); //Destrutor  - é chamado sempre que um objeto for destruído

    void  libera         (		  );
    BOOL  cria_linhaAdjencia  (CARDINAL tamanho);
    BOOL  associa_aresta(ULONG id_v2, REAL peso);
    void  exibe          (PCHAR prompt);
    void  exibe_arestas (PCHAR prompt);
    ULONG identifica_arestaMinima();
    
    inline ULONG grau_direcionado       (        )        {return num_arestas;} //Retorna o grau de um vertice
    inline void  selecionaAresta        (ULONG indice)    { ptr_arestas[indice].selecionada = TRUE; }
    inline BOOL  aresta_vistada         (ULONG indice)    { return ptr_arestas[indice].selecionada;}

    //retorna se ha ou nao adjacencia entre dois vertices
    inline BOOL adjacencia_aresta  (ULONG indice)    {return ptr_arestas[indice].adjacencia;}    
    
    inline REAL peso_aresta (ULONG indice) {return ptr_arestas[indice].peso;}
    
    inline void     set_valor   (LONG  vr) {valor = vr;}
    inline LONG     get_valor   () {return valor;}
    inline void     set_pi      (CARDINAL  pi) {this->pi = pi;}
    inline LONG     get_pi      () {return pi;}

};


#endif