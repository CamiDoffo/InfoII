#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "archivo.h"
Archivo::Archivo(){
}
Archivo::~Archivo(){
}
void check_null(FILE *fp)
{
	if(fp==NULL)
	{
		printf("Imposible mostrar\n");
		exit(1);
	}else{
		printf("Archivo encontrado\n\n");
	}
}

void Archivo::scanText(struct city **Cordoba,struct city **SantaFe,struct city **Mendoza)
{
	int id_prov=0, id_ciudad=0, mes=0, dia=0, hora=0, min=0;
    struct measurement m;
	char nombre[50];
	float temperatura=0, humedad=0;
    
	
	this->fp=fopen("data_set.txt", "r");
	
	check_null(this->fp);
	while(!feof(this->fp))
	{
		fscanf(this->fp,"%d	%d",&id_ciudad,&id_prov);
		if(id_prov==1)	{
            strcpy(nombre, "Cordoba");
			fscanf(this->fp,"	%s			%f	%f	%d	%d	%d	%d\n", nombre, &temperatura, &humedad, &hora, &min, &dia, &mes);
            m.hum=humedad;
            m.temp=temperatura;
            m.time.hh=hora;
            m.time.mm=min;
            m.time.day=dia;
            m.time.month=mes;
			push(m,id_ciudad,id_prov,nombre, Cordoba);
		}else if(id_prov==2){
            strcpy(nombre, "Santa Fe");
			fscanf(this->fp,"	%s			%f	%f	%d	%d	%d	%d\n", nombre, &temperatura, &humedad, &hora, &min, &dia, &mes);
			m.hum=humedad;
            m.temp=temperatura;
            m.time.hh=hora;
            m.time.mm=min;
            m.time.day=dia;
            m.time.month=mes;
            push(m,id_ciudad,id_prov,nombre,SantaFe);
		}else if(id_prov==3){
            strcpy(nombre, "Mendoza");
			fscanf(this->fp,"	%s			%f	%f	%d	%d	%d	%d\n", nombre, &temperatura, &humedad, &hora, &min, &dia, &mes);
			m.hum=humedad;
            m.temp=temperatura;
            m.time.hh=hora;
            m.time.mm=min;
            m.time.day=dia;
            m.time.month=mes;
            push(m,id_ciudad,id_prov,nombre,Mendoza);
		}else{
			fscanf(this->fp, "%*[^n]n");
		}
	}
	
	fclose(this->fp);
	ordenarLista(Cordoba);
	ordenarLista(SantaFe);
	ordenarLista(Mendoza);
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
			"7.Dia mas calido de cada ciudad\n"
			"8.Mejor provincia para cultivar pimientos\n");
	scanf("%d", &op);
	return op;
}
void ordenarLista(struct city **City)
{
    struct city *actual , *siguiente;
    int t;
     
    actual = *City;
    while(actual->next != NULL)
    {
        siguiente = actual->next;
         
        while(siguiente!=NULL)
        {
            if(actual->cityId > siguiente->cityId)
            {
               t = siguiente->cityId;
               siguiente->cityId = actual->cityId;
               actual->cityId = t;          
            }
            siguiente = siguiente->next;                    
        }    
        actual = actual->next;
        siguiente = actual->next;
          
    }
}
void push(struct measurement m, int cityId, int provId, char city_name[50], struct city **head){
    struct city *temp=*head;
    struct city *new_node = (struct city *)malloc(sizeof(struct city));

    //memory check
    if(new_node==NULL){
        printf("Memoria insuficiente\n");
        exit(0);
    }else{
        //seteo el nuevo nodo
        new_node->m=m;
		new_node->cityId=cityId;
		new_node->provId=provId;
		strcpy(new_node->city_name,city_name);
        new_node->next=NULL;
        if(*head==NULL){
            *head=new_node;
        }else{
            while (temp->next!=NULL){
                temp=temp->next;
            }
            temp->next=new_node;
        }
    }
}
void borrarTodo(struct city **head)
{
	struct city *temp;
	while(*head!=NULL){
		temp=*(head);
		*(head)=(*head)->next;
		free(temp);
	}
}
int cantidadMedidas(struct city *City){
	struct city *temp=City;
	int i=0;
	while(temp!=NULL){
		i++;
		temp=temp->next;
	}
	return i;
}
float tempPromProvincia(struct city *City)
{
	struct city *temp=City;
	float sum=0.0,prom=0.0;
	int i=0;
	
	while(temp!=NULL)
	{
		sum+=temp->m.temp;
		i++;
		temp=temp->next;
	}
	prom=sum/i;
	return prom;
}

void tempPromCiudad(struct city *head)
{
	struct city *temp=NULL;
	char cadena[50];
	float suma=0;
	int idAux=0, i=0, j=0;
	temp=head;
	idAux=temp->cityId;
	while(temp!=NULL)
	{
		if(temp->cityId==idAux)
		{
			suma=suma+temp->m.temp;
			i++;
			strcpy(cadena, temp->city_name);
		}else{
			printf("La temperatura promedio en %s es: %.2f °C\n",cadena,suma/i);
			suma=temp->m.temp;
			i=1;
			idAux=temp->cityId;
		}
		temp=temp->next;
	}
	printf("La temperatura promedio en %s es: %.2f °C\n",cadena,suma/i);
}


