/**
 *
 * Script para o funcionamento de uma garagem
 * @authors Alan Mesquita de Sousa & Jorge Rodolfo Lima
 * @link https://github.com/alanuhu
 * @version 0.1.3
 *
 * Copyright © Alan Mesquita & Jorge Rodolfo Lima- 2014
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

/**
 * const int TOTAL_SLOTS | numero total de espaços na garagem
 * const float INITIAL_PRICE | preço da primeira hora
 * const float TIME_PRICE | preço das demais horas
 */
#define TOTAL_SLOTS 3
#define INITIAL_PRICE  20.00 /** Valor da primeira hora */
#define TIME_PRICE  2.00     /** Valor da fração adicional de 15 min */

/** Declaracao de funcoes
 * int checkPlate | verifica se a placa fornecida eh valida
 * int searchCar | busca uma placa no vetor de carros
 * long int absTimeNow | retorna a hora absoluta atual
 * char parkingOptions | oferece menu retorna opcao
 * float calcValue | recebe o tempo de permanência em muntos e retorna o valor
 * void addCar | fluxo de entrada de carro da garagem
 * void carList | apresenta uma lista das placas do carros na garagem
 * void removeCar | fluxo de saida de carro da garagem
 * void makeReportFile | cria o arquivo para relatorio (formato YYYY-MM-DD.txt) e inclui cabecalho inicial
 * void presentDate | recebe a hora absoluta e imprime a data formatada em dd.mm.YYYY
 * void printEntrySlip | imprime o canhoto de entrada na impressora lpt1
 * void printExitSlip | imprime o recibo de saida na impressora lpt1
 * void convertTime | recebe a hora absoluta e imprime a hora formatada em HH:MM
*/
int checkPlate (char text[8]);
int searchCar(char *carPlate);
int countFreeSlots ();
long int absTimeNow();
char parkingOptions();
float calcValue(int mins);
void addCar();
void carList();
void removeCar();
void makeReportFile();
void presentDate (long int, int );
void convertTime (long int, int );
void printEntrySlip (char text[8], long int);
void printExitSlip(char text[8], long int, long int, int , float);

/**
 * Global vars
 * char carInSlot | array de carros
 * char dates | array de datas
 * float totalValue | arrecadação total do dia
 * fileP | apontador pro arquivo de saida
 */
char carInSlot[TOTAL_SLOTS][8],
     reportFileName [15];
long int entryTime[TOTAL_SLOTS];
float totalValue = 0.00;
FILE* fileP;


void main()
{
  char opt1;
  int i, opt;

  for (i=0;i<TOTAL_SLOTS;i++) { /** "Zera" os vetores a serem utilizados " */
      carInSlot[i][0]='\0';
      entryTime[i]=0;
      }
  makeReportFile();      /** cria e abre o arquivo e saída e armazena o nome do arquivo em reportFileName[15] */

  printf("*****************************************************\n");
  printf("**             Bem vindo a nossa garagem           **\n");
  printf("*****************************************************\n");

  while(1) {

    printf("\n-----------------------------------------------------");
    printf("\n|    Vagas restantes: %d    |    Total de vagas %d    |", countFreeSlots(), TOTAL_SLOTS);
    printf("\n-----------------------------------------------------\n\n");
    if(countFreeSlots()==0) {
        printf("\n\n   NAO HA VAGAS");
        }
    opt1 = parkingOptions();

    switch (opt1) {
    case '1' :
        if(countFreeSlots() == 0) {
          printf("\n\n   NAO HA VAGAS");
          sleep(2);
          continue;
          }
        else addCar();
        break;

    case '2' :
      if(countFreeSlots() == TOTAL_SLOTS) {
          printf("\n\n   Nao ha carros na garagem\n");
          sleep(2);
          continue;
          }
      else removeCar();
      break;

    case '3' :
      printf("\n\n\t\tSUBTOTAL DO DIA: R$ %.2f.\n\n", totalValue);
      printf ("\n\nDeseja encerrar o dia? (1 = Sim / 2 = Nao): ");
      scanf ("%d", &opt);
      if (opt==1) {
          fprintf (fileP, "\n\t\t\t\tTOTAL DO DIA: R$ %.2f", totalValue);
          fclose(fileP);
          printf("\n\n\t\t Ate logo!\n\n\n\n");
          sleep(1);
          exit(EXIT_SUCCESS);
          }
      else {
          sleep(2);
          continue;
          }
      break;

    case '4' :
      carList();
      if(countFreeSlots() == TOTAL_SLOTS) {
          printf("\n\tGaragem vazia");
          }
      else if (countFreeSlots() == 0 ) {
      printf("\n\tNAO HA VAGAS");
          }
      sleep(2);
      break;

    case'0' :
      printf ("\n\tTEM CERTEZA QUE DESEJA SAIR SEM FAZER O FECHAMENTO?");
      printf ("\n\tTodos os dados serao perdidos!\n\t\t\t(0 = Sim / 2 = Nao): ");
      scanf ("%d", &opt);
      if (opt==0) {
          printf("\n\n\t Ate logo!\n\n\n\n");
          sleep(2);
          exit(EXIT_SUCCESS);
          }
      break;
    }
  }
 return;
}

