/**
 *
 * Prototipo de tela de input - PRECISA SER MUITO MELHORADO!!!
 * desenvolvido por J. Rodolfo Lima
 * ADS-Unip - PIM IV - OUTUBRO, 2014
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define num_max_vagas 10 /** numero total de vagas */

/** funcoes:
        main: gerencia entrada e saida de veiculos e o "fechamento do dia"
        int relatorio: gera os relatorio diário em arquivo e impresso.
        int str2int (char texto[8]): converte a placa do carro em int, usando o valor ASCII de cada caracter
        int checkPlaca: Verifica se a cadeia fornecida corresponde a uma placa valida
*/

int relatorio ();
int checkPlaca (char texto[8]);
long int str2int (char texto[8]);

int main()
 {

  /**
   * @var char | placas de sete caracteres
   * @var int opt1, opt2 | opcoes de menu
   */
  char carroPlaca[8],
       opt1, opt2;

  /**
   * @var int vagasLivres : numero de vagas disponiveis
   * @var int numTotVagas : numero total de vagas
   * @var int i : indice para cada caracter em um string
   * @var int j : indice das vagas, no vetor de vagas
   * @var aux = variavel auxiliar para diversos usos
   */

 int vagasLivres = num_max_vagas,
      numTotVagas = num_max_vagas,
      aux,
      i, j;

  /**
   * @var long int carroLI : placa do carro covertida para long int
   */


 long int carroLI [num_max_vagas];

  /**
   * @var double horaEent | hora de entrada para cada veiculos
   * @var double horaSai | precismaos estudar a biblioteca time.h
   * @var double permanencia | para ver como usar isso
   */
 double horaEent [num_max_vagas],
        horaSai [num_max_vagas],
        permanencia [num_max_vagas];

  /**
   * @var float valor1h | preco da primeira hora
   * @var float valorMais | preco da fracao apos uma hora, fracao de 15 minutos?
   * @var float valorDevido | valor da estadia do veiculo, na saida
   * @var float totalDia | total do dia
   */
 float valor1h,
       valorMais,
       valorDevido,
       totalDia;

/** inicio do fluxo:
    zera totaldo dia,
    zera vetor de vagas ocupadas */

 totalDia=0;

 for(j=0;j<num_max_vagas;j++)
   {
   carroLI[j]=0;
   }

 do
   {
   printf ("\n\n");
   printf ("\n\t\t******************************");
   printf ("\n\t\t* Estacionamento PIM-Park IV *");
   printf ("\n\t\t*          Bem-Vindo!        *");
   printf ("\n\t\t******************************\n\n\n");

   do
     {
      /** conta vagas livres */
      vagasLivres = num_max_vagas;
      for (j=0;j<(num_max_vagas-1);j++) if (carroLI[j]!=0) vagasLivres-=1;

      printf ("\n    Vagas Livres: %d    Total de vagas: %d\n\n", vagasLivres, numTotVagas);
      if (vagasLivres==0) printf ("\n\n\t\tNÃO HÁ VAGAS.\n\n");

      printf ("\n\n    Escolha a funcao\n");
      printf ("\n\tE - Entrada de Veiculo");
      printf ("\n\tS - Saida de Veiculo");
      printf ("\n\tF - Fechamento do Dia");
      printf ("\n\tX - Encerrar SEM fechar o dia");
      printf ("\n\t\t\t\t\t Opcao -> ");

      opt1 = getchar();

      if ((opt1=='F')||(opt1=='f'))
        {
        printf ("\n\n\t FUNÇÃO AINDA NÃO IMPLEMENTADA.\n\nPressione qualquer tecla para continuar\n");
        }

      if ((opt1=='X')||(opt1=='x'))
         {
         printf ("\n\tTEM CERTEZA QUE QUER SAIR SEM FAZER O FECHAMENTO DO DIA?");
         printf ("\n\t\tS = Sim, tenho certeza\n\t\tN = Voltar ao inicio-> ");
         if ((getchar()=='S')||(getchar()=='s')) exit (EXIT_SUCCESS);
         }
     }
    while ((opt1!='E') && (opt1!='S') && (opt1!='e') && (opt1!='s'));

    if ((opt1=='E')||(opt1=='e')) /** Inicio do bloco de entrada de veiculos*/
      {
      do
        {
        if (vagasLivres==0) printf ("\n\n\t\tNÃO HÁ VAGAS.\n\n");
        else
          {
          for (j=7;j<=0;j--) if (carroLI==0) aux = j;   /** procura vaga livre */
          j = aux;

          printf ("\n    Carro entrando\n\tDigite a placa:  ");
          scanf ("%s", &carroPlaca);

/** A linha abaixo converte letras minusculas em maiusculas, importante para
    permitir a conversao da placa em long int, pela funcao str2int (abaixo).*/

          for (i=0;i<3;i++) if (carroPlaca[i]>=97 && carroPlaca[i]<=122) carroPlaca[i] -= 32;

          carroPlaca[7] = '\0'; /** Garante que o ultimo caracter da string sera '\0'.   */

          printf ("\n    Placa-> %s", carroPlaca);

///** A funcao chackPlaca, abaixo, verifica se a string fornecida corresponde a uma placa válida */

          if (checkPlaca(carroPlaca)!=0)
            {
            printf ("\n\n\tESTA NÃO É UMA PLACA VÁLIDA. \n\n");
            printf ("\n\n\tA = Alterar; V = Voltar ao inicio -> ");
            scanf("%c", &opt1);
            if ((opt1=='A')||(opt1=='a')) opt1 = 'E';
            }
          else
            {
            printf ("\n    C = Confirma; A = Altera -> ");
            scanf("%c", &opt1);
            if ((opt1=='C')||(opt1=='c'))
              {
              carroLI[aux] = str2int(carroPlaca);
              }
            else opt1='E';
            }
          }
        }
      while ((opt1=='E')||(opt1=='e'));
      }
    else /** Inicio do bloco de saida de veiculo*/
      {
      do
        {
        printf ("\n    Carro saindo\n\tDigite a placa:  ");
        scanf  ("%s", carroPlaca);
        for (i=0;i<3;i++) if (carroPlaca[i]>=97 && carroPlaca[i]<=122) carroPlaca[i] -= 32;
        carroPlaca[7] = '\0';

/** A funcao chackPlaca, abaixo, verifica se a string fornecida corresponde a uma placa válida */

        if (checkPlaca(carroPlaca)!=0)
          {
          printf ("\n\n\tESTA NÃO É UMA PLACA VÁLIDA. \n\n");
          printf ("\n\n\tA = Alterar; V = voltar ao inicio -> ");
          scanf("%c", &opt1);
          if ((opt1=='A')||(opt1=='a')) opt1 = 'S';
          }
        else
          {
          printf ("\n    Placa: %s. C = Confirma; A = Altera: ", carroPlaca);
          scanf  ("%c", &opt1);
          if ((opt1=='C')||(opt1=='c'))
             {

/** o laco abaixo procura a placa no vetor de placas */

             for (j=0;j<(num_max_vagas-1);j++)
               if (str2int(carroPlaca)==carroLI[j]) aux = j;
             /* falta calcular valor, imprimir recibo com hora de entrada e de saida, fazer relatório. */
             carroLI[aux]=0;
             }
          }
        }
      while ((opt1=='S')||(opt1=='s'));
      }
   }
  while (opt1!='X');
  return (0);
}

