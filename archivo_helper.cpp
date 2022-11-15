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
			fscanf(this->fp,"	%s			%f	%f	%d	%d	%d	%d\n", &nombre, &temperatura, &humedad, &hora, &min, &dia, &mes);
            m.hum=humedad;
            m.temp=temperatura;
            m.time.hh=hora;
            m.time.mm=min;
            m.time.day=dia;
            m.time.month=mes;
			push(m,id_ciudad,id_prov,"Cordoba", Cordoba);
		}else if(id_prov==2){
			fscanf(this->fp,"	%s			%f	%f	%d	%d	%d	%d\n", &nombre, &temperatura, &humedad, &hora, &min, &dia, &mes);
			m.hum=humedad;
            m.temp=temperatura;
            m.time.hh=hora;
            m.time.mm=min;
            m.time.day=dia;
            m.time.month=mes;
            push(m,id_ciudad,id_prov,"Santa Fe",SantaFe);
		}else if(id_prov==3){
			fscanf(this->fp,"	%s			%f	%f	%d	%d	%d	%d\n", &nombre, &temperatura, &humedad, &hora, &min, &dia, &mes);
			m.hum=humedad;
            m.temp=temperatura;
            m.time.hh=hora;
            m.time.mm=min;
            m.time.day=dia;
            m.time.month=mes;
            push(m,id_ciudad,id_prov,"Mendoza",Mendoza);
		}else{
			fscanf(this->fp, "%*[^n]n");
		}
	}
	
	fclose(this->fp);
}

