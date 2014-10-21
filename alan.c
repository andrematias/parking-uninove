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
static const int TOTAL_PARKING_SPACES = 10;
static const float INITIAL_PRICE = 25.00;
static const float TIME_PRICE = 5.00;

/**
 * global vars
 */


void main()
{
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
  char confirmation [7];

  printf ("\n    Carro entrando\n\tDigite a placa:  ");                                                                                                          
  scanf  ("%s", &carPlate);
  printf ("\n    Placa: %s. Confirma? (y/n): ", carPlate);  
  scanf  ("%s", &confirmation);
  printf("\n valores placa: %s confirmacao: %s", carPlate, confirmation);
}
