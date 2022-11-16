#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "archivo.h"
Archive::Archive(){
}
Archive::~Archive(){
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

void Archive::scanText(struct city **Cordoba,struct city **SantaFe,struct city **Mendoza)
{
	int id_prov=0, id_city=0, month=0, day=0, hour=0, min=0;
    struct measurement m;
	char name[50];
	float temperature=0, humidity=0;
    
	
	this->fp=fopen("data_set.txt", "r");
	
	check_null(this->fp);
	while(!feof(this->fp))
	{
		fscanf(this->fp,"%d	%d",&id_city,&id_prov);
		if(id_prov==1)	{
			fscanf(this->fp,"	%s			%f	%f	%d	%d	%d	%d\n", name, &temperature, &humidity, &hour, &min, &day, &month);
            strcpy(name, "Cordoba");
            m.temp=temperature;
			m.hum=humidity;
            m.time.hh=hour;
            m.time.mm=min;
            m.time.day=day;
            m.time.month=month;
			push(m,id_city,id_prov,name, Cordoba);
		}else if(id_prov==2){
            
			fscanf(this->fp,"	%s			%f	%f	%d	%d	%d	%d\n", name, &temperature, &humidity, &hour, &min, &day, &month);
			strcpy(name, "Santa Fe");
            m.temp=temperature;
			m.hum=humidity;
            m.time.hh=hour;
            m.time.mm=min;
            m.time.day=day;
            m.time.month=month;
            push(m,id_city,id_prov,name,SantaFe);
		}else if(id_prov==3){
            strcpy(name, "Mendoza");
			fscanf(this->fp,"	%s			%f	%f	%d	%d	%d	%d\n", name, &temperature, &humidity, &hour, &min, &day, &month);
			m.hum=humidity;
            m.temp=temperature;
            m.time.hh=hour;
            m.time.mm=min;
            m.time.day=day;
            m.time.month=month;
            push(m,id_city,id_prov,name,Mendoza);
		}else{
			fscanf(this->fp, "%*[^n]n");
		}
	}
	
	fclose(this->fp);
	sortList(Cordoba);
	sortList(SantaFe);
	sortList(Mendoza);
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
void sortList(struct city **City)
{
    struct city *current , *after;
    int t;
     
    current = *City;
    while(current->next != NULL)
    {
        after = current->next;
         
        while(after!=NULL)
        {
            if(current->cityId > after->cityId)
            {
               t = after->cityId;
               after->cityId = current->cityId;
               current->cityId = t;          
            }
            after = after->next;                    
        }    
        current = current->next;
        after = current->next;
          
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
void popAll(struct city **head)
{
	struct city *temp;
	while(*head!=NULL){
		temp=*(head);
		*(head)=(*head)->next;
		free(temp);
	}
}
//This function calculates the number of samples of each province
int amountSamples(struct city *City){
	struct city *temp=City;
	int i=0;
	while(temp!=NULL){
		i++;
		temp=temp->next;
	}
	return i;
}
//This function calculates the average of temperatures of each province
float tempAverageProvincie(struct city *City)
{
	struct city *temp=City;
	float add=0.0;
	int i=0;
	
	while(temp!=NULL)
	{
		add+=temp->m.temp;
		i++;
		temp=temp->next;
	}
	return add/i;
}
//This function calculates the average of temperatures of each city
void tempAverageCity(struct city *head)
{
	struct city *temp=NULL;
	char chain[50];
	float add=0;
	int id=0, i=0, j=0;
	temp=head;
	id=temp->cityId;
	while(temp!=NULL)
	{
		if(temp->cityId==id)
		{
			add+=temp->m.temp;
			i++;
			strcpy(chain, temp->city_name);
		}else{
			printf("La temperatura promedio en %s es: %.2f °C\n",chain,add/i);
			add=temp->m.temp;
			i=1;
			id=temp->cityId;
		}
		temp=temp->next;
	}
	printf("La temperatura promedio en %s es: %.2f °C\n",chain,add/i);
}

void hottestCity(struct city *head)
{
	struct city *temp=head;
	int i=0, idCity=0, idProv=0;
	char chain[50],MaxChain[50];
	float add=0, max=0;
	idCity=temp->cityId;
	while(temp!=NULL)
	{
		if(temp->cityId==idCity)
		{
			add+=temp->m.temp;
			i++;
			strcpy(chain, temp->city_name);
			idProv=temp->provId;
		}else{
			if(add/i>max)
				{
				max=add/i;
				strcpy(MaxChain, chain);
			}
			i=1;
			add=temp->m.temp;
			idCity=temp->cityId;
		}
		temp=temp->next;
	}
	if(idProv==1){
		printf("La ciudad mas calida de Cordoba es %s, con una temperatura promedio de: %.2f °C\n", MaxChain, max);
	}else if(idProv==2){
		printf("La ciudad mas calida de Santa Fe es %s, con una temperatura promedio de: %.2f °C\n", MaxChain, max);
	}else if(idProv==3){
		printf("La ciudad mas calida de Mendoza es %s, con una temperatura promedio de: %.2f °C\n", MaxChain, max);
	}
}

void coldestCity(struct city *head)
{
	struct city *temp=head;
	int i=0, idCity=0, idProv=0;
	char chain[50],MinChain[50];
	float add=0, min=100;
	idCity=temp->cityId;
	while(temp!=NULL)
	{
		if(temp->cityId==idCity)
		{
			add+=temp->m.temp;
			i++;
			strcpy(chain, temp->city_name);
			idProv=temp->provId;
		}else{
			if(add/i<min)
				{
				min=add/i;
				strcpy(MinChain, chain);
			}
			i=1;
			add=temp->m.temp;
			idCity=temp->cityId;
		}
		temp=temp->next;
	}
	if(idProv==1){
		printf("La ciudad mas fria de Cordoba es %s, con una temperatura promedio de: %.2f °C\n", MinChain, min);
	}else if(idProv==2){
		printf("La ciudad mas fria de Santa Fe es %s, con una temperatura promedio de: %.2f °C\n", MinChain, min);
	}else if(idProv==3){
		printf("La ciudad mas fria de Mendoza es %s, con una temperatura promedio de: %.2f °C\n", MinChain, min);
	}
}

void coldestDay(struct city *head, int idProv)
{
	struct city *temp=head;
	int d=0, m=0;//dia y mes
	char chain[50];
	float min=100;
	
	while(temp!=NULL)
	{
		if(temp->m.temp<min)
		{
			min=temp->m.temp;
			strcpy(chain, temp->city_name);
			d=temp->m.time.day;
			m=temp->m.time.month;
		}
		temp=temp->next;
	}
	if(idProv==1){
		printf("El dia mas frio de Cordoba es %d/%d, con una temperatura de %.2f °C en la ciudad de %s\n", d, m, min, chain);
	}else if(idProv==2){
		printf("El dia mas frio de Santa Fe es %d/%d, con una temperatura de %.2f °C en la ciudad de %s\n", d, m, min, chain);
	}else if(idProv==3){
		printf("El dia mas frio de Mendoza es %d/%d, con una temperatura de %.2f °C en la ciudad de %s\n", d, m, min, chain);
	}
}

void hottestDay(struct city *head){
	float max=0;
	int aux=0,day=0,month=0;
	struct city *temp=NULL;
	char chain[50];
	temp=head;
	aux=temp->cityId;
	while(temp!=NULL){
		if(temp->cityId==aux){
			if(temp->m.temp>max){
				max=temp->m.temp;
				day=temp->m.time.day;
				month=temp->m.time.month;
				strcpy(chain, temp->city_name);
			}
		}else{
			printf("El dia mas caluroso de la ciudad %s fue el dia %d/%d con %.2f °C.\n",chain,day,month,max);
			aux=temp->cityId;
			max=temp->m.temp;
			day=temp->m.time.day;
			month=temp->m.time.month;
		}
		temp=temp->next;
	}
	printf("El dia mas caluroso de la ciudad %s fue el dia %d/%d con %.2f °C.\n",chain,day,month,max);	
}

void bestProvPeppers(float averageCordoba, float averageSantaFe, float averageMendoza)
{
	if (fabs(averageMendoza-23) < fabs(averageCordoba-23) && fabs(averageMendoza-23) < fabs(averageSantaFe-23))
	{
		printf("La mejor provincia para cultivar pimientos es Mendoza ya que tiene una temperatura promedio de %.2f °C.\n",averageMendoza);
	}else if (fabs(averageSantaFe-23) < fabs(averageCordoba-23))
	{
		printf("La mejor provincia para cultivar pimientos es Santa Fe ya que tiene una temperatura promedio de %.2f °C.\n",averageSantaFe);
	}else
	{
		printf("La mejor provincia para cultivar pimientos es Cordoba ya que tiene una temperatura promedio de %.2f °C.\n",averageCordoba);
	}
}