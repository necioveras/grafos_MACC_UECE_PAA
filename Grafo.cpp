#include "Grafo.h"
#include "tipos.h"
#include "Fila.h"
#include "Lista.h"

#include <stdio.h>
#include <time.h>
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
  ULONG     i,id_v1, id_v2        ;  //Armazenar localmente todos as arestas com seus pesos do arquivo
  REAL      peso                  ;
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
     retorno = fscanf (ptr_file,"%lf",&peso); 
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

void GRAFO::gera_instancia_aleatoria(int numMaxVertices, int numMaxArestas, int maxPeso){

  PVERTICE  vertices              ;
  ULONG     i,id_v1, id_v2        ;  //Armazenar localmente todos as arestas com seus pesos do arquivo
  REAL      peso                  ;
  ULONG     n                     ;  //Numero de Vertices
  
  srand(time(NULL));
  n = (rand() % numMaxVertices+1);

  vertices = new VERTICE[n];  //Aloca os Vertices !!!!!!
  if (isnull (vertices))
  {
    printf ("\nSem memoria para a construcao do GRAFO!\n");
    return;
  }

  for (int i = 0 ; i < n; i++)
      vertices[i].cria_linhaAdjencia(n);             //Cria, para cada vertice, a linha de adjacencia 

  int retorno = rand() % numMaxArestas;
  // le informacoes sobre os vertices - a partir da segunda linha do arquivo
  while (retorno >= 0) {    
     id_v1 = (rand() % n)+1;
     id_v2 = (rand() % n)+1;
     peso  = rand()  % maxPeso;
     //Associa a aresta lida para o vértice atual
     vertices[id_v1-1].associa_aresta(id_v2-1, peso);
     retorno--;
  }

  // libera arestas anteriores, se existirem
  libera ();

  // atualiza dados da mochila
  ptr_vertices = vertices;
  num_vertices = n       ;
  
  gera_matrizAdjacencia(2);   //gera a matriz de adjacencia NAO DIRECIONADA com os vertices carregados.
   
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
  if (assigned(matriz_adjacencia)){
      for (int i = 0; i < num_vertices; i++)      
          delete [] matriz_adjacencia[i];
      delete[] matriz_adjacencia;
  }  
  
  //tirar da estrutura local e carregar para o atributo generico (privado) de matriz do GRAFO
  
  matriz_adjacencia = new BOOL*[num_vertices];
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
                    printf("\tAresta com: %lu\tPeso: %.1lf ", j+1, ptr_vertices[i].peso_aresta(j));
        }
      printf("\nTotal de arestas: %lu\n", qtde_arestas());
  }
  else
      printf("\nMatriz não gerada ou nula\n");
   
}

void GRAFO::exibe_Valoresvertices(){
  ULONG i, j;
  
  if (assigned(*matriz_adjacencia)){
      for (i=0 ; i < num_vertices ; i++)            
          printf("\nVertice: %lu\tValor: %ld", i+1, ptr_vertices[i].get_valor());
  }
  else
      printf("\nMatriz não gerada ou nula\n");
  printf("\n");
}

ULONG GRAFO::qtde_arestas ()
{
  ULONG i,soma;

  soma = 0;

  for (i = 0 ; i < num_vertices ; i++)
    soma = soma + ptr_vertices[i].grau_direcionado();

  return soma;
}

void GRAFO::bfs(CARDINAL x){    
    gera_matrizAdjacencia(2);                   //garantir que a matriz de adjacencia sera nao direcionada
    PFILA f = new FILA();
    PLISTA sequenciaVisita = new LISTA();
    CARDINAL verticeVisitado[num_vertices];     
    for (int i = 0; i < num_vertices ; i++) verticeVisitado[i] = 0;   //ninguem foi vistado
        
    for (int i = 0; i < num_vertices; i++){   //empilhar os vertices de primeiro nivel (adjacentes ao vertice inicial)
        if (matriz_adjacencia[x-1][i] == 1)
            f->push(i+1);
    }
    verticeVisitado[x-1] = 1;                      //informar que o vertice X-1 ja foi visitado
    sequenciaVisita->adiciona(x);                      //guarda o primeiro vertice (estado inicial )
    
    while (f->tamanho() > 0){                      //Enquanto a pilha não for vazia
        //printf("Analise da fila: "); f->exibe(); printf("\n");     //Visualiza passo-a-passo as visitas        
        int vertice;
        f->pop(vertice);                               
        
        if (verticeVisitado[vertice-1] == 0){               //vertice NAO visitado
            for (int i = 0; i < num_vertices; i++){         //empilhar os vertices adjacentes ao atual vistado
                if (matriz_adjacencia[vertice-1][i] == 1)   //teste de adjacencia
                    f->push(i+1);
                }
            verticeVisitado[vertice-1] = 1;
            sequenciaVisita->adiciona(vertice);
        }
        
    }
    //printf("Sequencia de vertices visitados (bfs):"); 
    sequenciaVisita->exibe(); printf("\n");
    
}

