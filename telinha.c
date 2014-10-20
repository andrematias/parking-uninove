/**
 *
 * Protótipo de tela de input - PRECISA SER MUITO MELHORADO!!!
 * desenvolvido por J. Rodolfo Lima
 * ADS-Unip - PIM IV - OUTUBRO, 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * para teste,começamos com três vagas
 */
#define num_max_vagas 3

void main()
{

  /**
   * @var char | placas de sete caracteres, no máximo, uma em cada vaga, preciso fazer vetor da placas
   */
  char placa [7];

  /**
   * @var int vagas | numero de vagas disponíveis
   * @var int numTotVagas | numero total de vagas
   * @var int opt1, opt2 | optcoes de menu
   */
  int vagas       = num_max_vagas,
      numTotVagas = num_max_vagas,
      opt1        = 0,
      opt2;

  /**
   * @var double horaEent | hora de entrada para cada veículos
   * @var double horaSai | precismaos estudar a biblioteca time.h
   * @var double permanencia | para ver como usar isso
   */
  double horaEent [num_max_vagas],
         horaSai [num_max_vagas],
         permanencia [num_max_vagas];

  /**
   * @var float valor1h | preço da primeira hora
   * @var float valorMais | preço da fração após uma hora, fração de 15 minutos?
   */
  float valor1h,
        valorMais,
        valorTotal;


  printf ("\n\n\n\t******************************\n");

  printf ("\t* Estacionamento PIM-Park IV *");
  printf ("\n\t*          Bem-Vindo!        *\n\t******************************\n\n\n\n\n");
  do
  {
    do

    {
      printf ("\n    Vagas Livres: %d    Vagas ocupadas: %d    Total de vagas: %d\n\n", vagas, (numTotVagas-vagas), numTotVagas);
      if (vagas==0) printf ("\n\n\t\tNÃO HÁ VAGAS.\n\n");

      printf ("\n\n    Escolha a função\n\n    (1- Entrada; 2- Saída; 3- Fechamento do Dia; 0 = Encerrar): ");

      scanf  ("%d", &opt1);
      if ((opt1==1) && (vagas==0))
      {
        printf ("\n\n\t\tNÃO HÁ VAGAS.\n\n");
        opt1 = 4;
      }
      if (opt1==0) exit (EXIT_SUCCESS);
      if (opt1==3) printf ("\n\n\t FUNÇÃO AINDA NÃO IMPLEMENTADA.\n\n");
    }

    while ((opt1!=1) && (opt1!=2));
    if (opt1==1)
    {
      printf ("\n    Carro entrando\n\tDigite a placa:  ");
      scanf  ("%s", &placa);
      printf ("\n    Placa: %s. Confirma? (0 = sim; 1 = não/alterar): ", placa);
      scanf  ("%d", &opt2);
      if (opt2!=0) opt2 = 1;
      else vagas = vagas-1;
    }
    else
    {
      printf ("\n    Carro saindo\n\tDigite a placa:  ");
      scanf  ("%s", &placa);
      printf ("\n    Placa: %s. Confirma? (0 = sim; 1 = não/alterar)", placa);
      scanf  ("%d", &opt2);
      if (opt2!=0) opt2 = 1;
      else vagas = vagas+1;
    }
  }
  while (opt1!=0);
  return (0);
}


