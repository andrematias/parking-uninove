/**
 *
 * Prototipo de tela de input - PRECISA SER MUITO MELHORADO!!!
 * desenvolvido por J. Rodolfo Lima
 * ADS-Unip - PIM IV - OUTUBRO, 2014
 */
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define num_max_vagas 10 /** numero total de vagas */
#define valor1h 20 /** valor da primeira hora */
#define valor15min 2 /** valor de de cada 15 min apos a primeira hora */

/** funcoes:
        main: gerencia entrada e saida de veiculos e o "fechamento do dia"
        int relatorio: gera os relatorio diário em arquivo e impresso.
        int str2int (char texto[8]): converte a placa do carro em int, usando o valor ASCII de cada caracter
        int checkPlaca: Verifica se a cadeia fornecida corresponde a uma placa valida
        long int horaAbsMin: retorna a hora absoluta atual em minutos
        float calcValor: retorna o valor da estadia
*/

int relatorio ();
int checkPlaca (char texto[8]);
long int str2int (char texto[8]);
long int horaAbsMin();
float calcValor(int);


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
   * @var int j : indice de o vetor
   * @var aux = variavel auxiliar para diversos usos
   */

 int vagasLivres = num_max_vagas,
     aux, i;

  /**
   * @var long int carroLI : placa do carro covertida para long int
   * @var long int horaMinEntra : hora absoluta de entrada, em minutos
   * @var lonh int horaMinSai : hora absoluta de saida, em minutos
   */

 long int carroLI [num_max_vagas],
          horaMinEntra [num_max_vagas],
          horaMinSai;

  /**
   * @var float valor1h | preco da primeira hora
   * @var float valorMais | preco da fracao apos uma hora, fracao de 15 minutos.
   * @var float valorDevido | valor da estadia do veiculo, na saida
   * @var float totalDia | total do dia
   */
 float valorDevido,
       totalDia;

/** inicio do fluxo:
    zera totaldo dia,
    zera vetor de vagas ocupadas */

 totalDia=0;

 for(i=0;i<num_max_vagas;i++)
   {
   carroLI[i]=0;
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
      for (i=0;i<(num_max_vagas);i++) if (carroLI[i]!=0) vagasLivres-=1;

      printf ("\n    Vagas Livres: %d    Total de vagas: %d\n\n", vagasLivres, num_max_vagas);
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
          for (i=7;i<=0;i--) if (carroLI==0) aux = i;   /** procura vaga livre */

          printf ("\n    Carro entrando\n\tDigite a placa:  ");
          scanf ("%s", &carroPlaca);

/** A linha abaixo converte letras minusculas em maiusculas, importante para
    permitir a conversao da placa em long int, pela funcao str2int (abaixo).*/

          for (i=0;i<3;i++) if (carroPlaca[i]>=97 && carroPlaca[i]<=122) carroPlaca[i] -= 32;

          carroPlaca[7] = '\0'; /** Garante que o ultimo caracter da string sera '\0'.   */

          printf ("\n    Placa-> %s", carroPlaca);

          if (checkPlaca(carroPlaca)!=0) /** Verifica se a cadeia corresponde a uma placa válida */
            {
            printf ("\n\n\tESTA NÃO É UMA PLACA VÁLIDA. \n\n");
            printf ("\n\n\tA = Alterar; V = Voltar ao inicio -> ");
            scanf("%c", &opt1);
            if ((opt1=='A')||(opt1=='a')) opt1 = 'E';
            }
          else
            {
            printf ("\n    Confirma? S/N -> ");
            scanf("%c", &opt1);
            if ((opt1=='s')||(opt1=='S'))
              {
/** Insere o carro no sistema */

              carroLI[aux] = str2int(carroPlaca);
              horaMinEntra[aux] = horaAbsMin();
              opt1='V';

/*FALTA IMPLEMENTAR O RECIBO!!*/

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

/** o laco abaixo procura a placa no vetor de placas */
          aux=0;
          for (i=0;i<(num_max_vagas);i++) if (str2int(carroPlaca)==carroLI[i]) aux = i;
/** caso o veiculo não esteja registrado no sistema:  */
          if (aux == 0)
             {
             printf ("\nPlaca nao registrada no sistema. \n\t\t\tTecle A = Alterar; C = Cancelar: ");
             scanf ("%c", &opt1);
             if ((opt1=='A')||(opt1=='a')) opt1 = 'S';
             else opt1 = 'V';
             }
          else
             {
             horaMinSai = horaAbsMin();
             valorDevido = calcValor(horaMinSai-horaMinEntra[aux]);
             printf ("\n\tPermanência: %ldh ", (horaMinSai-horaMinEntra[aux])/60);
             printf("%ldmin Valor: R$%f", (horaMinSai-horaMinEntra[aux])%60, valorDevido);
             printf ("\n\tConfirma? S = sim ; N = não -> ");
             scanf ("%c", &opt2);
             if ((opt2=='S')||(opt1=='s'))
                {
            /* falta imprimir recibo com hora de entrada e de saida e fazer relatório. */
                carroLI[aux]=0;
                }
             else opt1 = 'V';
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

  /** a funcao horaAbsMin() retorna a hora atual em minutos transcorridos
      desde a Epoch (hora absoluta em minutos) */

 long int horaAbsMin()
{
    time_t horaMinAtual;

    /** a linha abaixo recebe a hora atual,em segundos, desde Epoch: */

    horaMinAtual = time(NULL);

    /** e esta retorna a hora atual, em MINUTOS, desde Epoch: */

    return (horaMinAtual/60);
}

 /** a funcao calcValor retorna a hora atual em minutos transcorridos
      desde a Epoch (hora absoluta em minutos) */

float calcValor(int mins)
{
 int fracs; /** fracoes de 15 minutos apos uma hora*/
 float valFinal;
 if (mins<=60) valFinal = valor1h;
 else
   {
   if (mins%15==0) fracs = (mins-60)/15;
   else fracs = 1 + ((mins-60)/15);
   valFinal = valor1h + (valor15min*fracs);
   }

return (valFinal);
}
