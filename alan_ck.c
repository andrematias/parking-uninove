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
 * const int TOTAL_PARKING_SPACES | numero total de espaços na garagem
 * const float INITIAL_PRICE | preço da primeira hora
 * const float TIME_PRICE | preço das demais horas
 */
#define TOTAL_PARKING_SPACES 3
#define INITIAL_PRICE  20.00 /** Valor da primeira hora */
#define TIME_PRICE  2.00     /** Valor da fração adicional de 15 min */

/** Declaracao de funcoes
*/
int checkPlate (char texto[8]);
int searchCar(char *carPlate);
int parkingOptions();
float calcValue(int mins);
void listCar();
void removeCar();
void addCar();
void main();

/**
 * Global vars
 * char cars | array de carros
 * char dates | array de datas
 * int remainingSpaces | espaços remanecentes
 */
char cars[TOTAL_PARKING_SPACES][8],
     datesString[TOTAL_PARKING_SPACES][50];
int dates[TOTAL_PARKING_SPACES],
    remainingSpaces = TOTAL_PARKING_SPACES;
float totalValue = 0.00;

void main()
{
  int option;
  int i;

  for (i=0;i<TOTAL_PARKING_SPACES;i++)
      {
      cars[i][0]='\0';
      datesString[i][0]='\0';
      }

  printf("\033[96m***************************************************** \n");
  printf("**             Bem vindo a nossa garagem           ** \n");
  printf("*****************************************************\033[0m \n");

  while(1) {

    printf("\n\n-----------------------------------------------------\n");
    printf("|    Vagas restantes: \033[93m%d\033[0m    |    Total de vagas \033[93m%d\033[0m    |", remainingSpaces, TOTAL_PARKING_SPACES);
    printf("\n-----------------------------------------------------\n\n");
    if(remainingSpaces == 0) {
        printf("\n\n  \033[1;31m Não ha vagas na garagem\033[0m\n");
        }
    option= parkingOptions();
    if(option== 1) {
      if(remainingSpaces == 0) {
        printf("\n\n  \033[1;31m Não ha vagas na garagem\033[0m\n");
        sleep(2);
        continue;
      }
      addCar();
    }

    if(option== 2) {
      if(remainingSpaces == TOTAL_PARKING_SPACES) {
        printf("\n\n  \033[1;31m Não existem carros na garagem\033[0m\n");
        sleep(2);
        continue;
      }
      removeCar();
    }

    if(option== 3) {
        printf("\n\n  \033[92m O valor total do dia é: R$ %.2f.\033[0m\n\n\n\n", totalValue);
        sleep(2);
        exit(EXIT_SUCCESS);
    }

    if(option== 0) {
        printf ("\n\tTEM CERTEZA QUE DESEJA SAIR SEM FAZER O FECHAMENTO?");
        printf ("\n\tTodos os dados serao perdidos!\n\t\t\t(0 = Sim / 2 = Não): ");
        scanf ("%d", &option);
        if (option!=0) {
            option=1;
            }
        else {
            printf("\n\n  \033[92m Bye!\033[0m\n\n\n\n");
            sleep(2);
            exit(EXIT_SUCCESS);
            }
    }

  }
 return;
}

/**
 *
 * Função que retorna a opção selecionada
 * @return int | opção escolhida
 */
int parkingOptions() {
  int output;
  printf("\n\n  Escolha a função\n\n  • 1 - Entrada\n  • 2 - Saída\n  • 3 - Fechamento do Dia\n  • 0 - Encerrar :  ");
  scanf ("%d", &output);
  return output;
}

/**
 *
 * Função que adiciona carro
 * @return void
 */
void addCar() {
  char carPlate [8];
  int confirm,
      i;
  time_t now;
  char buff[20];

  printf("\n  Carro entrando\n\tDigite a placa:  ");
  scanf("%s", carPlate);
  for (i=0;i<3;i++) {
      if (carPlate[i]>=97 && carPlate[i]<=122) {
          carPlate[i] -= 32; /** Passa as letras da placa do carro para maiusculas*/
          }
      }
  printf("\n  Placa: %s. Confirma? (1 para sim / 2 para nao): ", carPlate);
  scanf("%d", &confirm);
  if (confirm != 1) {
      return;
      }
  else {
      if (checkPlate(carPlate)!=0)
          {
          printf ("\n PLACA INVALIDA. (Tecle: 1 para corrigir / 2 para voltar): ");
          scanf ("%d", &confirm);
          if (confirm != 1) {
              return;
              }
          else {
              addCar();
              return;
              }
          }
    for (i=0; i<TOTAL_PARKING_SPACES;i++) {
      if( strlen(cars[i]) == 0 ) {
        strcpy(cars[i], carPlate);
        i = TOTAL_PARKING_SPACES;
      }
    }

    time(&now);
    dates[searchCar(carPlate)] = now;

    remainingSpaces--;

    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
    printf("\n\n\t\033[92mEntrada:\n\tCarro placa: %s\n\tData/Hora %s.\033[0m\n", carPlate, buff);
    sleep(2);
  }
}

