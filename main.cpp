#include <iostream>
#include <stdio.h>
#include "archivo.h"
#include "archivo_helper.cpp"
using namespace std;


//int cantidadMedidas(struct city *City);
void push(struct measurement m, int cityId, int provId, char city_name[50], struct city **head);
int menu();
int main(int argc, char *argv[]) {
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
			printf("Cantidad de mediciones: %d",cantidadMedidas(Cordoba)+cantidadMedidas(SantaFe)+cantidadMedidas(Mendoza));
			break;
		case 2:
			for (int i = 0; i < 77; i++)//dudoso, ver
			{
				printf("Temperatura promedio de la provincia de Cordoba: %.2f",promCordoba);
				printf("Temperatura promedio de la provincia de Mendoza: %.2f",promMendoza);
				printf("Temperatura promedio de la provincia de Santa Fe: %.2f",promSantaFe);
			}
			break;
		case 3:
			for (int i = 0; i < 77; i++)//dudoso, ver
			{

				printf("Temperatura promedio de ciudad de Cordoba: %.2f",tempPromCiudad(Cordoba,i).dataf);
				printf("Temperatura promedio de ciudad de Mendoza: %.2f",tempPromCiudad(Mendoza,i).dataf);
				printf("Temperatura promedio de ciudad de Santa Fe: %.2f",tempPromCiudad(SantaFe,i).dataf);
			}
			break;
		case 4:
			d=ciudadCalida(Cordoba);
			printf("La ciudad mas calida de Cordoba es %s con una temperatura de %.2f",d.cityName,d.dataf);
			d=ciudadCalida(Mendoza);
			printf("La ciudad mas calida de Mendoza es %s con una temperatura de %.2f",d.cityName,d.dataf);
			d=ciudadCalida(SantaFe);
			printf("La ciudad mas calida de Santafe es %s con una temperatura de %.2f",d.cityName,d.dataf);
			break;
		case 5:
			d=ciudadFria(Cordoba);
			printf("La ciudad mas fria de Cordoba es %s con una temperatura de %.2f",d.cityName,d.dataf);
			d=ciudadFria(Mendoza);
			printf("La ciudad mas fria de Mendoza es %s con una temperatura de %.2f",d.cityName,d.dataf);
			d=ciudadFria(SantaFe);
			printf("La ciudad mas fria de Santafe es %s con una temperatura de %.2f",d.cityName,d.dataf);
			break;
		case 6:
			diaFrio(Cordoba);
			diaFrio(Mendoza);
			diaFrio(SantaFe);
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
	




	return 0;
}

int menu(){
	int op=0;
	printf("Ingrese una opcion:\n"
			"1.Cantidad de mediciones por provincia\n"
			"2.Temperatura promedio de cada provincia\n"
			"3.Temperatura promedio de cada ciudad\n"
			"4.Ciudad mas calida de cada provincia\n"
			"5.Ciudad mas fria de cada provincia\n"
			"6.Dia mas frio de cada provincia\n"
			"7.Cia mas calido de cada ciudad\n"
			"8.Mejor provincia para cultivar pimientos\n");
	scanf("%d", &op);
	return op;
}