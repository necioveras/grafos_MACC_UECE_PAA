#include "tipos.h"
#include "funcoes.h"

  /*
      Implementacao de GRAFOs - MACC - UECE
   *  Disciplina: Projeto e análise de algoritmos
      ALUNOS:
			NÉCIO  VERAS
                        ROBERTO MARINHO
  */

/*==========================================================================
=                                                                          =
=                                                                          =
=		          FUNCAO  PRINCIPAL                                =
=                                                                          =
=                                                                          =
============================================================================
*/

int main (int argc, char *argv[])
{
  int      arg;
  CARDINAL i;  

  if (argc <= 2)   //Argumentos insuficientes
  {
    if (argc == 2 && (strcasecmp(argv[1],"sobre") == 0))  
        exibe_menu_apresentacao();
    else
        exibe_menu_erro(argv[0]);
    return -1;
  }  
    
  gerencia_comando(argc, argv);
  
  return 0;
}