/**
 *
 * Funcao que retorna a opção selecionada
 * @return int | opcao escolhida
 */
char parkingOptions() {
  char opt1[2];
  printf("\n\n  Escolha a tarefa:\n\n  * 1 - Entrada\n  * 2 - Saida\n  * 3 - Fechamento do Dia - Subtotal\n");
  printf("  * 4 - Lista de carros na garagem\n  * 0 - Encerrar\t\t --> ");
  scanf ("%s", &opt1);
  opt1[1]='\0';  /** Evita alguns problemas caso o usuario digite varios caracteres ao inves de apenas um*/
  return opt1[0];
}

/**
 *
 * Função que adiciona carro
 * @return void
 */
void addCar() {
  char carPlate [8];
  int aux, i, opt;

  printf("\n  Carro entrando\n\tDigite a placa:  ");
  scanf("%s", carPlate);
  for (i=0;i<3;i++) {
      if (carPlate[i]>=97 && carPlate[i]<=122) {
          carPlate[i] -= 32; /** Passa as letras da placa do carro para maiusculas*/
          }
      }
  printf("\n  Placa: %s. Confirma? (1 para sim / 2 para nao): ", carPlate);
  scanf("%d", &opt);
  if (opt != 1) {
      return;
      }
  else {
      while (checkPlate(carPlate)>0) {
          printf (" (Tecle: 1 para corrigir / 2 para voltar): ");
          scanf ("%d", &opt);
          if (opt != 1) {
            return;
            }
          else {
            addCar();
            return;
            }
          }
      }
    for( i = TOTAL_SLOTS; i >=0; i-- ) {
      if( carInSlot[i][0] == '\0' ) {
        aux=i;
      }
    }
    strcpy(carInSlot[aux], carPlate);
    entryTime[aux] = absTimeNow();
    printf("\n\n\tEntrada:\n\tCarro placa: %s\n\tData: ", carPlate);
    presentDate(entryTime[aux],1);
    printf ("Hora: ");
    convertTime(entryTime[aux],1);
    printEntrySlip (carPlate, entryTime[aux]);
    sleep(1);
  }


void removeCar() {
  char carPlate [8],
       buff[20];
  int minutes,
      opt,
      carFoundIndex,
      aux, i;
  time_t now;
  float hoursValue;
  long int exitTime;

  printf("\n  Carro saindo\n\tDigite a placa:  ");
  scanf("%s", carPlate);
  for (i=0;i<3;i++) {
      if (carPlate[i]>=97 && carPlate[i]<=122) {
          carPlate[i] -= 32;       /** Passa as letras da placa do carro para maiusculas*/
          }
      }
  carPlate[7] = '\0';              /** encerra a string carPlate na 8a. posição*/

  carFoundIndex = searchCar(carPlate);
  if(carFoundIndex == -1) {
    printf("\n\n   Nenhum carro encontrado com a placa: %s\n", carPlate);
    sleep(1);
    carList();
    sleep(2);
    removeCar();
    }
  else {
    aux = searchCar(carPlate);
    exitTime = absTimeNow();
    minutes = (exitTime/60)-(entryTime[aux]/60);
    hoursValue = calcValue(minutes);
    printf ("\n\n\tCarro placa: %s \tData: ", carPlate);
    presentDate(entryTime[aux],1);
    printf ("\n\tEntrada: ");
    convertTime(entryTime[aux],1);
    printf ("\t  Saida: ");
    convertTime(exitTime,1);
    printf ("\n\tEstadia: %dh %dmins.\n\tValor: R$ %.2f.\n", minutes/60, minutes%60, hoursValue);
    printf ("\n\t Confirma? ( 1 para Sim / 2 para Corrigir / 3 para Voltar): ");
    scanf ("%d", &opt);
    if (opt== 1) {
      totalValue += hoursValue;
      fprintf (fileP, "%s\t",carPlate);
      convertTime(entryTime[i],0);
      fprintf (fileP, "\t");
      convertTime(exitTime,0);
      fprintf (fileP, "\t%2dh %2dmin\tR$ %6.2f\tR$ %6.2f\n",minutes/60, minutes%60,hoursValue,totalValue);
      printExitSlip(carPlate, entryTime[i], exitTime, minutes, hoursValue);
      entryTime[aux] = 0;
      carInSlot[aux][0] = '\0';
      sleep(1);
      }
   else if (opt==2) removeCar();
   }
  return;
}

