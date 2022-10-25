#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"

int lowest_min_temp(WeatherTable array){
    Weather lowest;
    lowest = array[FST_YEAR][january][FST_DAY];

    for (int year = FST_YEAR; year < LST_YEAR; ++year){
        for (t_month month = january; month < december; ++month){
            for (int day = FST_DAY; day < LST_DAY; ++day){
                if (array[year][month][day]._min_temp < lowest._min_temp){
                    lowest._min_temp = array[year][month][day]._min_temp;
                }
            }
        }
    }

    return lowest._min_temp;
}

void highest_max_temp(WeatherTable array, int output[YEARS]){
    Weather highest;
    highest = array[FST_YEAR][january][FST_DAY];
    //i need to take the maximum temperature per year, for that i calculate the maximum temperature throught each day of the year
    for (int year = 0u; year < LST_YEAR; ++year){ // the same as "for (int year = FST_YEAR; year < LST_YEAR; ++year){"
        for (t_month month = january; month <= december; ++month){
            for (int day = 0u; day < LST_DAY; ++day){
                if (array[year + FST_YEAR][month][day + FST_DAY]._max_temp > highest._max_temp){
                    highest._max_temp = array[year + FST_YEAR][month][day + FST_DAY]._max_temp;
                }
            }
        }
        output[year] = highest._max_temp;
        printf("La mayor temperatura maxima por año es:");
        printf("En %u: %d", year, highest._max_temp);
    }
}

void max_monthly_rainfall_per_year(WeatherTable array, t_month output[YEARS]){
    Weather weather;
    weather = array[FST_YEAR][january][FST_DAY];
    t_month aux[MONTHS];

    for (int year = FST_YEAR; year < LST_YEAR; ++year){
        for (t_month month = january; month < december; ++month){
            for (int day = FST_DAY; day < LST_DAY; ++day){
                if (array[year][month][day]._rainfall < weather._rainfall){
                    aux[month] = array[year][month][day]._rainfall;
                }
            }
            if (month > january){
                if (aux[month-1] <= aux[month]){
                    output[year] = month;
                }
                else{
                    output[year] = month-1;
                }
            }
            printf("El mes con mayor cantidad de precipitaciones por año es:\n");
            printf("En %u: %d", year, output[year]);
        }
    }
}