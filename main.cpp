#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "analisis_data.cpp"
using namespace std;


int main() {
	Archive file;
	struct city *Cordoba=NULL;
	struct city *SantaFe=NULL;
	struct city *Mendoza=NULL;
	struct Data *d;
	float averageCordoba=0.0, averageSantaFe=0.0, averageMendoza=0.0;
	int amountCordoba=0, amountSantaFe=0, amountMendoza=0;
	char keep='s';

	file.scanText(&Cordoba, &SantaFe, &Mendoza);
	amountCordoba=amountSamples(Cordoba);
	amountSantaFe=amountSamples(SantaFe);
	amountMendoza=amountSamples(Mendoza);
	averageCordoba=tempAverageProvincie(Cordoba);
	averageSantaFe=tempAverageProvincie(SantaFe);
	averageMendoza=tempAverageProvincie(Mendoza);
	

	while (keep=='s' || keep=='S')
	{
		switch (menu())
		{
		case 1://funciona
			printf("Cantidad de mediciones de Cordoba: %d\n",amountCordoba);
			printf("Cantidad de mediciones de Santa Fe: %d\n",amountSantaFe);
			printf("Cantidad de mediciones de Mendoza: %d\n",amountMendoza);
			break;
		case 2://funciona
			printf("Temperatura promedio de la provincia de Cordoba: %.2f\n",averageCordoba);
			printf("Temperatura promedio de la provincia de Mendoza: %.2f\n",averageMendoza);
			printf("Temperatura promedio de la provincia de Santa Fe: %.2f\n",averageSantaFe);
			break;
		case 3:
			tempAverageCity(Cordoba);
			tempAverageCity(Mendoza);
			tempAverageCity(SantaFe);
			break;
		case 4:
			hottestCity(Cordoba);
			hottestCity(Mendoza);
			hottestCity(SantaFe);
			break;
		case 5:
			coldestCity(Cordoba);
			coldestCity(Mendoza);
			coldestCity(SantaFe);
			break;
		case 6:
			coldestDay(Cordoba, Cordoba->provId);
			coldestDay(Mendoza, Mendoza->provId);
			coldestDay(SantaFe, SantaFe->provId);
			break;
		case 7:
			hottestDay(Cordoba);
			hottestDay(Mendoza);
			hottestDay(SantaFe);
			break;
		case 8:
			bestProvPeppers(averageCordoba,averageSantaFe,averageMendoza);
			break;
		default:
			printf("Opcion invalida\n");
			break;
		}
		printf("Otra opcion? s/n\n");
		scanf(" %c", &keep);
	}
	
	popAll(&Cordoba);
	popAll(&Mendoza);
	popAll(&SantaFe);
	return 0;
}