void carList() {
  int i;

  printf("\n\t-------------------------------------------");
  printf("\n\t|            Carros na Garagem            |");
  printf("\n\t-------------------------------------------");
  printf("\n\t|  vaga  |   placa    |  hora de entrada  |");
  printf("\n\t-------------------------------------------");
  for (i=0;i<TOTAL_SLOTS;i++) {
   if ((carInSlot[i][0]) != '\0' ) {
      printf("\n\t|   %2d   |  %8s  |      ", i+1, carInSlot[i]);
      convertTime (entryTime[i],1);
      printf ("       |\n");
      printf("\t-------------------------------------------");
    }
  }
 return;
}

/**
 *
 * Procura pela placa no @array carInSlot
 *
 * @params char | placa do carro
 * @return int | indice da placa no array
 */
int searchCar(char *carPlate) {
  int output =-1, i;
  for( i = 0; i < TOTAL_SLOTS; i++ ) {
    if( strcmp(carInSlot[i], carPlate) == 0 ) {
      output =i;
    }
  }
  return output;
}

float calcValue(int mins) {
 int fractions; /** fracoes de 15 minutos apos uma hora*/
 float finalValue;
 if (mins<=5) finalValue = 0.0;  /**tolerancia de 5 minutos sem cobrar */
 else if (mins<=60) finalValue = INITIAL_PRICE;
 else
   {
   if (mins%15==0) fractions = (mins-60)/15;
   else fractions = 1 + ((mins-60)/15);
   finalValue = INITIAL_PRICE + (TIME_PRICE*fractions);
   }
return (finalValue);
}

 /**
 *
 * cria o nome do arquivo de saida com o padrão: YYYY-MM-DD.rtf,que aber também como planilha
 * separada por tabulações. Escreve o cabecalho do arquivo, com data e hora de inicio do sistema
 */

void makeReportFile () {

int i;
char buff [20];
long int today;

  today = absTimeNow();
  strftime (buff, 11, "%Y-%m-%d", localtime(&today));
  for (i=0;i<10;i++) {
      reportFileName[i]=buff[i];
      }
  strcat (reportFileName, ".rtf");
  reportFileName[15]='\0';
  fileP = fopen (reportFileName, "w");   /** abre o arquivo de saída */
  fprintf (fileP, "Sistema aberto em (data e hora): ");
  strftime (buff, 20, "%d.%m.%Y  %H:%M h", localtime(&today));
  fprintf(fileP, "%s",buff);
  fprintf (fileP, "\nPlaca\tEntrada\tSaida\tPermanencia\tValor Pago\tSubtotal\n", buff);
  return;
  }


/** a funcao countFreeSlots retorna o número de vagas livres no estacionamento
    */
int countFreeSlots ()
{
int i, output = 0;
for (i=0;i<(TOTAL_SLOTS);i++) if (carInSlot[i][0]=='\0') output+=1;
return (output);
}

/** Verifica se a placa fornecida eh uma placa valida (3 letras seguidas de 4 algarismos)
 * e verifica se a mesma placa ja nao esta inserida no sistema;
 * @var output | recebe valor 0 se a placa eh valida ou um valor maior se for invalida
 * @var ii | indices de posicao dos caracteres no texto */

