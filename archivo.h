#include <iostream>
#include <string.h>
#include <cstring>
#include <math.h>
using namespace std;

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

class Archive{
	private:
		FILE *fp;
	public:
		Archive();
		void scanText(struct city **Cordoba,struct city **SantaFe,struct city **Mendoza);
		~Archive();
};

int menu();
void sortList(struct city **City);
void push(struct measurement m, int cityId, int provId, char city_name[50], struct city **head);
void popAll(struct city **head);
int amountSamples(struct city *City);
float tempAverageProvincie(struct city *City);
void tempAverageCity(struct city *head);
void hottestCity(struct city *head);
void coldestCity(struct city *head);
void coldestDay(struct city *head, int idProv);
void hottestDay(struct city *head);
void bestProvPeppers(float averageCordoba, float averageSantaFe, float averageMendoza);