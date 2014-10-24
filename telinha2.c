/**
 *
 * Protótipo de tela de input - PRECISA SER MUITO MELHORADO!!!
 * desenvolvido por J. Rodolfo Lima
 * ADS-Unip - PIM IV - OUTUBRO, 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define num_max_vagas 10 /** numero total de vagas */

/** funções:
           recDia: recupera os dados parciais do último uso após interrupção do sistem;
           entSaiFecha: gerencia entrada e saíde de veículos e o "fechamento do dia"
           relatorio: gera os relatório diário em arquivo e impresso.
           str2int (char texto[8]): converte a placa do carro em int, usando o valor ASCII de cada caracter
*/

int recDia ();
int entSaiFecha ();
int relatorio ();
long int str2int (char texto[8]);

int main()
 {
 char optMain;

 do
 {
 printf ("\n\n");
 printf ("\n\t******************************");
 printf ("\n\t* Estacionamento PIM-Park IV *");
 printf ("\n\t*          Bem-Vindo!        *");
 printf ("\n\t******************************\n\n");
 printf ("\tSão %d vagas para o seu conforto.\n\n\n", num_max_vagas);
 printf ("    Iniciar o programa (digite I).");
 printf ("\n    recuperar/Continuar o dia (digite C).\n    Para gerar Relatório (digite R).\n");
 printf ("\n    Ou pressione qualquer outra tecla para sair -> ");
 scanf  ("%c", &optMain);


 switch (optMain)
   {
   case ('I'):
     entSaiFecha();
     break;
   case ('i'):
     entSaiFecha();
     break;
   case ('C'):
     {
     printf ("\n    AINDA NÃO IMPLEMENTADO\n    Sair (S/N)?");
     scanf ("%c", &optMain);
     if ((optMain!='N')||(optMain!='n')) exit (EXIT_SUCCESS);
     }
     break;
   case ('c'):
     {
     printf ("\n    AINDA NÃO IMPLEMENTADO\n    Sair (S/N)?");
     scanf ("%c", &optMain);
     if ((optMain!='N')||(optMain!='n')) exit (EXIT_SUCCESS);
     }
     break;

   case ('R'):
     {
     printf ("\n    AINDA NÃO IMPLEMENTADO\n    Sair (S/N)?");
     scanf ("%c", &optMain);
     if ((optMain!='N')||(optMain!='n')) exit (EXIT_SUCCESS);
     }
     break;
   case ('r'):
     {
     printf ("\n    AINDA NÃO IMPLEMENTADO\n    Sair (S/N)?");
     scanf ("%c", &optMain);
     if ((optMain!='N')||(optMain!='n')) exit (EXIT_SUCCESS);
     }
     break;
  }
 }
 while (optMain!='S');
return (0);
 }


int entSaiFecha()
 {

  /**
   * @var char | placas de sete caracteres
   */
  char carroPlaca [8];

  /**
   * @var int vagasLivres | numero de vagas disponíveis
   * @var int numTotVagas | numero total de vagas
   * @var int opt1, opt2 | opcoes de menu
   * @var int i : indice para cada caracter em um string
   * @var j indice das vagas, no vetor de vagas
   * @var int statusVaga indicador do estado da vaga
   * @var long int carroPlacaInt placa do carro transformada para int
   * @var i indice para caracter em string
   * @var aux = variavel auxiliar para diversos usos
   */
 int vagasLivres = num_max_vagas,
      numTotVagas = num_max_vagas,
      opt1, opt2, aux,
      i, j[num_max_vagas],
      statusVaga [num_max_vagas],
      carroPlacaInt/*[num_max_vagas]*/;

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
   * @var float valorDevido | valor da estadia do veiculo, na saída
   * @var float totalDia | total do dia
   */
 float valor1h,
        valorMais,
        valorDevido,
        totalDia;

 do
   {
   printf ("\n\n");
   printf ("\n\t******************************");
   printf ("\n\t* Estacionamento PIM-Park IV *");
   printf ("\n\t*          Bem-Vindo!        *");
   printf ("\n\t******************************\n\n\n");
   do

    {
      printf ("\n    Vagas Livres: %d    Vagas ocupadas: %d    Total de vagas: %d\n\n", vagasLivres, (numTotVagas-vagasLivres), numTotVagas);
      if (vagasLivres==0) printf ("\n\n\t\tNÃO HÁ VAGAS.\n\n");

      printf ("\n\n    Escolha a função\n\n    (1- Entrada; 2- Saída; 3- Fechamento do Dia; 4 = Encerrar): ");

      scanf  ("%d", &opt1);
      if ((opt1==1) && (vagasLivres==0))
      {
        printf ("\n\n\t\tNÃO HÁ VAGAS.\n\n");
        opt1 = 0;
      }
      if (opt1==4) exit (EXIT_SUCCESS);
      if (opt1==3) printf ("\n\n\t FUNÇÃO AINDA NÃO IMPLEMENTADA.\n\n");
    }
    while ((opt1!=1) && (opt1!=2));

    if (opt1==1)
      {
      printf ("\n    Carro entrando\n\tDigite a placa:  ");
      scanf ("%s", &carroPlaca);

/** A linha abaixo converte letras minusculas em maiúsculas, importante para
    permitir a conversao da placa em long int, pela funcao str2int (abaixo).
*/
      for (i=0;i<7;i++) if (carroPlaca[i]>=97 && carroPlaca[i]<=122) carroPlaca[i] -= 32;

/** A linha abaixo garante que o último caracter da string da placa seá o caracter de fim.
*/
      carroPlaca[7] = '\0';

/** A sequencia abaixo verifica se a placa inserida tem três letras e quatro numeros
    usando os intervalos de valores para letras maiusculas e para algarismos da tabela ASCII
    */
      aux = 0;
      for (i=0;i<3;i++) if ((carroPlaca[i]<65)||(carroPlaca[i]>90)) aux+=1;
      for (i=3;i<7;i++) if ((carroPlaca[i]<48)||(carroPlaca[i]>57)) aux+=1;


      printf ("\n    Placa-> %s", carroPlaca);
      if (aux==0)
        {
        printf ("\n    Confirma? (1 = sim; 2 = voltar): ");
        scanf  ("%d", &opt2);
        }
      else
        {
        printf ("\n\n\tESTA NÃO É UMA PLACA VÁLIDA. \n\n");
        opt2 = 2;
        }
      if (opt2!=1) opt2 = 2;
      else
        {
        carroPlacaInt = str2int(carroPlaca);
        vagasLivres = vagasLivres-1;
        }
      }
    else
      {
      printf ("\n    Carro saindo\n\tDigite a placa:  ");
      scanf  ("%s", carroPlaca);
      printf ("\n    Placa: %s. Confirma? (1 = sim; 2 = não/alterar)", carroPlaca);
      scanf  ("%d", &opt2);
      if (opt2!=1) opt2 = 2;
      else vagasLivres = vagasLivres+1;
      }
  }
  while (opt1!=4);
  return (0);
}

/** a função long int str2int (char texto[8]), a seguir, converte texto em um numero (long int),
    substituindo cada caracter pelo sei código ASCII correspondente. Funciona apenas para caracteres
    cujo codigo ascii tem dois dígitos. Isso permite armazenar a placa em um vetor de long int,
    muito mais fácil de lidar do que uma matriz de char.
    */

long int str2int (char texto[8])
 {
  int i,
      numLetra;
  long int valorConvertido;

  for (i=0;i<7;i++)
    {
    numLetra =texto[i];
    valorConvertido += numLetra * (pow(100,i));
    }
 return (valorConvertido);
 }



