#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <math.h>
#include <stdint.h>
#define no_of_points 2
#define M_PI 3.14159265358979323846
#define rad 6371
#include<string.h>

static double haversine(double lat1, double lon1, double lat2, double lon2)
	{
				double a, c, z;
        // distance between latitudes
        // and longitudes
        double dLat = (lat2 - lat1) * M_PI / 180.0;
        double dLon = (lon2 - lon1) * M_PI / 180.0;
 
        // convert to radians
        lat1 = (lat1) * M_PI / 180.0;
        lat2 = (lat2) * M_PI / 180.0;
 
        // apply formulae
        a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
        c = 2 * asin(sqrt(a));
        
				z = rad* c* pow(10,3);
				
				return z;
	}