void ciudadCalida(struct city *head)
{
	struct city *temp=NULL;
	temp=head;
	int i=0, idAux=0, idProv=0;
	char cadena[50],MaxCadena[50];
	float suma=0, max=0;
	idAux=temp->cityId;
	while(temp!=NULL)
	{
		if(temp->cityId==idAux)
		{
			suma=suma+temp->m.temp;
			i++;
			strcpy(cadena, temp->city_name);
			idProv=temp->provId;
		}else{
			if(suma/i>max)
				{
				max=suma/i;
				strcpy(MaxCadena, cadena);
			}
			i=1;
			suma=temp->m.temp;
			idAux=temp->cityId;
		}
		temp=temp->next;
	}
	if(idProv==1){
		printf("La ciudad mas calida de Cordoba es %s, con una temperatura promedio de: %.2f °C\n", MaxCadena, max);
	}else if(idProv==2){
		printf("La ciudad mas calida de Santa Fe es %s, con una temperatura promedio de: %.2f °C\n", MaxCadena, max);
	}else if(idProv==3){
		printf("La ciudad mas calida de Mendoza es %s, con una temperatura promedio de: %.2f °C\n", MaxCadena, max);
	}
}

void ciudadFria(struct city *head)
{
	struct city *temp=NULL;
	temp=head;
	int i=0, idAux=0, idProv=0;
	char cadena[50],MinCadena[50];
	float suma=0, min=100;
	idAux=temp->cityId;
	while(temp!=NULL)
	{
		if(temp->cityId==idAux)
		{
			suma=suma+temp->m.temp;
			i++;
			strcpy(cadena, temp->city_name);
			idProv=temp->provId;
		}else{
			if(suma/i<min)
				{
				min=suma/i;
				strcpy(MinCadena, cadena);
			}
			i=1;
			suma=temp->m.temp;
			idAux=temp->cityId;
		}
		temp=temp->next;
	}
	if(idProv==1){
		printf("La ciudad mas fria de Cordoba es %s, con una temperatura promedio de: %.2f °C\n", MinCadena, min);
	}else if(idProv==2){
		printf("La ciudad mas fria de Santa Fe es %s, con una temperatura promedio de: %.2f °C\n", MinCadena, min);
	}else if(idProv==3){
		printf("La ciudad mas fria de Mendoza es %s, con una temperatura promedio de: %.2f °C\n", MinCadena, min);
	}
}

void diaFrio(struct city *head, int idProv)
{
	struct city *temp=head;
	int d=0, m=0;//dia y mes
	char cadena[50];
	float min=100;
	
	while(temp!=NULL)
	{
		if(temp->m.temp<min)
		{
			min=temp->m.temp;
			strcpy(cadena, temp->city_name);
			d=temp->m.time.day;
			m=temp->m.time.month;
		}
		temp=temp->next;
	}
	if(idProv==1){
		printf("El dia mas frio de Cordoba es %d/%d, con una temperatura de %.2f °C en la ciudad de %s\n", d, m, min, cadena);
	}else if(idProv==2){
		printf("El dia mas frio de Santa Fe es %d/%d, con una temperatura de %.2f °C en la ciudad de %s\n", d, m, min, cadena);
	}else if(idProv==3){
		printf("El dia mas frio de Mendoza es %d/%d, con una temperatura de %.2f °C en la ciudad de %s\n", d, m, min, cadena);
	}
}

void diaCalor(struct city *head){
	float max=0;
	int aux=0,dia=0,mes=0;
	struct city *temp=NULL;
	char cadena[50];
	temp=head;
	aux=temp->cityId;
	while(temp!=NULL){
		if(temp->cityId==aux){
			if(temp->m.temp>max){
				max=temp->m.temp;
				dia=temp->m.time.day;
				mes=temp->m.time.month;
				strcpy(cadena, temp->city_name);
			}
		}else{
			printf("El dia mas caluroso de la ciudad %s fue el dia %d/%d con %.2f °C.\n",cadena,dia,mes,max);
			aux=temp->cityId;
			max=temp->m.temp;
			dia=temp->m.time.day;
			mes=temp->m.time.month;
		}
		temp=temp->next;
	}
	printf("El dia mas caluroso de la ciudad %s fue el dia %d/%d con %.2f °C.\n",cadena,dia,mes,max);	
}

void provPimientos(float promCordoba, float promSantaFe, float promMendoza)
{
	if (fabs(promMendoza-23) < fabs(promCordoba-23) && fabs(promMendoza-23) < fabs(promSantaFe-23))
	{
		printf("La mejor provincia para cultivar pimientos es Mendoza ya que tiene una temperatura promedio de %.2f °C.\n",promMendoza);
	}else if (fabs(promSantaFe-23) < fabs(promCordoba-23))
	{
		printf("La mejor provincia para cultivar pimientos es Santa Fe ya que tiene una temperatura promedio de %.2f °C.\n",promSantaFe);
	}else
	{
		printf("La mejor provincia para cultivar pimientos es Cordoba ya que tiene una temperatura promedio de %.2f °C.\n",promCordoba);
	}
}