void removeCar() {
  char carPlate [8];
  int confirm,
      carFoundIndex,
      i;
  time_t now;
  char buff[20];
  int minutes;
  float hoursValue;

  printf("\n  Carro saindo\n\tDigite a placa:  ");
  scanf("%s", carPlate);
  for (i=0;i<3;i++) {
      if (carPlate[i]>=97 && carPlate[i]<=122) {
          carPlate[i] -= 32; /** Passa as letras da placa do carro para maiusculas*/
          }
      }
  carPlate[7] = '\0';                                                            /** encerra a string carPlate na 8a. posição*/
  printf("\n  Placa: %s. Confirma? (1 para sim / 2 para nao): ", carPlate);
  scanf("%d", &confirm);

  if(confirm == 1) {
    carFoundIndex = searchCar(carPlate);
    if(carFoundIndex == -1) {
      printf("\n\n  \033[1;31m Nenhum carro encontrado com a placa: %s\033[0m\n", carPlate);
      sleep(1);
      listCar();
      sleep(2);
      removeCar();
    } else {
      time(&now);
      strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));

      minutes = (difftime(now, dates[carFoundIndex]))/60;
      if (minutes<=5) {                                      /**tolerância de 5 minutos sem cobrar */
          hoursValue = 0;
          }
      else {
          hoursValue = calcValue(minutes);
          }
      printf("\n\033[92m\n\tSaída:\n\tCarro placa: %s \n\tData/Hora %s \n\tPermanencia: %dh %dmins.\n\tValor: R$ %.2f.\033[0m\n",
          carPlate, buff, minutes/60, minutes%60, hoursValue);
      totalValue += hoursValue;
      strcpy(cars[carFoundIndex], "");
      dates[carFoundIndex] = 0;
      remainingSpaces++;
      sleep(2);
    }
  }
  return;
}

void listCar() {
  int i;

  printf("\n\t---------------------------------\n");
  printf("\t|  \033[95mLista de placas disponiveis\033[0m  |\n");
  printf("\t---------------------------------\n");
  printf("\t|    \033[93mplaca\033[0m   |  \033[93mhora de entrada\033[0m |\n");
  printf("\t---------------------------------\n");
  for(i=0; i<TOTAL_PARKING_SPACES;i++) {
    if( strlen(cars[i]) != 0 ) {
      printf("\t|  %8s  |    %d    |\n", cars[i], dates[i]);
      printf("\t---------------------------------\n");
    }
  }
 return;
}

/**
 *
 * Procura pela placa no @array cars
 *
 * @params char | placa do carro
 * @return int | indice da placa no array
 */
int searchCar(char *carPlate) {
  int output = -1, i;
  for (i=0;i<TOTAL_PARKING_SPACES;i++) {
    if( strcmp(cars[i], carPlate) == 0 ) {
      output = i;
    }
  }
  return output;
}

float calcValue(int mins) {
 int fractions; /** fracoes de 15 minutos apos uma hora*/
 float finalValue;
 if (mins<=60) finalValue = INITIAL_PRICE;
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
 * Verifica se a placa fornecida eh uma placa valida
 * (três letras seguidas qye autro algarismos)
 * @var chk | recebe valor 0 se a placa eh valida ou um valor maior se for invalida
 * @var ii | indices de posicao dos caracteres no texto */

int checkPlate (char texto[8])
 {
 int chk=0, ii;

 for (ii=0;ii<3;ii++) if ((texto[ii]<65)||(texto[ii]>90)) chk+=1;
 for (ii=3;ii<6;ii++) if ((texto[ii]<48)||(texto[ii]>57)) chk+=1;
 if (texto[7]!='\0') chk+=1;
 return (chk);
 }