void GRAFO::dfs(CARDINAL x){
    gera_matrizAdjacencia(2);                   //garantir que a matriz de adjacencia sera nao direcionada
    PFILA f = new FILA();
    PLISTA sequenciaVisita = new LISTA();
    CARDINAL verticeVisitado[num_vertices];     
    for (int i = 0; i < num_vertices ; i++) verticeVisitado[i] = 0;   //ninguem foi vistado
        
    sequenciaVisita->adiciona(x);                                      //marca a primeira visitação. É importante marcar logo, pois                                                                        
    verticeVisitado[x-1] = 1;                                          //pode não haver outros vértices.
    
    int verticeAtual = x;
    
    f->push(x);    
    int passosVolta = 0;                                          //controlar a volta  
    while (f->tamanho() > 0){                                         //devo procurar ate nao existir mais arestas                 
        BOOL ida = FALSE;
        for (int i = 0; i < num_vertices; i++)                  //Procura por adjacencias NAO exploradas
            if (matriz_adjacencia[verticeAtual-1][i] == 1 && verticeVisitado[i] == 0){ //garantir que nao seja aresta com o mesmo vertice (já visitado)
                f->push(i+1);                                         //empilhar APENAS o primeiro vertice adjacente ao vertice atual                       
                if (verticeVisitado[verticeAtual-1] == 0){            //guardar caso o vertice nao tenha sido visitado, pois pode ser a VOLTA
                    sequenciaVisita->adiciona(verticeAtual);
                    verticeVisitado[verticeAtual-1] = 1;
                }
                f->pop(verticeAtual);                                
                ida          = TRUE;
                passosVolta  = 1;                                      //marca o inico dos passos de uma volta
                verticeAtual = i+1;
                break;
        }
        if (ida == FALSE){                                              //Estamos fazendo o percurso de VOLTA em busca de arestas não exploradas
            if (verticeVisitado[verticeAtual-1] == 0){                  //marcar como visitado (caso ele não tenha sido) o vertice inicial do retorno
                sequenciaVisita->adiciona(verticeAtual);
                verticeVisitado[verticeAtual-1] = 1;
            }
            if (sequenciaVisita->get_elem(sequenciaVisita->tamanho() - passosVolta) != NULL){ //Se for NULL então voltamos um passo "além" do vertice original
                verticeAtual = sequenciaVisita->get_dado(sequenciaVisita->tamanho() - passosVolta);                        
                passosVolta++;                                          //variavel que controla a qtde de passos em regressão
            }
            else {  //NULL =  Voltamos ao vertice INICIAL. Se NAO existir aresta a ser explorada entao, acabou o algoritmo
                int verticeInicial = sequenciaVisita->get_dado(0);                        
                for (int i = 0; i < num_vertices; i++)                               //Procura outras adjacencias
                        if (matriz_adjacencia[verticeInicial-1][i] == 1 && verticeVisitado[i] == 0){  //Se encontrar, inicia TUDO novamente por outro caminho
                            ida = TRUE;                                 //Avisa que devemos inicial novamente o caminho de IDA
                            verticeAtual = verticeInicial;
                        }
                if (ida == FALSE){                            //Nao encontrou novas adjacencias, entao acabamos com a exploracao de profundidade
                    //printf("Sequencia de vertices visitados (dfs):"); 
                    sequenciaVisita->exibe(); printf("\n");     
                    return;
                }
            }            
        }
    }        
}

