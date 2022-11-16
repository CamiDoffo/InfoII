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
	struct Data *d;
	float promCordoba=0.0, promSantaFe=0.0, promMendoza=0.0;
	int cantCordoba=0, cantSantaFe=0, cantMendoza=0;
	char seguir='s';

	file.scanText(&Cordoba, &SantaFe, &Mendoza);
	cantCordoba=cantidadMedidas(Cordoba);
	cantSantaFe=cantidadMedidas(SantaFe);
	cantMendoza=cantidadMedidas(Mendoza);
	promCordoba=tempPromProvincia(Cordoba);
	promSantaFe=tempPromProvincia(SantaFe);
	promMendoza=tempPromProvincia(Mendoza);
	

	while (seguir=='s' || seguir=='S')
	{
		switch (menu())
		{
		case 1://funciona
			printf("Cantidad de mediciones de Cordoba: %d\n",cantCordoba);
			printf("Cantidad de mediciones de Santa Fe: %d\n",cantSantaFe);
			printf("Cantidad de mediciones de Mendoza: %d\n",cantMendoza);
			break;
		case 2://funciona
			printf("Temperatura promedio de la provincia de Cordoba: %.2f\n",promCordoba);
			printf("Temperatura promedio de la provincia de Mendoza: %.2f\n",promMendoza);
			printf("Temperatura promedio de la provincia de Santa Fe: %.2f\n",promSantaFe);
			break;
		case 3:
			tempPromCiudad(Cordoba);
			tempPromCiudad(Mendoza);
			tempPromCiudad(SantaFe);
			break;
		case 4:
			ciudadCalida(Cordoba);
			ciudadCalida(Mendoza);
			ciudadCalida(SantaFe);
			break;
		case 5:
			ciudadFria(Cordoba);
			ciudadFria(Mendoza);
			ciudadFria(SantaFe);
			break;
		case 6:
			diaFrio(Cordoba, Cordoba->provId);
			diaFrio(Mendoza, Mendoza->provId);
			diaFrio(SantaFe, SantaFe->provId);
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