#include <iostream>
#include <cstring>
#include <math.h>
using namespace std;

struct Data
{
	char cityName[50];
	float dataf;
	int datai;
};

struct city{
	struct city *next;
	struct measurement m;
	int cityId;
	int provId;
	char city_name[50];
};

struct measurement{
	float temp;
	float hum;
	struct timestamp time;
};

struct timestamp{
	int day;
	int month;
	int hh;
	int mm;
};

class Archivo{
	private:
		FILE *fp;
	public:
		Archivo();
		void scanText(struct city **Cordoba,struct city **SantaFe,struct city **Mendoza);
		~Archivo();
};

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
		for(int i=0; i<50;i++)
			new_node->city_name[i]=city_name[i];
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
float tempPromProvincia(struct city *City)
{
	struct city *temp=NULL;
	float prom=0.0;
	int i=0;
	temp=City;
	while(temp!=NULL)
	{
		prom+=temp->m.temp;
		i++;
		temp=temp->next;
	}
	
	return prom/i;
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
struct Data tempPromCiudad(struct city *head, int id)
{
	struct city *temp=head;
	struct Data d;
	float suma=0.0;
	int i=0;
	
	while(temp!=NULL)
	{
		if(temp->cityId==id)
		{
			suma+=temp->m.temp;
			i++;
			for(int j=0; j<50; j++)
			{
			d.cityName[i]=temp->city_name[j];
			}
		}
		temp=temp->next;
	}
	d.dataf=suma/(float)i;
	return d;
}
struct Data ciudadCalida(struct city *head)
{
	struct city *temp=head;
	struct Data d;
	d.dataf=tempPromCiudad(head, 0).dataf;

	for (int i = 1; i < 77; i++)
	{
		if(d.dataf<tempPromCiudad(head, i).dataf){
			d.dataf=tempPromCiudad(head, i).dataf;
			d.datai=i;
			for (int i = 0; i < 50; i++)
			{
				d.cityName[i]=tempPromCiudad(head, i).cityName[i];
			}
		}
	}
	return d;
}
struct Data ciudadFria(struct city *head)
{
	struct city *temp=head;
	struct Data d;
	d.dataf=tempPromCiudad(head, 0).dataf;

	for (int i = 1; i < 77; i++)
	{
		if(d.dataf>tempPromCiudad(head, i).dataf){
			d.dataf=tempPromCiudad(head, i).dataf;
			for (int i = 0; i < 50; i++)
			{
				d.cityName[i]=tempPromCiudad(head, i).cityName[i];
			}
		}
	}
	return d;
}
void diaFrio(struct city *head)
{
	struct city *temp=head;
	int k=0, d=0, m=0,idProv=0;
	char cadena[50];
	float min=100;
	
	while(temp!=NULL)
	{
		if(temp->m.temp<min)
		{
			min=temp->m.temp;
			idProv=temp->provId;
			for(k=0;k<50;k++)
			{
				cadena[k]=temp->city_name[k];
			}
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

void diaCalor(struct city *head){
	float max=0;
	int dia=0,mes=0;
	struct city *temp=head;
	char cadena[50];
	struct Data d = ciudadCalida(head);
	while(temp!=NULL){
		if(temp->cityId==d.datai){//datai==identificador de ciudad
			if(temp->m.temp>max){
				max=temp->m.temp;
				dia=temp->m.time.day;
				mes=temp->m.time.month;
				for(int k=0; k<50; k++)
				{
					cadena[k]=temp->city_name[k];
				}
			}
		}
		temp=temp->next;
	}
	printf("El dia mas caluroso de la ciudad %s fue el dia %d/%d con %.2f °C.\n",cadena,dia,mes,max);	
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