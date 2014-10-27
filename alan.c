/**
 *
 * Script para o funcionamento de uma garagem
 * @author Alan Mesquita de Sousa
 * @link https://github.com/alanuhu
 * @version 0.1.3
 *
 * Copyright © Alan Mesquita - 2014
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
#define TOTAL_PARKING_SPACES 5
#define INITIAL_PRICE  25.00
#define TIME_PRICE  5.00

/**
 * Global vars
 * char cars | array de carros
 * char dates | array de datas
 * int remainingSpaces | espaços remanecentes
 */
char cars[TOTAL_PARKING_SPACES][50];
char datesString[TOTAL_PARKING_SPACES][50];
int dates[TOTAL_PARKING_SPACES];
int remainingSpaces = TOTAL_PARKING_SPACES;
int totalValue = 0;

void main()
{
  int parkingOption;

  printf("\033[96m***************************************************** \n");
  printf("**             Bem vindo a nossa garagem           ** \n");
  printf("*****************************************************\033[0m \n");

  while(1) {

    printf("\n\n-----------------------------------------------------\n");
    printf("|    Vagas restantes: \033[93m%d\033[0m    |    Total de vagas \033[93m%d\033[0m    |", remainingSpaces, TOTAL_PARKING_SPACES);
    printf("\n-----------------------------------------------------\n\n");

    parkingOption = parkingOptions();
    if(parkingOption == 1) {
      if(remainingSpaces == 0) {
        printf("\n\n  \033[1;31m Não existe mais vagas na garagem\033[0m\n");
        sleep(2);
        continue;
      }
      addCar();
    }

    if(parkingOption == 2) {
      if(remainingSpaces == TOTAL_PARKING_SPACES) {
        printf("\n\n  \033[1;31m Não existem carros na garagem\033[0m\n");
        sleep(2);
        continue;
      }
      removeCar();
    }

    if(parkingOption == 3) {
        printf("\n\n  \033[92m O valor total do dia é: R$ %d.\033[0m\n\n\n\n", totalValue);
        sleep(2);
        exit(EXIT_SUCCESS);
    }

    if(parkingOption == 0) {
        printf("\n\n  \033[92m Bye!\033[0m\n\n\n\n");
        sleep(2);
        exit(EXIT_SUCCESS);
    }

  }
}

/**
 *
 * Função que retorna a opção selecionada
 * @return int | opção escolhida
 */
int parkingOptions() {
  int output;
  printf("\n\n  Escolha a função\n\n  • 1 - Entrada\n  • 2 - Saída\n  • 3 - Fechamento do Dia\n  • 0 - Encerrar :  ");
  scanf("%d", &output);
  return output;
}

/**
 *
 * Função que adiciona carro
 * @return void
 */
addCar() {
  char carPlate [50];
  int confirmation;
  int i;
  time_t now;
  char buff[20];

  printf("\n  Carro entrando\n\tDigite a placa:  ");
  scanf("%s", carPlate);
  printf("\n  Placa: %s. Confirma? (1 para sim / 2 para nao): ", carPlate);
  scanf("%d", &confirmation);

  if(confirmation == 1) {
    for( i = 0; i <= TOTAL_PARKING_SPACES; ++ i ) {
      if( strlen(cars[i]) == 0 ) {
        strcpy(cars[i], carPlate);
        i = TOTAL_PARKING_SPACES;
      }
    }

    time(&now);
    dates[searchCar(carPlate)] = now;

    remainingSpaces--;

    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
    printf("\n\n    \033[92mCarro adicionado na garagem com a placa: %s, na data %s.\033[0m\n", carPlate, buff);
    sleep(2);
  } else {
    addCar();
  }
}

removeCar() {
  char carPlate [50];
  int confirmation;
  int carFoundIndex;
  time_t now;
  char buff[20];
  float seconds;
  int hoursvalue;

  printf("\n  Carro saindo\n\tDigite a placa:  ");
  scanf("%s", carPlate);
  printf("\n  Placa: %s. Confirma? (1 para sim / 2 para nao): ", carPlate);
  scanf("%d", &confirmation);

  if(confirmation == 1) {
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

      seconds = difftime(now, dates[carFoundIndex]);
      hoursvalue = calcHoursValue(seconds);
      printf("\n\n    \033[92mCarro removido da garagem com a placa: %s na data %s e se passaram %f horas e o valor foi R$ %d.\033[0m\n",
          carPlate,
          buff,
          seconds/3600,
          hoursvalue
      );
      totalValue += hoursvalue;
      strcpy(cars[carFoundIndex], "");
      dates[carFoundIndex] = 0;
      remainingSpaces++;
      sleep(2);
    }

  } else {
    removeCar();
  }
}

listCar() {
  int i;

  printf("\n\t---------------------------------\n");
  printf("\t|  \033[95mLista de placas disponiveis\033[0m  |\n");
  printf("\t---------------------------------\n");
  printf("\t|    \033[93mplaca\033[0m   |  \033[93mhora de entrada\033[0m |\n");
  printf("\t---------------------------------\n");
  for( i = 0; i <= TOTAL_PARKING_SPACES; ++ i ) {
    if( strlen(cars[i]) != 0 ) {
      printf("\t|  %8s  |    %d    |\n", cars[i], dates[i]);
      printf("\t---------------------------------\n");
    }
  }
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
  for( i = 0; i <= TOTAL_PARKING_SPACES; ++ i ) {
    if( strcmp(cars[i], carPlate) == 0 ) {
      output = i;
    }
  }
  return output;
}

int calcHoursValue(int seconds) {
  return INITIAL_PRICE + (floor(seconds/3600) * TIME_PRICE);
}
