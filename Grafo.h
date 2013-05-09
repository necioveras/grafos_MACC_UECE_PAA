/**********************************************************************************
 * Arquivo  : Grafo.h                                                             *
 * Criacao  : 24/04/2013                                                          *
 * Autor    : Nécio Veras                                                         *
 * Descricao: Classe Grafo capaz de manipular qualquer quantidade de vertices e   *
 *            arestas.                                                            *
 **********************************************************************************/

#ifndef __Grafo_h__
#define __Grafo_h__

#include "Vertice.h"
#include "tipos.h"
#include "Lista.h"


/*==========================================================================
=                                                                          =
=                    Classes definidas neste arquivo                       =
=                                                                          =
============================================================================
*/

class   VERTICE             ;
class   GRAFO               ;

typedef GRAFO    *PGRAFO    ;
typedef VERTICE  *PVERTICE  ;




/*==========================================================================
=                                                                          =
=                                                                          =
=		              CLASSE GRAFO                                 =
=                                                                          =
=                                                                          =
============================================================================
*/

class GRAFO
{

  private:

    PVERTICE ptr_vertices     ;
    ULONG    num_vertices     ;
    BOOL   **matriz_adjacencia;
    

    void libera ();

  public:

    GRAFO   (); //Construtor - é chamado sempre que um objeto for criado
   ~GRAFO   (); //Destrutor  - é chamado sempre que um objeto for desmontado   

    BOOL    carrega (PCHAR nomearquivo);    
    void    exportar(PCHAR nomearquivo);
    void    exibe   (		       );
    void    exibe_matrizAdjacencia();
    void    exibe_matrizComPesos();
    void    exibe_Valoresvertices();
    void    gera_matrizAdjacencia(CARDINAL sentido);
    ULONG   identifica_aresta_minima_nao_visitada(PLISTA &vertices, ULONG &v1, ULONG &v2);    //Devolve o peso minimo
    
    inline  ULONG    qtde_vertices (  )  {return num_vertices;}

    ULONG            qtde_arestas  (  );

    BOOL    existe_aresta (ULONG v1, ULONG v2, CARDINAL sentido);
    inline BOOL**  get_matriz_adjacencia () {return matriz_adjacencia;}
    
    void    bfs (CARDINAL x); 
    void    dfs (CARDINAL x); 
    void    sp  (CARDINAL s, CARDINAL t);
    void    mst (PCHAR nomearquivo);
};



#endif