/** a funcao long int str2int (char texto[8]), a seguir, converte texto em um numero (long int),
    substituindo cada caracter pelo sei codigo ASCII correspondente. Funciona apenas para caracteres
    cujo codigo ascii tem dois digitos. Isso permite armazenar a placa em um vetor de long int,
    muito mais fácil de lidar do que uma matriz de char.
    */

long int str2int (char texto[8])
 {
  int ii,
      numChar;
  long int valorConvertido;

  for (ii=0;ii<7;ii++)
    {
    numChar = texto[ii];
    valorConvertido += numChar * (pow(100,ii));
    }
 return (valorConvertido);
 }

  /** a funcao int checkPlaca (char texto[8]) verifica se o texto de
      sete caracteres inserido contém três letras maiusculas seguidas
      de quatro algarismos e retorna 0 se a placa eh valida ou um valor
      maior se for invalida */

int checkPlaca (char texto[8])
 {
/** @var chk | recebe valor 0 se a placa eh valida ou um valor maior se for invalida
    @var ii | indices de posicao dos caracteres no texto */

 int chk=0, ii;

 for (ii=0;ii<3;ii++) if ((texto[ii]<65)||(texto[ii]>90)) chk+=1;
 for (ii=3;ii<7;ii++) if ((texto[ii]<48)||(texto[ii]>57)) chk+=1;
 return (chk);
 }
