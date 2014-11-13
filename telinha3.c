/**
 *
 * Protótipo de tela de input - PRECISA SER MUITO MELHORADO!!!
 * desenvolvido por J. Rodolfo Lima
 * ADS-Unip - PIM IV - OUTUBRO, 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

#define num_max_vagas 10 /** numero total de vagas */

/** funções:
           recDia: recupera os dados parciais do último uso após interrupção do sistem;
           main: gerencia entrada e saíde de veículos e o "fechamento do dia"
           relatorio: gera os relatório diário em arquivo e impresso.
           str2int (char texto[8]): converte a placa do carro em int, usando o valor ASCII de cada caracter
*/

int recDia ();
int relatorio ();
int checkPlaca (char texto[8]);
//long int str2int (char texto[8]);

int main()
 {

  /**
   * @var char | placas de sete caracteres
   * @var int opt1, opt2 | opcoes de menu
   */
  char carroPlaca [num_max_vagas] [8],
       opt1, opt2;

  /**
   * @var int vagasLivres : numero de vagas disponíveis
   * @var int numTotVagas : numero total de vagas
   * @var int i : indice para cada caracter em um string
   * @var int j : indice das vagas, no vetor de vagas
   * @var int statusVaga : indicador do estado da vaga
   * @var aux = variavel auxiliar para diversos usos
   */

 int vagasLivres = num_max_vagas,
      numTotVagas = num_max_vagas,
      aux,
      i, j,
      statusVaga [num_max_vagas];

  /**
   * @var long int carroPlacaLI : placa do carro transformada para int
   */


 //long int carroPlacaLI [num_max_vagas];

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

 totalDia=0;
 for(j=0;j<num_max_vagas;j++)
   {
   statusVaga[j]=0;
   }

 do
   {
   printf ("\n\n");
   printf ("\n\t\t******************************");
   printf ("\n\t\t* Estacionamento PIM-Park IV *");
   printf ("\n\t\t*          Bem-Vindo!        *");
   printf ("\n\t\t******************************\n\n\n");


   for (j=0;j<num_max_vagas;j++) if (statusVaga[j]==1) vagasLivres-=1;
   do
     {
      printf ("\n    Vagas Livres: %d    Vagas ocupadas: %d    Total de vagas: %d\n\n", vagasLivres, (numTotVagas-vagasLivres), numTotVagas);
      if (vagasLivres==0) printf ("\n\n\t\tNÃO HÁ VAGAS.\n\n");

      printf ("\n\n    Escolha a fun%c%co\n", 135, 198);
      printf ("\n\tE - Entrada de Veículo");
      printf ("\n\tS - Saída de Veículo");
      printf ("\n\tF - Fechamento do Dia");
      printf ("\n\tX - Encerrar SEM fechar o dia");
      printf ("\n\t\t\t\t\t Opção -> ");

      opt1 = getchar();

      if ((opt1=='F')||(opt1=='f'))
        {
        printf ("\n\n\t FUNÇÃO AINDA NÃO IMPLEMENTADA.\n\nPressione qualquer tecla para continuar\n");
        }

      if ((opt1=='X')||(opt1=='x'))
         {
         printf ("\n\tTEM CERTEZA QUE QUER SAIR SEM FAZER O FECHAMENTO DO DIA?");
         printf ("\n\t\tS = Sim, tenho certeza\n\t\tN = Não, quero voltar ao início: ");
         if ((getchar()=='S')||(getchar()=='s')) exit (EXIT_SUCCESS);
         }
     }
    while ((opt1!='E') && (opt1!='S') && (opt1!='e') && (opt1!='s'));


    if ((opt1=='E')||(opt1=='e')) /** Inicio do bloco de entrada de veículos*/
      {
      if (vagasLivres==0) printf ("\n\n\t\tNÃO HÁ VAGAS.\n\n");
      else
        {
        printf ("\n    Carro entrando\n\tDigite a placa:  ");
        scanf ("%s", &carroPlaca);

/** A linha abaixo converte letras minusculas em maiúsculas, importante para
    permitir a conversao da placa em long int, pela funcao str2int (abaixo).
*/
        for (i=0;i<7;i++) if (carroPlaca[j][i]>=97 && carroPlaca[j][i]<=122) carroPlaca[j][i] -= 32;

        carroPlaca[j][7] = '\0'; /** Isto garante que o último caracter da string sera \0.   */

        printf ("\n    Placa-> %s", carroPlaca);
        if (checkPlaca(carroPlaca)==0)
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
//          carroPlacaLI = str2int(carroPlaca);
          vagasLivres = vagasLivres-1;
          }
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
  while (opt1!='Z');
  return (0);
}

/** a função long int str2int (char texto[8]), a seguir, converte texto em um numero (long int),
    substituindo cada caracter pelo sei código ASCII correspondente. Funciona apenas para caracteres
    cujo codigo ascii tem dois dígitos. Isso permite armazenar a placa em um vetor de long int,
    muito mais fácil de lidar do que uma matriz de char.
    */
/*
long int str2int (char texto[8])
 {
  int ii,
      numLetra;
  long int valorConvertido;

  for (ii=0;ii<7;ii++)
    {
    numLetra = texto[ii];
    valorConvertido += numLetra * (pow(100,ii));
    }
 return (valorConvertido);
 }
*/
  /** a função int checkPlaca (char texto[8]) verifica se o texto de sete caracteres inserido contém
    três letras maiúsculas segidas de quatro algarismos.
    Retorna 0 se a placa eh valida ou um valor maior se for invalida */

int checkPlaca (char texto[8])
 {
/** @var chk | recebe valor 0 se a placa eh valida ou um valor maior se for invalida
    @var ii | indices de posição dos caracteres no texto */

 int chk=0, ii;

 for (ii=0;ii<3;ii++) if ((texto[ii]<65)||(texto[ii]>90)) chk+=1;
 for (ii=3;ii<7;ii++) if ((texto[ii]<48)||(texto[ii]>57)) chk+=1;
 return (chk);
 }
