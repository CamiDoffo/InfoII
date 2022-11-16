#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "analisis_data.cpp"
using namespace std;


int main() {
	Archivo file;
	struct city *Cordoba=NULL;
	struct city *SantaFe=NULL;
	struct city *Mendoza=NULL;
	struct Data d;
	float promCordoba=tempPromProvincia(Cordoba), promSantaFe=tempPromProvincia(SantaFe), promMendoza=tempPromProvincia(Mendoza);
	char seguir='s';

	file.scanText(&Cordoba, &SantaFe, &Mendoza);

	while (seguir=='s')
	{
		switch (menu())
		{
		case 1:
			printf("Cantidad de mediciones: %d\n",cantidadMedidas(Cordoba)+cantidadMedidas(SantaFe)+cantidadMedidas(Mendoza));
			break;
		case 2:
			printf("Temperatura promedio de la provincia de Cordoba: %.2f\n",promCordoba);
			printf("Temperatura promedio de la provincia de Mendoza: %.2f\n",promMendoza);
			printf("Temperatura promedio de la provincia de Santa Fe: %.2f\n",promSantaFe);
			break;
		case 3:
			for (int i = 0; i < 77; i++)//dudoso, ver
			{
				d=tempPromCiudad(Cordoba,i);
				printf("Temperatura promedio de %s de Cordoba: %.2f\n",d.cityName,d.dataf);
				d=tempPromCiudad(Mendoza,i);
				printf("Temperatura promedio de %s de Mendoza: %.2f\n",d.cityName,d.dataf);
				d=tempPromCiudad(SantaFe,i);
				printf("Temperatura promedio de %s de Santa Fe: %.2f\n",d.cityName,d.dataf);
			}
			break;
		case 4:
			d=ciudadCalida(Cordoba);
			printf("La ciudad mas calida de Cordoba es %s con una temperatura de %.2f\n",d.cityName,d.dataf);
			d=ciudadCalida(Mendoza);
			printf("La ciudad mas calida de Mendoza es %s con una temperatura de %.2f\n",d.cityName,d.dataf);
			d=ciudadCalida(SantaFe);
			printf("La ciudad mas calida de Santafe es %s con una temperatura de %.2f\n",d.cityName,d.dataf);
			break;
		case 5:
			d=ciudadFria(Cordoba);
			printf("La ciudad mas fria de Cordoba es %s con una temperatura de %.2f\n",d.cityName,d.dataf);
			d=ciudadFria(Mendoza);
			printf("La ciudad mas fria de Mendoza es %s con una temperatura de %.2f\n",d.cityName,d.dataf);
			d=ciudadFria(SantaFe);
			printf("La ciudad mas fria de Santafe es %s con una temperatura de %.2f\n",d.cityName,d.dataf);
			break;
		case 6:
			diaFrio(Cordoba,Cordoba->cityId);
			diaFrio(Mendoza, Mendoza->cityId);
			diaFrio(SantaFe, SantaFe->cityId);
			break;
		case 7:
			diaCalor(Cordoba);
			diaCalor(Mendoza);
			diaCalor(SantaFe);
			break;
		case 8:
			provPimientos(promCordoba,promSantaFe,promMendoza);
			break;
		default:
			printf("Opcion invalida\n");
			break;
		}
		printf("Otra opcion? s/n\n");
		scanf(" %c", &seguir);
	}
	
	borrarTodo(&Cordoba);
	borrarTodo(&Mendoza);
	borrarTodo(&SantaFe);
	return 0;
}