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
            LONG    peso;          //Peso associado à aresta 
    }ARESTA[], *PARESTA;            //Matriz e ponteiro para aresta

  private:

    PARESTA   ptr_arestas;
    ULONG     num_arestas;
    LONG      valor;

  public:

    VERTICE (); //Construtor - é chamado sempre que um objeto for criado
   ~VERTICE (); //Destrutor  - é chamado sempre que um objeto for destruído

    void  libera         (		  );
    BOOL  cria_linhaAdjencia  (CARDINAL tamanho);
    BOOL  associa_aresta(ULONG id_v2, LONG peso);
    void  exibe          (PCHAR prompt);
    void  exibe_arestas (PCHAR prompt);
    
    inline ULONG grau_direcionado       (        )        {return num_arestas;} //Retorna o grau de um vertice

    //retorna se ha ou nao adjacencia entre dois vertices
    inline BOOL adjacencia_aresta  (ULONG indice)    {return ptr_arestas[indice].adjacencia;}
    
    inline CARDINAL peso_aresta (ULONG indice) {return ptr_arestas[indice].peso;}
    inline void     set_valor   (LONG  vr) {valor = vr;}
    inline LONG     get_valor    () {return valor;}

};


#endif