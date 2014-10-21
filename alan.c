/**
 *
 * Protótipo de tela de input - PRECISA SER MUITO MELHORADO!!!
 * desenvolvido por J. Rodolfo Lima
 * ADS-Unip - PIM IV - OUTUBRO, 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/**
 * para teste,começamos com três vagas
 */
#define TOTAL_PARKING_SPACES 10
#define INITIAL_PRICE = 25.00
#define TIME_PRICE = 5.00

/**
 * global vars
 */
char cars[10][50];
int dates[10];

void main()
{

  /*time_t now;
  time(&now);

  dates[2] = now;

  printf("%d", dates[2]);*/

  int parkingOption;

  printf("     Bem vindo a nossa garagem \n");

  while(1) {
    parkingOption = parkingOptions();

    if(parkingOption == 1) {
      addCar();
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
  printf("\n\n    Escolha a função\n\n    (1- Entrada; 2- Saída; 3- Fechamento do Dia; 0 = Encerrar): ");
  scanf("%d", &output);
  return output;
}

/**
 *
 * Função que adiciona carro
 */
addCar() {
  char carPlate [7];
  int confirmation;
  int i;
  time_t now;
  int ueba;

  printf("\n    Carro entrando\n\tDigite a placa:  ");
  scanf("%s", &carPlate);
  printf("\n    Placa: %s. Confirma? (1 para sim / 2 para nao): ", carPlate);
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

  } else {
    addCar();
  }


    for( i = 0; i <= TOTAL_PARKING_SPACES; ++ i ) {
      printf("\n    Placas: %s.", cars[i]);
    }

    for( i = 0; i <= TOTAL_PARKING_SPACES; ++ i ) {
      printf("\n    dataplaca: %d.", dates[i]);
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
