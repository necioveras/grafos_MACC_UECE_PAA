/**********************************************************************************
 * Arquivo  : tipos.h                                                             *
 * Criacao  : 24/04/2013                                                          *
 * Autor    : Nécio Veras                                                         *
 * Descricao: Este aquivo contem tipos e estrutras de dados definidos de forma a  *
 *            auxiliar em implementações diversas. Alguns tipos são redefinidos   *
 *            para simplificar o processo de codificação.                         *
 **********************************************************************************/

#ifndef __tipos_h__
#define	__tipos_h__

#include <stdlib.h>
#include <limits.h> 
#include <values.h>


/*==========================================================================
=                                                                          =
=                                                                          =
=          Estruturas personalizadas para facilitar a programação          =
=                                                                          =
=                                                                          =
============================================================================
*/

#ifdef __MSDOS__
typedef enum {FALSE, TRUE}  BOOL;           // logico
#define bool     BOOL
#else
#define BOOL     bool
#define FALSE    false
#define TRUE     true
#endif

typedef unsigned long  int  CARDINAL, *PCARDINAL;

// operacoes com ponteiros
#define isnull(p)       ((p) == NULL)       // indica se um ponteiro e' nulo
#define assigned(p)     ((p) != NULL)       // indica se um ponteiro e' valido

//Algumas redefinições 

typedef          char       CHAR,  *PCHAR;  // caractere
typedef unsigned char       BYTE,  *PBYTE;  // inteiro sem sinal de 8 bits (byte)
typedef unsigned char       BIT,   *PBIT;   // um bit (0 ou 1)
typedef signed   short int  INT,   *PINT;   // inteiro com sinal de 16 bits
typedef unsigned short int  UINT,  *PUINT;  // inteiro sem sinal de 16 bits
typedef signed   long  int  LONG,  *PLONG;  // inteiro com sinal de 32 bits
typedef unsigned long  int  ULONG, *PULONG; // inteiro sem sinal de 32 bits
typedef double REAL, *PREAL;                // numero de ponto flutuante

typedef void  *POINTER;                     // ponteiro generico



/*==========================================================================
=                                                                          =
=                    Final das Estruturas Personalizadas                   =
=                                                                          =
============================================================================
*/


#endif	/* TIPOS_H */

