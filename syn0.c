/**
 *
 * Sistema para Gerenciar um estacionamento
 * @authors Alan Mesquita de Sousa & Jorge Rodolfo Lima
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <math.h>

/**
 * const int TOTAL_SLOTS | numero total de vagas
 * const float INITIAL_PRICE | valor da primeira hora
 * const float TIME_PRICE | valor da fracao adicional de 15 min
 */
#define TOTAL_SLOTS 4
#define INITIAL_PRICE  20.00
#define TIME_PRICE  3.00

/** Declaracao de funcoes
 * int checkPlate | verifica se a placa fornecida eh valida
 * int searchCar | busca uma placa no vetor de carros
 * int countFreeSlots () | conta as vagas livres
 * int nextFreeSlot | retorna o indice da proxima vaga livre
 * long int str2int (char texto[8]) | converte a placa do carro em int codificado
 * long int absTimeNow | retorna a hora absoluta atual
 * char parkingOptions | oferece menu retorna opcao
 * float calcValue | recebe o tempo de permanência em muntos e retorna o valor
 * void addCar | fluxo de entrada de carro da garagem
 * void carList | apresenta uma lista das placas do carros na garagem
 * void removeCar | fluxo de saida de carro da garagem
 * void makeReportFile | cria e abre o arquivo de relatorio (formato YYYY-MM-DD.txt)
 * void presentDate | retorna uma hora absoluta e imprime a data formatada em dd.mm.YYYY
 * void convertTime | recebe uma hora absoluta e imprime a hora formatada em HH:MM
*/


int checkPlate (char text[8]);
int searchCar(char text[8]);
int countFreeSlots ();
int nextFreeSlot ();
long int str2int (char text[8]);
long int absTimeNow();
char parkingOptions();
float calcValue(int);
void addCar();
void carList();
void removeCar();
void makeReportFile();
void int2plate (long int);
void presentDate (long int, int);
void convertTime(long int, int);

/**
 * Global vars
 * char cars | array de carros
 * char dates | array de datas
 * int freeSlots | espacos remanecentes
 * float totalValue | arrecadacao total do dia
 * fileP | apontador pro arquivo de saida
 */
char reportFileName [15],
     buff[20];
long int carInSlot[TOTAL_SLOTS],
         entryTime[TOTAL_SLOTS];
float totalValue = 0.00;
FILE* fileP;

