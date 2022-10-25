#ifndef _WEATHER_UTILS_H
#define _WEATHER_UTILS_H
#include <stdio.h>
#include "array_helpers.h"
#include "weather.h"

// returns the lowest minimum temperature in history
int lowest_min_temp(WeatherTable array);

// gives the highest maximum temperature of each year
void highest_max_temp(WeatherTable array, int output[YEARS]);

// gives the month of maximum rainfall per year
void max_monthly_rainfall_per_year(WeatherTable array, t_month output[YEARS]);

#endif