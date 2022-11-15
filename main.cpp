#include <iostream>
using namespace std;

struct city{
	struct city *next;
	struct meansurement m;
	int cityId;
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

struct blablabla{
	int pepe;
};

int main(int argc, char *argv[]) {
	char *filepath = NULL;
	
	/* parse the filepath given in command line arguments */
	filepath = parse_filepath(argc, argv);
	
	/* create an array with the type of tclimate */
	WeatherTable array;
	
	/* parse the file to fill the array and obtain the actual length */
	array_from_file(array, filepath);
	
	/* show the ordered array in the screen */
	array_dump(array);
	
	// show the lowest minimum temperature in history
	int lowest = lowest_min_temp(array);
	printf("La menor temperatura minima historica es: %d\n", lowest);
	
	//show the highest maximum temperature of each year
	int output[YEARS];
	highest_max_temp(array, output);
	
	// show the month of maximum rainfall per year
	t_month output2[YEARS];
	max_monthly_rainfall_per_year(array, output2);
	//hola pepito
	return 0;
}