int checkPlate (char text[8])
 {
 int output=0, i;

 for (i=0;i<3;i++) if ((text[i]<65)||(text[i]>90)) output+=1;
 for (i=3;i<6;i++) if ((text[i]<48)||(text[i]>57)) output+=1;
 if (text[7]!='\0') output+=1;
 if (output>0) {
  printf ("\n\t%s - PLACA INVALIDA. ", text);
  return (output);
  }
 else if (searchCar(text)>=0) {
    printf ("\n\t%s - CARRO JA INSERIDO NA VAGA %d. \n\t\t", text, 1+searchCar(text));
    output +=1;
    }
 return (output);
 }

 /** a funcao presentDate recebe uma hora absoluta e imprime a data formatada
    (DD.MM.YYY). Se o parametro int a eh maior que 0, ela imprime na tela,
    senao, imprime no arquivo de relatorio */


void presentDate (long int anyTime, int a)
  {
  char buff [20];

  strftime (buff, 11, "%d.%m.%Y", localtime(&anyTime));
  if (a>0) printf ("%s ", buff);
  else fprintf (fileP, "%s ", buff);
  return;
}

/** a funcao presentDate (long int, anytime) recebe a uma hora absoluta e imprime a hora formatada
    (HH:MM). Se o parametro int a eh maior que 0, ela imprime na tela,
    senao, imprime no arquivo de relatorio */

void convertTime(long int anyTime, int a)
  {
  char buff [20];
  strftime (buff, 8, " %H:%M", localtime(&anyTime));
  if (a>0) printf ("%s",buff);
  else fprintf (fileP, "%s",buff);
  return;
}

/** a funcao absTimeNow() retorna o tempo absoluto, em segundos, desde 21:00:00 de 20.nov.1969 */

 long int absTimeNow()
{
    time_t absTimeSec;
    absTimeSec = time(NULL);
    return (absTimeSec);
}

void printEntrySlip(char text[8], long int inTime)
{
FILE *prnt;
char buf1 [14];
char buf2 [8];
char plate [8];

  strftime (buf1, 12, "%d.%m.%Y", localtime(&inTime));
  strftime (buf2, 7, "%H:%M", localtime(&inTime));

prnt = fopen("lpt1", "w");

fprintf (prnt, "************************************\n");
fprintf (prnt, "**    Bem vindo a nossa garagem   **\n");
fprintf (prnt, "************************************\n\n");
fprintf (prnt, "------------------------------------\n");
fprintf (prnt, "Data: %s | Entrada: %s\n", buf1, buf2);
fprintf (prnt, "------------------------------------\n");
fprintf (prnt, "Não nos responsabilizamos por ");
fprintf (prnt, "pertences deixados no veiculo\n\n");
fprintf (prnt, "Funcionamento das 06h as 22h\n");
fprintf (prnt, "De Segunda-Feira a Sabado \n");
fprintf (prnt, "Nao trabalhamos com pernoite\n\n");
fprintf (prnt, "     Agradecemos a preferencia\n");
fprintf (prnt, "------------------------------------\n");

fprintf (prnt, "\f");

fclose (prnt);

return (0);

}

void printExitSlip(char text[8], long int inTime, long int outTime, int mins, float pay)
{
FILE *prnt;
char buf1 [14];
char buf2 [8];
char buf3 [8];
char plate [8];

  strftime (buf1, 12, "%d.%m.%Y", localtime(&inTime));
  strftime (buf2, 7, "%H:%M", localtime(&inTime));
  strftime (buf3, 7, "%H:%M", localtime(&outTime));

prnt = fopen("lpt1", "w");

fprintf (prnt, "************************************\n");
fprintf (prnt, "**    Bem vindo a nossa garagem   **\n");
fprintf (prnt, "************************************\n\n");
fprintf (prnt, "------------------------------------\n");
fprintf (prnt, "Data: %s | Entrada: %s\n", buf1, buf2);
fprintf (prnt, "------------------------------------\n");
fprintf (prnt, "                 | Saida: %s\n");
fprintf (prnt, "------------------------------------\n");
fprintf (prnt, "Permanencia: %dh %dm Valor: R$ %6.2f\n\n", mins/60, mins%60, pay);
fprintf (prnt, "------------------------------------\n");
fprintf (prnt, "Favor verificar seu troco\n\n");
fprintf (prnt, "Funcionamento das 06h as 22h\n");
fprintf (prnt, "De Segunda-Feira a Sabado \n");
fprintf (prnt, "Nao trabalhamos com pernoite\n\n");
fprintf (prnt, "     Agradecemos a preferencia\n\n");
fprintf (prnt, "------------------------------------\n");

fprintf (prnt, "\f");

fclose (prnt);

return (0);

}