void main()
{
  char option;
  int i;

  for (i=0;i<TOTAL_SLOTS;i++) { /** "Zera" os vetores a serem utilizados " */
      entryTime[i]=0;
      carInSlot[i]=0;
      }
  carInSlot[0] = 52515049688365;
  carInSlot[1] = 52515049688366;
  carInSlot[2] = 52515049688367;
  carInSlot[3] = 52515049688368; /*
  carInSlot[10] = 52515049688369;
  carInSlot[5] = 52515049688370;
  carInSlot[11] = 53515049688365;
  carInSlot[7] = 53515049688366;
  carInSlot[8] = 53515049688367;
  carInSlot[9] = 53515049688368;
  carInSlot[12] = 53515049688369; */
  entryTime[0] = (absTimeNow()-8437);
  entryTime[1] = (absTimeNow()-7681);
  entryTime[2] = (absTimeNow()-7908);
  entryTime[3] = (absTimeNow()-7152);/*
  entryTime[10] = (absTimeNow()-7379);
  entryTime[5] = (absTimeNow()-6623);
  entryTime[11] = (absTimeNow()-6850);
  entryTime[7] = (absTimeNow()-120);
  entryTime[8] = (absTimeNow()-6321);
  entryTime[9] = (absTimeNow()-5565);
  entryTime[12] = (absTimeNow()-5792);*/

  makeReportFile();      /** cria e abre o arquivo e saída e armazena o nome do arquivo em reportFileName[15] */

  printf("*****************************************************\n");
  printf("**           BEM VINDO A NOSSA GARAGEM!            **\n");
  printf("*****************************************************\n\n");

  while(1) {

    printf("\n----------------------------------------------------");
    printf("\n|    Vagas livres: %2d    |    Total de vagas %2d    |", countFreeSlots(), TOTAL_SLOTS);
    printf("\n----------------------------------------------------\n\n");
    if(countFreeSlots() == 0) {
        printf("\n\n\tNAO HA VAGAS\n");
        }
    option = parkingOptions();

    switch (option) {
    case '1' :
        if(countFreeSlots() == 0) {
          printf("\n\n\tNAO HA VAGAS\n");
          sleep(1);
          parkingOptions();
          }
        else addCar();
        break;

    case '2' :
      if(countFreeSlots() == TOTAL_SLOTS) {
        printf("\n\n\t Estacionamento vazio\n");
        sleep(1);
        parkingOptions();
        }
      else removeCar();
      break;

    case '3' :
      printf("\n\n\tValor total do dia: R$ %.2f.\n\n\n", totalValue);
      printf ("\n\nDeseja encerrar o dia? (1 = Sim/ 2 = Nao): ");
      scanf ("%s", &option);
      if (option=='1') {
          fprintf (fileP, "\n\t\t\t\t\tTOTAL DO DIA: R$ %.2f", totalValue);
          fclose(fileP);
          printf("\n\n\t\tAte logo!\n\n");
          sleep(1);
          exit(EXIT_SUCCESS);
          }
      else {
          parkingOptions();
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
      break;

    case'0' :
      printf ("\n\tTEM CERTEZA QUE DESEJA SAIR SEM FAZER O FECHAMENTO?");
      printf ("\n\tTodos os dados serao perdidos!\n\t\t\t(0 = Sim / 2 = Nao): ");
      scanf ("%s", &option);
      if (option!='0') {
          parkingOptions();
          }
      else {
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
 * Funcao que retorna a opcao selecionada
 * @return int | opcao escolhida
 */
char parkingOptions() {
  char output[2];
  printf("\n\n  Escolha a tarefa:\n\n  * 1 - Entrada\n  * 2 - Saida\n  * 3 - Fechamento do Dia / Subtotal\n  * 4 - Lista carros estacionados\n  * 0 - Encerrar :  ");
  scanf ("%s", &output);
  output[1]='\0';  /** Evita alguns problemas caso o usuario digite varios caracteres ao inves de apenas um*/
  return output[0];
}


/**
 *
 * Funcao que adiciona carro
 * @return void
 */
void addCar() {
  char carPlate [8],
       opt;
  int i;

  printf("\n\tCarro entrando\n\tDigite a placa:  ");
  scanf("%s", carPlate);
  for (i=0;i<3;i++) {
    if (carPlate[i]>=97 && carPlate[i]<=122) {
      carPlate[i] -= 32; /** Passa as letras da placa do carro para maiusculas*/
      }
    }
  while (checkPlate(carPlate)>0) {
      printf (" (Tecle: 1 para corrigir / 2 para voltar): ");
      scanf ("%s", &opt);
      if (opt != '1') {
        return;
        }
      else {
        addCar();
        return;
        }
    }
  printf("\n\tPlaca: %s. Confirma? (1 para sim / 2 para nao): ", carPlate);
  scanf("%s", &opt);
  if (opt != '1') {
    return;
    }
  else {
    i = nextFreeSlot();
    printf ("\n\tVaga %d ocupada", i+1);
    carInSlot[i] = str2int(carPlate);
    entryTime[i] = absTimeNow();
    printf("\n\n\tEntrada:\n\tCarro placa: %s\n\tData: ", carPlate);
    presentDate(absTimeNow(),1);
    printf ("Hora: ");
    convertTime(absTimeNow(),1);
    printf ("\n\tentryTime = %ld\n\t codigo da placa: %ld\n", entryTime[i], carInSlot[i]);
    sleep(2);
    }
  return;
}
void removeCar() {
  char carPlate [8],
       opt;
  char buff[20];
  int i, aux,
      minutes;
  long int exitTime;
  float hoursValue;

  printf("\n  Carro saindo\n\tDigite a placa:  ");
  scanf("%s", carPlate);
  for (i=0;i<3;i++) {
    if (carPlate[i]>=97 && carPlate[i]<=122) {
      carPlate[i] -= 32;       /** Passa as letras da placa do carro para maiusculas*/
      }
    }
  carPlate[7] = '\0';              /** encerra a string carPlate na 8a. posicao*/
  if (searchCar(carPlate)<0) {
    printf("\n\n\tNenhum carro encontrado com a placa: %s\n", carPlate);
    sleep(1);
    carList();
    parkingOptions();
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
    scanf ("%s", &opt);
    if (opt=='1') {
        totalValue += hoursValue;
        fprintf (fileP, "%s\t",carPlate);
        convertTime(entryTime[i],0);
        fprintf (fileP, "\t");
        convertTime(exitTime,0);
        fprintf (fileP, "\t%2dh %2dmin\tR$ %6.2f\tR$ %6.2f\n",minutes/60, minutes%60,hoursValue,totalValue);
        entryTime[aux] = 0;
        printf ("\n\tVaga %d Liberada\n\n", 1+searchCar(carPlate));
        carInSlot[aux] = 0;
        sleep(1);
        }
     else if (opt=='2') removeCar();
  }
  return;
}

void carList() {
  int i, j;
  long int aux;
  char text[8];

  printf("\n\t-------------------------------------------");
  printf("\n\t|            Carros na Garagem            |");
  printf("\n\t-------------------------------------------");
  printf("\n\t|  vaga  |   placa   |   hora de entrada  |");
  printf("\n\t-------------------------------------------");
  for (i=0;i<TOTAL_SLOTS;i++) {
    if (carInSlot[i] > 0 ) {
      printf("\n\t|   %2d   |  ", i+1 );
      int2plate(carInSlot[i]);
      printf("  |       ");
      convertTime(entryTime[i],1);
      printf("       |");
    }
  }
  printf("\n\t-------------------------------------------\n");
 return;
}

/**
 *
 * SearchCar procura pela placa no @array cars
 *
 * @params char | placa do carro
 * @return int | indice da placa no array
 */
int searchCar(char text[8]) {
  int i, output=-1;
  long int teste;
  for(i=0;i< TOTAL_SLOTS;i++) {
    teste = str2int(text);
    if (teste==carInSlot[i]) {
      output = i;
      }
    }
  return(output);
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

 /** cria o nome do arquivo de saida com o padrao: YYYY-MM-DD.csv
 * escreve o cabecalho do arquivo, com data e hora de inicio do sistema
 */

void makeReportFile ()
 {

int i;
char buff [20];
long int today;

  today = absTimeNow();
  strftime (buff, 11, "%Y-%m-%d", localtime(&today));
  for (i=0;i<10;i++) {
      reportFileName[i]=buff[i];
      }
  strcat (reportFileName, ".txt");
  reportFileName[15]='\0';
  fileP = fopen (reportFileName, "w");   /** abre o arquivo de saída */
  fprintf (fileP, "Sistema aberto em (data e hora): ");
  strftime (buff, 20, "%d.%m.%Y %H:%M", localtime(&today));
  fprintf (fileP, "\nPlaca\tEntrada\tSaida\tPermanencia\tValor Pago\tSubtotal\n", buff);
  return;
  }

/** a funcao long int str2int (char text[8]), a seguir, converte text em um numero (long int),
    substituindo cada caracter pelo sei codigo ASCII correspondente. Funciona apenas para caracteres
    cujo codigo ascii tem dois digitos. Isso permite armazenar a placa em um vetor de long int,
    muito mais facil de lidar do que uma matriz de char.
    */

long int str2int (char text[8])
 {
  int ii,
      numChar;
  long int output=0;

  for (ii=0;ii<7;ii++)
    {
    numChar = text[ii];
    output += numChar * (pow(100,ii));
    }
 return (output);
 }

/** a funcao countFreeSlots retorna o número de vagas livres no estacionamento
    */

int countFreeSlots ()
{
int i, output = 0;
for (i=0;i<(TOTAL_SLOTS);i++) if (carInSlot[i]==0) output+=1;
return (output);
}

/** a funcao nextFreeSlot retorna o indice da proxima vaga livre */

int nextFreeSlot()
{
int i, output;
for (i=(TOTAL_SLOTS-1);i>=0;i--) {
  if (carInSlot[i]==0) {
    output = i;
    }
  }
return (output);
}

void int2plate (long int inp)
{
int i;
for (i=0;i<7;i++){
  printf("%c", (inp%100));
  inp=inp/100;
  }
return;
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

/** a funcao presentDate recebe a uma hora absoluta e imprime a hora formatada
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

 long int absTimeNow()
{
    time_t absTimeSec;
    absTimeSec = time(NULL);
    return (absTimeSec);
}
