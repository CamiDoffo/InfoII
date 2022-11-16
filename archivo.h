#include <iostream>
#include <string.h>
#include <cstring>
#include <math.h>
using namespace std;

struct Data{
	char cityName[50];
	float dataf;
	int datai;
};
struct timestamp{
	int day;
	int month;
	int hh;
	int mm;
};
struct measurement{
	float temp;
	float hum;
	struct timestamp time;
};

struct city{
	struct city *next;
	struct measurement m;
	int cityId;
	int provId;
	char city_name[50];
};

class Archivo{
	private:
		FILE *fp;
	public:
		Archivo();
		void scanText(struct city **Cordoba,struct city **SantaFe,struct city **Mendoza);
		~Archivo();
};

int menu();
char* convert_to_string(char a[50]);
void push(struct measurement m, int cityId, int provId, char city_name[50], struct city **head);
void borrarTodo(struct city **head);
int cantidadMedidas(struct city *City);
float tempPromProvincia(struct city *City);
struct Data tempPromCiudad(struct city *head, int id);
struct Data ciudadCalida(struct city *head);
struct Data ciudadFria(struct city *head);
void diaFrio(struct city *head, int idProv);
void diaCalor(struct city *head);
void provPimientos(float promCordoba, float promSantaFe, float promMendoza);