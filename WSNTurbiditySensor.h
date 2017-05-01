/*
# Example code d'utilisation Turbidity meter V1.0.
 # Editeur : bngesp
 # Date   : 2017.03.16
 # Product: Turbidity
 # SKU    : SEN0189
*/

#ifndef WSNTurbiditySensor_h
#define WSNTurbiditySensor_h

#include <stdlib.h>
#include <stdint.h>
#include <Arduino.h>

// constantes

#define SensorPin A0  //le pin ou est branche le capteur
#define intervalMesure 20 //intervalle de ou on lit les valeurs sur le pin SensorPin
#define intervalConvertion 800 //intervalle ou les valeurs prises seront convertis en turbidity
#define tailleEchantillon  40  //taille des echantillons


class Turbidity
{

public:
	Turbidity();
	Turbidity(uint8_t sensorPin);
	void updateTurbidity();
	//~Turbidity();
	void init(uint8_t mesure, uint32_t convertion,uint8_t taille);
	uint16_t moyenne(uint8_t* arr, uint8_t number);
	float getMesure();
	
private:
	uint8_t _sensorPin;
	uint8_t _intervalMesure;
	uint32_t _intervalConvertion;
	uint8_t _tailleEchantillon;
	float turbidityValue;
	uint8_t tableauTurbidity[];
	uint8_t indexTurbidity; 

};

#endif