#include "WSNTurbiditySensor.h"

Turbidity::Turbidity()
{
	_sensorPin = SensorPin;
	
	_intervalMesure = intervalMesure;
	_intervalConvertion = intervalConvertion;
	_tailleEchantillon = tailleEchantillon;
	turbidityValue = 0.0;
	tableauTurbidity[_tailleEchantillon];
	indexTurbidity=0; 
};

Turbidity::Turbidity(uint8_t pin)
{
	_sensorPin = pin;
	_intervalMesure = intervalMesure;
	_intervalConvertion = intervalConvertion;
	_tailleEchantillon = tailleEchantillon;
	turbidityValue = 0.0;
	tableauTurbidity[_tailleEchantillon];
	indexTurbidity=0; 
};

void Turbidity::init(uint8_t mesure, uint32_t Convertion,uint8_t taille)
{

	_intervalMesure = mesure;
	_intervalConvertion = Convertion;
	_tailleEchantillon = taille;
	tableauTurbidity[_tailleEchantillon];
	indexTurbidity=0; 
};

float Turbidity::getMesure()
{
	return turbidityValue;
};

uint16_t Turbidity::moyenne(uint8_t* arr, uint8_t number)
{
	uint8_t i;
	 int max,min;
	 uint16_t avg;
	 uint16_t amount=0;

	 if(number<5){  //less than 5, calculated directly statistics
	  for(i=0;i<number;i++){
	    amount+=arr[i];
	  }
	  avg = amount/number;
	  return avg;
	 }else{
	  
	   if(arr[0]<arr[1]){
	    min = arr[0];max=arr[1];
	   }
	   else{
	     min=arr[1];max=arr[0];
	    }
	    
	 for(i=2;i<number;i++){
	  if(arr[i]<min){
	    amount+=min;  //arr<min
	    min=arr[i];
	  }else {
	    if(arr[i]>max){
	      amount+=max;  //arr>max
	      max=arr[i];
	    }else{
	      amount+=arr[i]; //min<=arr<=max
	    }
	  }//if

	 }//for

	 avg = (uint16_t)amount/(number-2);

	 }//if

	 return avg;
};

void Turbidity::updateTurbidity()
{
	static unsigned long samplingTime = millis();
	//static unsigned long printTime = millis();
	static uint16_t voltage;

	if(millis()-samplingTime > _intervalMesure)
	{
		tableauTurbidity[indexTurbidity++]=analogRead(_sensorPin);
		if(indexTurbidity == _tailleEchantillon)
			{
				indexTurbidity=0;
			}
		voltage = moyenne(tableauTurbidity, _tailleEchantillon)*(5.0/1024.0);
		turbidityValue = (voltage*0.1035) - 0.292;
		//turbidityValue −= 0.292 ;
		samplingTime=millis();
	}
}