void GRAFO::sp(CARDINAL s, CARDINAL t){

    // Atualiza as distãncias iniciais dos vértices: Inicializa com Zero o vértice inicial e com Infinito todos os outros vértices.
    for (int p = 0; p < num_vertices; p++){ 
        ptr_vertices[p].set_valor(INFINITO);
	ptr_vertices[p].set_pi(p); 
    }
    ptr_vertices[s-1].set_valor(0);
    
    // Relaxamento das arestas.  
    for (int i = 0; i < num_vertices; i++){
        for (int j = 0; j < qtde_arestas(); j++){
            if (ptr_vertices[i].adjacencia_aresta(j)){    	
                if (ptr_vertices[j].get_valor() > ptr_vertices[i].get_valor() + ptr_vertices[i].peso_aresta(j)){
		 	ptr_vertices[j].set_valor(ptr_vertices[i].get_valor() + ptr_vertices[i].peso_aresta(j));
		    	ptr_vertices[j].set_pi(i);  
		}
	     }
        }
    }
    
    // Verificação de ciclos negativos.
    for (int i = 0; i < num_vertices; i++){
        for (int j = 0; j < num_vertices; j++){
            if (ptr_vertices[i].adjacencia_aresta(j))
                if (ptr_vertices[j].get_valor() > ptr_vertices[i].get_valor() + ptr_vertices[i].peso_aresta(j)){
                  printf("Existe um ciclo negativo\n");
                  return;
                }
        }
    }
    
    // PRIMEIRA LINHA: Exibição dos valor do menor caminho entre s e t
    printf("%ld\n", ptr_vertices[t-1].get_valor());
    
    // SEGUNDA LINHA: Exibição da sequencia de vertices correspondentes a um caminho de s a t em G.
    int f = t - 1;
    PLISTA l = new LISTA();

    while(ptr_vertices[f].get_pi() != f){
	l->adiciona(f + 1);
	f = ptr_vertices[f].get_pi();
    }

    l->adiciona(s);
    for(int z = l->tamanho() - 1; z>=0; z--){
	printf("%d\t",l->get_dado(z));
    }
    printf("\n");
}

void GRAFO::exportar(PCHAR nomearquivo){
    FILE     *ptr_file              ;

  if ((ptr_file = fopen (nomearquivo,"w")) == NULL)
    return;
  
  fprintf (ptr_file, "%ld\n", num_vertices);   //Total de vertices  
  
  for (int i = 0; i < num_vertices; i++)  
      for (int j = 0; j < num_vertices; j++)  
          if (ptr_vertices[i].adjacencia_aresta(j) == TRUE)
              fprintf(ptr_file, "%d\t%d\t%.1f\n", i+1, j+1, ptr_vertices[i].peso_aresta(j));
  
  fclose (ptr_file);
}

ULONG GRAFO::identifica_aresta_minima_nao_visitada(PLISTA &vertices, ULONG &v1, ULONG &v2){
/*.......................................................................
 Recebe uma LISTA de vertices e identifica qual a aresta mínima NÃO visitada. 
 Devolve por referência os dois vértices envolvidos na aresta
  .......................................................................
*/

    ULONG minimo = INFINITO;
    float peso   = 0;                              //var. para ajuste de pesos para os grafos nao direcionados
    for (int i = 0; i < vertices->tamanho(); i++){
        for (int j = 0; j < num_vertices; j++){
            if (matriz_adjacencia[vertices->get_dado(i)][j] == TRUE){
                peso = ptr_vertices[vertices->get_dado(i)].peso_aresta(j) + ptr_vertices[j].peso_aresta(vertices->get_dado(i));
                if ((ptr_vertices[vertices->get_dado(i)].aresta_vistada(j) == FALSE) && (ptr_vertices[j].aresta_vistada(vertices->get_dado(i)) == FALSE))
                    if (minimo > peso && vertices->busca_elem(j) == FALSE){
                        //printf("\nLista (T) %d Minimo (anterior=%ld) eh a aresta %d e %d com peso %f\n", l->tamanho(),minimo, l->get_dado(i)+1, j+1, peso);                        
                        minimo = peso;                        
                        v1 = vertices->get_dado(i);
                        v2 = j;                        
                    }
            }                
        }
    }
    ptr_vertices[v1].selecionaAresta(v2);
    return minimo;
}

void GRAFO::mst(PCHAR nomearquivo){  
    
    FILE     *ptr_file;    

    if ((ptr_file = fopen (nomearquivo,"w+")) == NULL)
        return;     
    
    gera_matrizAdjacencia(2);      //cria estrutura NAO direcionada
    PLISTA l = new LISTA();
    PLISTA arestas = new LISTA();
        
    l->adiciona(0);                //Vertice inicial
    ULONG v1, v2;
    int i = 0;
    while (i < num_vertices -1){        
        ULONG peso = identifica_aresta_minima_nao_visitada(l, v1, v2);  //função chave para o funcionamento do algoritmo. Ela usa uma LISTA de vertices para buscar a identificação
        l->adiciona(v2);  
        arestas->adiciona(v1);
        arestas->adiciona(v2);        
        i++;
    }               
    
    fprintf (ptr_file, "%d\n", l->tamanho());   //Total de vertices  
    i = 0;
    while (i < arestas->tamanho()){             //total de arestas
        int v1, v2;
        v1 = arestas->get_dado(i);
        v2 = arestas->get_dado(i+1);
        i = i + 2;
        float peso = ptr_vertices[v1].peso_aresta(v2) + ptr_vertices[v2].peso_aresta(v1);
        fprintf(ptr_file, "%d\t%d\t%.1f\n", v1+1, v2+1, peso);
    }
  
    fclose (ptr_file);
    
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
